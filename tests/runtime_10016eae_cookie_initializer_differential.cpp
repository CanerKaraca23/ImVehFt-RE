#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <cstring>

#pragma comment(lib, "kernel32.lib")

extern "C" void __cdecl ___security_init_cookie(void);
extern "C" DWORD DAT_10029490 = 0;
extern "C" DWORD DAT_10029494 = 0;

namespace
{
constexpr DWORD kImageBase = 0x10000000;
constexpr DWORD kInitializer = 0x10016eae;
constexpr DWORD kCookieAddress = 0x10029490;
constexpr DWORD kComplementAddress = 0x10029494;
constexpr DWORD kGetSystemTimeAsFileTimeIat = 0x10022108;
constexpr DWORD kGetCurrentProcessIdIat = 0x10022104;
constexpr DWORD kGetCurrentThreadIdIat = 0x10022064;
constexpr DWORD kGetTickCountIat = 0x10022100;
constexpr DWORD kQueryPerformanceCounterIat = 0x100220fc;

struct ApiValues
{
    DWORD filetime_low;
    DWORD filetime_high;
    DWORD process_id;
    DWORD thread_id;
    DWORD tick_count;
    DWORD qpc_low;
    DWORD qpc_high;
    char trace[16];
    DWORD trace_length;
};

ApiValues g_api{};
std::uint8_t* g_original = nullptr;

void Record(char event)
{
    if (g_api.trace_length < sizeof(g_api.trace))
        g_api.trace[g_api.trace_length++] = event;
}

void WINAPI StubGetSystemTimeAsFileTime(LPFILETIME value)
{
    Record('G');
    value->dwLowDateTime = g_api.filetime_low;
    value->dwHighDateTime = g_api.filetime_high;
}

DWORD WINAPI StubGetCurrentProcessId()
{
    Record('P');
    return g_api.process_id;
}

DWORD WINAPI StubGetCurrentThreadId()
{
    Record('T');
    return g_api.thread_id;
}

DWORD WINAPI StubGetTickCount()
{
    Record('K');
    return g_api.tick_count;
}

BOOL WINAPI StubQueryPerformanceCounter(PLARGE_INTEGER value)
{
    Record('Q');
    value->LowPart = g_api.qpc_low;
    value->HighPart = static_cast<LONG>(g_api.qpc_high);
    return TRUE;
}

std::uint8_t* MapOriginal(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return nullptr;
    const DWORD size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    auto* bytes = new std::uint8_t[size];
    DWORD read = 0;
    const BOOL ok = ReadFile(file, bytes, size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size)
    {
        delete[] bytes;
        return nullptr;
    }
    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
    {
        delete[] bytes;
        return nullptr;
    }
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(bytes + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase)
    {
        delete[] bytes;
        return nullptr;
    }
    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kImageBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kImageBase)))
    {
        delete[] bytes;
        return nullptr;
    }
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes, nt->OptionalHeader.SizeOfHeaders);
    auto* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (!section->SizeOfRawData) continue;
        if (section->PointerToRawData > size ||
            section->SizeOfRawData > size - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData > nt->OptionalHeader.SizeOfImage - section->VirtualAddress)
        {
            VirtualFree(image, 0, MEM_RELEASE);
            delete[] bytes;
            return nullptr;
        }
        std::memcpy(image + section->VirtualAddress,
                    bytes + section->PointerToRawData, section->SizeOfRawData);
    }
    delete[] bytes;
    return image;
}

bool WritePointer(DWORD address, const void* value)
{
    DWORD old_protection = 0;
    auto* slot = reinterpret_cast<void**>(static_cast<std::uintptr_t>(address));
    if (!VirtualProtect(slot, sizeof(*slot), PAGE_READWRITE, &old_protection)) return false;
    *slot = const_cast<void*>(value);
    DWORD ignored = 0;
    VirtualProtect(slot, sizeof(*slot), old_protection, &ignored);
    return true;
}

bool PatchOriginalImports()
{
    return WritePointer(kGetSystemTimeAsFileTimeIat,
                        reinterpret_cast<const void*>(&StubGetSystemTimeAsFileTime)) &&
           WritePointer(kGetCurrentProcessIdIat,
                        reinterpret_cast<const void*>(&StubGetCurrentProcessId)) &&
           WritePointer(kGetCurrentThreadIdIat,
                        reinterpret_cast<const void*>(&StubGetCurrentThreadId)) &&
           WritePointer(kGetTickCountIat,
                        reinterpret_cast<const void*>(&StubGetTickCount)) &&
           WritePointer(kQueryPerformanceCounterIat,
                        reinterpret_cast<const void*>(&StubQueryPerformanceCounter));
}

