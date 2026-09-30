#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" void __cdecl FUN_1001074b(void*);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kEntry = 0x1001074b;
constexpr std::uint32_t kFreeTailJump = 0x1001075c;
constexpr std::uint32_t kOriginalFree = 0x100116db;

struct Invocation
{
    std::int32_t esp_after_call;
    std::int32_t esp_after_caller_cleanup;
};

std::uint32_t g_free_count = 0;
std::uint32_t g_freed_pointer = 0;
volatile std::uint32_t g_esp_before = 0;

extern "C" void __cdecl _free(void* memory)
{
    ++g_free_count;
    g_freed_pointer = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(memory));
}

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, std::uint32_t, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov ecx, dword ptr [ebp + 10h]
        mov dword ptr [ecx], edx
        add esp, 4
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov dword ptr [ecx + 4], edx
        pop ebp
        ret
    }
}

std::uint8_t* MapReference(char const* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    DWORD const size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(size);
    DWORD read = 0;
    BOOL const ok = ReadFile(file, bytes.data(), size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size)
        return nullptr;
    auto const* dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
        return nullptr;
    auto const* nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(
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
    auto const* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (!section->SizeOfRawData)
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

bool RedirectOriginalFree(std::uint8_t* image)
{
    auto* const jump = image + (kFreeTailJump - kImageBase);
    if (jump[0] != 0xE9)
        return false;
    std::int32_t old_relative = 0;
    std::memcpy(&old_relative, jump + 1, sizeof(old_relative));
    if (static_cast<std::int64_t>(kFreeTailJump) + 5 + old_relative !=
        kOriginalFree)
        return false;
    auto const replacement = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(&_free) -
        reinterpret_cast<std::uintptr_t>(jump + 5));
    std::memcpy(jump + 1, &replacement, sizeof(replacement));
    return true;
}
} // namespace

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "Run this harness as PE32/x86.");
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <ImVehFt.asi>\n");
        return 2;
    }
    auto* const reference = MapReference(argv[1]);
    if (!reference || !RedirectOriginalFree(reference))
    {
        std::fprintf(stderr, "Could not map reference or verify free tail-jump.\n");
        return 3;
    }

    constexpr std::uint32_t kCases = 512;
    for (std::uint32_t i = 0; i < kCases; ++i)
    {
        std::uint32_t const pointer = 0x82000000u ^ (i * 0x1021u);
        Invocation original{}, candidate{};
        g_free_count = 0;
        InvokeRaw(kEntry, pointer, &original);
        auto const original_count = g_free_count;
        auto const original_pointer = g_freed_pointer;
        g_free_count = 0;
        InvokeRaw(static_cast<std::uint32_t>(
                      reinterpret_cast<std::uintptr_t>(FUN_1001074b)),
                  pointer, &candidate);
        if (g_free_count != 1 || original_count != 1 ||
            g_freed_pointer != original_pointer ||
            original_pointer != pointer ||
            original.esp_after_call != candidate.esp_after_call ||
            original.esp_after_caller_cleanup !=
                candidate.esp_after_caller_cleanup ||
            original.esp_after_call != -4 ||
            original.esp_after_caller_cleanup != 0)
        {
            std::fprintf(stderr, "Differential mismatch at case %u.\n", i);
            return 4;
        }
    }
    std::printf("PASS: %u mapped-original/candidate calls; freed pointer, caller-cleanup ESP delta, and final caller stack matched.\n",
                kCases);
    std::puts("LIMIT: _free was replaced by a test recorder; real heap behavior was not exercised.");
    return 0;
}
