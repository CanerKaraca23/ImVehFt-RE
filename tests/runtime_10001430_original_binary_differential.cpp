#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" void* __stdcall FUN_10001430(char*, std::uint32_t);
extern "C" void* __cdecl FUN_10010893(std::size_t);

struct ExceptionStorage
{
    void* __thiscall construct(char** message);
};

void* ExceptionStorage::construct(char** message)
{
    (void)message;
    return this;
}

extern "C" __declspec(noreturn) void __stdcall __CxxThrowException_8(
    void*, const void*)
{
    std::abort();
}

std::uint8_t DAT_10028608 = 0;
extern "C"
{
std::uint8_t IVF_RELOC_TARGET_10022250[4] = {};
}

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kFunctionAddress = 0x10001430;
constexpr std::uint32_t kAllocationCallAddress = 0x10001438;
constexpr std::uint32_t kAllocatorAddress = 0x10010893;
constexpr std::uint32_t kAllocationSize = 0x14;

void* g_allocation_result = nullptr;
std::uint32_t g_allocation_size = 0;
unsigned g_allocation_calls = 0;

int Fail(const char* message)
{
    std::fprintf(stderr, "FAIL: %s\n", message);
    return 1;
}

std::uint8_t* MapPreferredImage(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;

    const DWORD file_size = GetFileSize(file, nullptr);
    if (file_size == INVALID_FILE_SIZE || file_size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }

    std::vector<std::uint8_t> bytes(file_size);
    DWORD read = 0;
    const BOOL read_ok = ReadFile(file, bytes.data(), file_size, &read, nullptr);
    CloseHandle(file);
    if (!read_ok || read != file_size)
        return nullptr;

    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
        return nullptr;
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase)
        return nullptr;

    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kImageBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kImageBase)))
        return nullptr;
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);

    auto* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (section->SizeOfRawData == 0)
            continue;
        if (section->PointerToRawData > bytes.size() ||
            section->SizeOfRawData > bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData >
                nt->OptionalHeader.SizeOfImage - section->VirtualAddress)
        {
            VirtualFree(image, 0, MEM_RELEASE);
            return nullptr;
        }
        std::memcpy(image + section->VirtualAddress,
                    bytes.data() + section->PointerToRawData,
                    section->SizeOfRawData);
    }
    return image;
}

bool RedirectAllocatorCall(std::uint8_t* image)
{
    auto* code = image + (kAllocationCallAddress - kImageBase);
    if (code[0] != 0xe8)
        return false;
    std::int32_t old_relative = 0;
    std::memcpy(&old_relative, code + 1, sizeof(old_relative));
    if (kAllocationCallAddress + 5 + old_relative != kAllocatorAddress)
        return false;

    const auto replacement = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10010893) -
        (static_cast<std::uintptr_t>(kAllocationCallAddress) + 5));
    DWORD old_protection = 0;
    if (!VirtualProtect(code, 5, PAGE_EXECUTE_READWRITE, &old_protection))
        return false;
    std::memcpy(code + 1, &replacement, sizeof(replacement));
    DWORD ignored = 0;
    if (!VirtualProtect(code, 5, old_protection, &ignored))
        return false;
    return FlushInstructionCache(GetCurrentProcess(), code, 5) != 0;
}

using TestFunction = void*(__stdcall*)(char*, std::uint32_t);

extern "C" __declspec(naked) void* __cdecl InvokeWithEsi(
    TestFunction, char*, std::uint32_t, std::uint32_t*)
{
    __asm
    {
        push ebp
        mov ebp, esp
        push esi
        mov esi, dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0ch]
        call dword ptr [ebp + 08h]
        pop esi
        pop ebp
        ret
    }
}

bool CompareOne(TestFunction original, std::uint32_t iteration)
{
    alignas(16) std::uint32_t original_result[5] = {
        0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555};
    alignas(16) std::uint32_t candidate_result[5] = {
        0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee};
    char argument[16] = {};
    for (std::size_t i = 0; i + 1 < sizeof(argument); ++i)
        argument[i] = static_cast<char>('A' + ((iteration + i) % 26));
    const std::uint32_t parameter = 0x10203040u ^ (iteration * 0x01010101u);
    std::uint32_t context[3] = {
        0x12340000u + iteration,
        0x56780000u ^ (iteration * 17u),
        0x9abc0000u - iteration * 3u};

    g_allocation_result = original_result;
    g_allocation_size = 0;
    g_allocation_calls = 0;
    void* original_return = InvokeWithEsi(original, argument, parameter, context);
    const auto original_calls = g_allocation_calls;
    const auto original_size = g_allocation_size;

    g_allocation_result = candidate_result;
    g_allocation_size = 0;
    g_allocation_calls = 0;
    void* candidate_return = InvokeWithEsi(
        &FUN_10001430, argument, parameter, context);
    const auto candidate_calls = g_allocation_calls;
    const auto candidate_size = g_allocation_size;

    if (original_return != original_result || candidate_return != candidate_result)
        return false;
    if (original_calls != 1 || candidate_calls != 1 ||
        original_size != kAllocationSize || candidate_size != kAllocationSize)
        return false;
    return std::memcmp(original_result, candidate_result,
                       sizeof(original_result)) == 0 &&
           original_result[0] == reinterpret_cast<std::uintptr_t>(argument) &&
           original_result[1] == parameter && original_result[2] == context[0] &&
           original_result[3] == context[1] && original_result[4] == context[2];
}
} // namespace

extern "C" void* __cdecl FUN_10010893(std::size_t size)
{
    ++g_allocation_calls;
    g_allocation_size = static_cast<std::uint32_t>(size);
    return g_allocation_result;
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return Fail("usage: harness <hash-pinned-original-ImVehFt.asi>");

    auto* image = MapPreferredImage(argv[1]);
    if (image == nullptr)
        return Fail("could not map the original ASI at its preferred base");
    if (!RedirectAllocatorCall(image))
        return Fail("original allocator callsite did not match Ghidra evidence");

    const auto original = reinterpret_cast<TestFunction>(
        image + (kFunctionAddress - kImageBase));
    for (std::uint32_t i = 0; i < 64; ++i)
    {
        if (!CompareOne(original, i))
        {
            std::fprintf(stderr, "allocation-success differential mismatch at case %u\n", i);
            return 1;
        }
    }
    VirtualFree(image, 0, MEM_RELEASE);
    std::printf("allocation-success differential: 64/64 cases matched\n");
    return 0;
}
