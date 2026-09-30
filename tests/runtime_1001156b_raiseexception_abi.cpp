#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" void __stdcall __CxxThrowException_8(
    unsigned long, unsigned char*);

unsigned long DAT_1002226c[8]{};

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kEntry = 0x1001156b;
constexpr std::uint32_t kRaiseExceptionIat = 0x1002206c;

struct RaiseRecord
{
    std::uint32_t count;
    std::uint32_t code;
    std::uint32_t flags;
    std::uint32_t number_of_arguments;
    std::uint32_t arguments[3];
};

struct Invocation
{
    std::int32_t esp_delta;
};

RaiseRecord g_raise{};
volatile std::uint32_t g_esp_before = 0;

extern "C" void __stdcall TestRaiseException(
    std::uint32_t code, std::uint32_t flags, std::uint32_t number_of_arguments,
    std::uint32_t* arguments)
{
    ++g_raise.count;
    g_raise.code = code;
    g_raise.flags = flags;
    g_raise.number_of_arguments = number_of_arguments;
    for (unsigned i = 0; i < 3; ++i)
        g_raise.arguments[i] = arguments[i];
}

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, std::uint32_t, std::uint32_t, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ecx], edx
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

bool PatchImport(HMODULE module, char const* function_name, void* replacement)
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
                            function_name) != 0)
                continue;
            DWORD old_protection = 0;
            if (!VirtualProtect(&addresses->u1.Function,
                                sizeof(addresses->u1.Function), PAGE_READWRITE,
                                &old_protection))
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
    auto* const original_iat = reinterpret_cast<std::uint32_t*>(
        reference + (kRaiseExceptionIat - kImageBase));
    *original_iat = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestRaiseException));
    if (!PatchImport(GetModuleHandleW(nullptr), "RaiseException",
                     reinterpret_cast<void*>(&TestRaiseException)))
    {
        std::fprintf(stderr, "Could not redirect candidate RaiseException import.\n");
        return 4;
    }
    std::memcpy(DAT_1002226c,
                reference + (0x1002226c - kImageBase), sizeof(DAT_1002226c));

    constexpr std::uint32_t kCases = 512;
    for (std::uint32_t i = 0; i < kCases; ++i)
    {
        unsigned char attributes = (i & 1u) ? 8 : 0;
        std::uint32_t const object = 0x81230000u ^ (i * 0x1009u);
        RaiseRecord const empty{};
        g_raise = empty;
        Invocation original{};
        InvokeRaw(kEntry, object,
                  static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&attributes)),
                  &original);
        RaiseRecord const original_record = g_raise;

        g_raise = empty;
        Invocation candidate{};
        InvokeRaw(static_cast<std::uint32_t>(
                      reinterpret_cast<std::uintptr_t>(__CxxThrowException_8)),
                  object,
                  static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&attributes)),
                  &candidate);
        if (g_raise.count != 1 || original_record.count != 1 ||
            std::memcmp(&original_record.code, &g_raise.code,
                        sizeof(RaiseRecord) - offsetof(RaiseRecord, code)) != 0 ||
            original.esp_delta != candidate.esp_delta ||
            original.esp_delta != 0)
        {
            std::fprintf(stderr, "Differential mismatch at case %u.\n", i);
            return 5;
        }
    }
    std::printf("PASS: %u mapped-original/candidate RaiseException-return cases; exception tuple/payload and RET 8 stack cleanup matched.\n",
                kCases);
    std::puts("LIMIT: RaiseException was replaced by a recorder; actual SEH dispatch and C++ unwinding were not exercised.");
    return 0;
}
