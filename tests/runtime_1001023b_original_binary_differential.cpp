#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

struct FUN_1001023b_this
{
    void __thiscall invoke(
        const std::uint32_t* param_1,
        std::uint32_t unused_stack_param);
};

extern "C" std::uint8_t IVF_RELOC_TARGET_10022228[4];
std::uint8_t IVF_RELOC_TARGET_10022228[4] = {};

namespace
{
constexpr std::uint32_t kBase = 0x10000000;
constexpr std::uint32_t kTarget = 0x1001023b;
constexpr std::uint32_t kExceptionVtable = 0x10022228;

int Fail(const char* message)
{
    std::fprintf(stderr, "FAIL: %s\n", message);
    return 1;
}

std::uint8_t* MapOriginal(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    const DWORD size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(size);
    DWORD read = 0;
    const BOOL ok = ReadFile(file, bytes.data(), size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size)
        return nullptr;
    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
        return nullptr;
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kBase)
        return nullptr;
    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kBase)))
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

extern "C" __declspec(naked) std::int32_t __cdecl InvokeThiscallTwoArgs(
    void*, void*, const std::uint32_t*, std::uint32_t)
{
    __asm
    {
        push ebp
        mov ebp, esp
        push ebx
        mov ebx, esp
        mov ecx, dword ptr [ebp + 0ch]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        call dword ptr [ebp + 8]
        mov eax, esp
        sub eax, ebx
        mov esp, ebx
        pop ebx
        pop ebp
        ret
    }
}

bool RunCase(void* original, void* candidate, std::uint32_t iteration)
{
    alignas(4) std::uint32_t original_object[3] = {
        0xeeee0000u ^ iteration,
        0xcccc0000u + iteration * 0x101u,
        0xa1b2c3d4u ^ (iteration * 0x10001u)};
    alignas(4) std::uint32_t candidate_object[3];
    std::memcpy(candidate_object, original_object, sizeof(original_object));
    const std::uint32_t value = 0x12345678u ^ (iteration * 0x9e3779b9u);
    const std::uint32_t ignored = (iteration % 11u) * 0x01010101u;

    const auto original_stack_delta = InvokeThiscallTwoArgs(
        original, original_object, &value, ignored);
    const auto candidate_stack_delta = InvokeThiscallTwoArgs(
        candidate, candidate_object, &value, ignored);
    std::uint32_t original_vtable = 0;
    std::uint32_t candidate_vtable = 0;
    std::memcpy(&original_vtable, original_object, 4);
    std::memcpy(&candidate_vtable, candidate_object, 4);
    const auto expected_candidate_vtable = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(IVF_RELOC_TARGET_10022228));
    return original_stack_delta == 0 && candidate_stack_delta == 0 &&
        original_vtable == kExceptionVtable &&
        candidate_vtable == expected_candidate_vtable &&
        original_object[1] == value && candidate_object[1] == value &&
        reinterpret_cast<std::uint8_t*>(original_object)[8] == 0 &&
        reinterpret_cast<std::uint8_t*>(candidate_object)[8] == 0 &&
        std::memcmp(reinterpret_cast<std::uint8_t*>(original_object) + 9,
                    reinterpret_cast<std::uint8_t*>(candidate_object) + 9, 3) == 0;
}
} // namespace

int main(int argc, char** argv)
{
    if (argc != 2)
        return Fail("usage: harness <hash-pinned original ImVehFt.asi>");
    auto* image = MapOriginal(argv[1]);
    if (!image)
        return Fail("could not map original ASI at preferred base");

    using Method = void(FUN_1001023b_this::*)(const std::uint32_t*, std::uint32_t);
    static_assert(sizeof(Method) == sizeof(void*));
    Method method = &FUN_1001023b_this::invoke;
    void* candidate = nullptr;
    std::memcpy(&candidate, &method, sizeof(candidate));
    void* original = image + (kTarget - kBase);
    for (std::uint32_t i = 0; i < 128; ++i)
    {
        if (!RunCase(original, candidate, i))
        {
            std::fprintf(stderr, "ABI/data differential mismatch at case %u\n", i);
            return 1;
        }
    }
    VirtualFree(image, 0, MEM_RELEASE);
    std::puts("1001023b original-binary differential: 128/128 cases matched; both clean 8 stack bytes");
    return 0;
}
