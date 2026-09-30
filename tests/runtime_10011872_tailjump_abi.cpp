#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" void __stdcall FUN_10011872(
    wchar_t*, wchar_t*, wchar_t*, std::uint32_t, std::uintptr_t);

std::uint32_t DAT_10039a04 = 0;

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kEntry = 0x10011872;
constexpr std::uint32_t kDecodePointerIat = 0x10022060;

struct Invocation
{
    std::uint32_t eax;
    std::int32_t esp_delta;
};

std::uint32_t g_decoded = 0;
std::uint32_t g_decode_argument = 0;
std::uint32_t g_dispatch_args[5]{};
std::uint32_t g_dispatch_count = 0;
volatile std::uint32_t g_esp_before = 0;

int ReportException(EXCEPTION_POINTERS* exception, char const* side)
{
    std::fprintf(stderr, "%s exception 0x%08lx at %p\n", side,
                 exception->ExceptionRecord->ExceptionCode,
                 exception->ExceptionRecord->ExceptionAddress);
    return EXCEPTION_EXECUTE_HANDLER;
}

extern "C" void* __stdcall TestDecodePointer(void* encoded)
{
    g_decode_argument = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(encoded));
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(g_decoded));
}
extern "C" __declspec(noreturn) void __cdecl __invoke_watson(
    wchar_t*, wchar_t*, wchar_t*, std::uint32_t, std::uintptr_t)
{
    ExitProcess(0xE1);
}

extern "C" std::uint32_t __stdcall DispatchDecoded(
    std::uint32_t a, std::uint32_t b, std::uint32_t c,
    std::uint32_t d, std::uint32_t e)
{
    g_dispatch_args[0] = a;
    g_dispatch_args[1] = b;
    g_dispatch_args[2] = c;
    g_dispatch_args[3] = d;
    g_dispatch_args[4] = e;
    ++g_dispatch_count;
    return a ^ (b << 1) ^ (c >> 1) ^ d ^ (e * 0x45D9F3Bu);
}

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        push esi
        push edi
        push dword ptr [ebp + 1Ch]
        push dword ptr [ebp + 18h]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        mov dword ptr [g_esp_before], esp
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, dword ptr [ebp + 20h]
        mov dword ptr [edx], eax
        mov ecx, esp
        sub ecx, dword ptr [g_esp_before]
        mov dword ptr [edx + 4], ecx
        pop edi
        pop esi
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

bool PatchDecodePointerImport(HMODULE module, void* replacement)
{
    auto* const base = reinterpret_cast<std::uint8_t*>(module);
    auto* const dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    auto* const nt = reinterpret_cast<IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
    auto const directory = nt->OptionalHeader
        .DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (directory.VirtualAddress == 0)
        return false;
    auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(
        base + directory.VirtualAddress);
    for (; descriptor->Name != 0; ++descriptor)
    {
        auto* names = reinterpret_cast<IMAGE_THUNK_DATA32*>(
            base + (descriptor->OriginalFirstThunk
                        ? descriptor->OriginalFirstThunk
                        : descriptor->FirstThunk));
        auto* addresses = reinterpret_cast<IMAGE_THUNK_DATA32*>(
            base + descriptor->FirstThunk);
        for (; names->u1.AddressOfData != 0; ++names, ++addresses)
        {
            if (IMAGE_SNAP_BY_ORDINAL32(names->u1.Ordinal))
                continue;
            auto const* imported = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                base + names->u1.AddressOfData);
            if (std::strcmp(reinterpret_cast<char const*>(imported->Name),
                            "DecodePointer") != 0)
                continue;
            DWORD old_protection = 0;
            if (!VirtualProtect(&addresses->u1.Function,
                                sizeof(addresses->u1.Function),
                                PAGE_READWRITE, &old_protection))
                return false;
            addresses->u1.Function = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(replacement));
            DWORD ignored = 0;
            VirtualProtect(&addresses->u1.Function,
                           sizeof(addresses->u1.Function), old_protection,
                           &ignored);
            return true;
        }
    }
    return false;
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
    if (!reference)
    {
        std::fprintf(stderr, "Could not map reference ASI at preferred base.\n");
        return 3;
    }
    auto* const iat_slot = reinterpret_cast<std::uint32_t*>(
        reference + (kDecodePointerIat - kImageBase));
    *iat_slot = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestDecodePointer));
    if (!PatchDecodePointerImport(GetModuleHandleW(nullptr),
                                  reinterpret_cast<void*>(&TestDecodePointer)))
    {
        std::fprintf(stderr, "Could not redirect candidate DecodePointer import.\n");
        return 4;
    }
    DAT_10039a04 = *reinterpret_cast<std::uint32_t*>(
        reference + (0x10039A04 - kImageBase));
    g_decoded = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&DispatchDecoded));

    constexpr std::uint32_t kCases = 512;
    for (std::uint32_t i = 0; i < kCases; ++i)
    {
        std::uint32_t const args[5] = {
            0x00410000u + i, 0x11223344u ^ (i * 11u),
            0xAABBCCDDu + (i * 17u), 0x7F000000u ^ (i * 43u),
            0xE0001000u + (i * 97u)};
        Invocation original{}, candidate{};
        g_dispatch_count = 0;
        __try {
            InvokeRaw(kEntry, args[0], args[1], args[2], args[3], args[4],
                      &original);
        } __except (ReportException(GetExceptionInformation(), "original")) {
            return 6;
        }
        std::uint32_t const original_decode_argument = g_decode_argument;
        std::uint32_t const original_args[5] = {
            g_dispatch_args[0], g_dispatch_args[1], g_dispatch_args[2],
            g_dispatch_args[3], g_dispatch_args[4]};
        if (g_dispatch_count != 1)
        {
            std::fprintf(stderr, "Original dispatch count mismatch: %u\n", i);
            return 4;
        }

        g_dispatch_count = 0;
        __try {
            InvokeRaw(static_cast<std::uint32_t>(
                          reinterpret_cast<std::uintptr_t>(FUN_10011872)),
                      args[0], args[1], args[2], args[3], args[4], &candidate);
        } __except (ReportException(GetExceptionInformation(), "candidate")) {
            return 7;
        }
        if (g_dispatch_count != 1 || original.eax != candidate.eax ||
            original.esp_delta != candidate.esp_delta ||
            original_decode_argument != g_decode_argument ||
            std::memcmp(original_args, g_dispatch_args,
                        sizeof(original_args)) != 0)
        {
            std::fprintf(stderr, "Original/candidate mismatch at case %u.\n", i);
            return 5;
        }
    }

    std::printf("PASS: %u mapped-original/candidate decoded-handler calls; five stack arguments, return value, and ESP delta matched.\n",
                kCases);
    std::puts("LIMIT: DecodePointer and decoded handler were test stubs; Watson fallback and real process callback effects were not exercised.");
    return 0;
}