bool PatchCurrentExecutableImports()
{
    auto* image = reinterpret_cast<std::uint8_t*>(GetModuleHandleW(nullptr));
    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(image);
    if (!image || dos->e_magic != IMAGE_DOS_SIGNATURE) return false;
    auto* nt = reinterpret_cast<IMAGE_NT_HEADERS32*>(image + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386) return false;
    const auto directory = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!directory.VirtualAddress || !directory.Size) return false;
    auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(image + directory.VirtualAddress);
    bool seen[5]{};
    for (; descriptor->Name; ++descriptor)
    {
        auto* names = reinterpret_cast<IMAGE_THUNK_DATA32*>(
            image + (descriptor->OriginalFirstThunk ? descriptor->OriginalFirstThunk
                                                    : descriptor->FirstThunk));
        auto* slots = reinterpret_cast<IMAGE_THUNK_DATA32*>(image + descriptor->FirstThunk);
        for (; names->u1.AddressOfData; ++names, ++slots)
        {
            if (IMAGE_SNAP_BY_ORDINAL32(names->u1.Ordinal)) continue;
            const auto* imported = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                image + names->u1.AddressOfData);
            const char* name = reinterpret_cast<const char*>(imported->Name);
            const void* stub = nullptr;
            unsigned which = 0;
            if (std::strcmp(name, "GetSystemTimeAsFileTime") == 0)
            { stub = reinterpret_cast<const void*>(&StubGetSystemTimeAsFileTime); which = 0; }
            else if (std::strcmp(name, "GetCurrentProcessId") == 0)
            { stub = reinterpret_cast<const void*>(&StubGetCurrentProcessId); which = 1; }
            else if (std::strcmp(name, "GetCurrentThreadId") == 0)
            { stub = reinterpret_cast<const void*>(&StubGetCurrentThreadId); which = 2; }
            else if (std::strcmp(name, "GetTickCount") == 0)
            { stub = reinterpret_cast<const void*>(&StubGetTickCount); which = 3; }
            else if (std::strcmp(name, "QueryPerformanceCounter") == 0)
            { stub = reinterpret_cast<const void*>(&StubQueryPerformanceCounter); which = 4; }
            if (!stub) continue;
            if (!WritePointer(static_cast<DWORD>(reinterpret_cast<std::uintptr_t>(slots)), stub))
                return false;
            seen[which] = true;
        }
    }
    for (bool present : seen) if (!present) return false;
    return true;
}

bool RunCase(DWORD seed, ApiValues values, unsigned case_id)
{
    auto* original_cookie = reinterpret_cast<DWORD*>(
        static_cast<std::uintptr_t>(kCookieAddress));
    auto* original_complement = reinterpret_cast<DWORD*>(
        static_cast<std::uintptr_t>(kComplementAddress));
    *original_cookie = seed;
    *original_complement = 0x13579BDF;
    DAT_10029490 = seed;
    DAT_10029494 = 0x13579BDF;
    values.trace_length = 0;
    std::memset(values.trace, 0, sizeof(values.trace));
    g_api = values;

    reinterpret_cast<void(__cdecl*)(void)>(
        static_cast<std::uintptr_t>(kInitializer))();
    const DWORD old_cookie = *original_cookie;
    const DWORD old_complement = *original_complement;
    const ApiValues old_api = g_api;

    DAT_10029490 = seed;
    DAT_10029494 = 0x13579BDF;
    values.trace_length = 0;
    std::memset(values.trace, 0, sizeof(values.trace));
    g_api = values;
    ___security_init_cookie();
    const bool matches = old_cookie == DAT_10029490 &&
        old_complement == DAT_10029494 &&
        old_api.trace_length == g_api.trace_length &&
        std::memcmp(old_api.trace, g_api.trace, sizeof(g_api.trace)) == 0;
    if (!matches)
    {
        (void)case_id;
        return false;
    }
    return true;
}
} // namespace

int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    g_original = MapOriginal(argv[1]);
    if (!g_original || !PatchOriginalImports() || !PatchCurrentExecutableImports()) return 3;

    ApiValues ordinary{0x10203040, 0x50607080, 0x11223344, 0x55667788,
                       0x99AABBCC, 0xDDEEFF01, 0x23456789, {}, 0};
    ApiValues default_cookie{0, 0, 0, 0, 0, 0xBB40E64E, 0, {}, 0};
    ApiValues low_cookie{0, 0, 0, 0, 0, 0x00001234, 0, {}, 0};
    const bool passed =
        RunCase(0xBB40E64E, ordinary, 0) &&
        RunCase(0x00001234, ordinary, 1) &&
        RunCase(0x00000000, ordinary, 2) &&
        RunCase(0x0000FFFF, low_cookie, 3) &&
        RunCase(0xBB40E64E, default_cookie, 4) &&
        RunCase(0x12345678, ordinary, 5) &&
        RunCase(0xBB40E64F, ordinary, 6);
    VirtualFree(g_original, 0, MEM_RELEASE);
    if (!passed) return 1;
    static constexpr char message[] =
        "PASS: 0x10016eae original-vs-candidate matched 7 deterministic cookie cases.\r\n";
    DWORD written = 0;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), message, sizeof(message) - 1, &written, nullptr);
    return 0;
}
