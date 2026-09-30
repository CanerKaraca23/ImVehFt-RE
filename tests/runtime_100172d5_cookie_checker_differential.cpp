#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <cstring>

extern "C" std::uintptr_t DAT_10029490 = 0;
extern "C" void __cdecl ___report_gsfailure();
void __fastcall __security_check_cookie(std::uintptr_t);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kChecker = 0x100172d5;
constexpr std::uint32_t kReportFailure = 0x1001ae25;
constexpr std::uint32_t kCookie = 0x10029490;
int g_report_failure_calls = 0;

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

bool PatchJump(std::uint32_t source, const void* target)
{
    auto* site = reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(source));
    const auto destination = reinterpret_cast<std::uintptr_t>(target);
    const auto displacement = static_cast<std::int32_t>(destination - (source + 5u));
    DWORD old_protection = 0;
    if (!VirtualProtect(site, 5, PAGE_EXECUTE_READWRITE, &old_protection)) return false;
    site[0] = 0xE9;
    std::memcpy(site + 1, &displacement, sizeof(displacement));
    FlushInstructionCache(GetCurrentProcess(), site, 5);
    DWORD ignored = 0;
    VirtualProtect(site, 5, old_protection, &ignored);
    return true;
}

void Check(std::uintptr_t cookie, bool candidate)
{
    if (candidate)
        __security_check_cookie(cookie);
    else
        reinterpret_cast<void(__fastcall*)(std::uintptr_t)>(
            static_cast<std::uintptr_t>(kChecker))(cookie);
}

bool RunCase(std::uint32_t saved_cookie, std::uint32_t supplied_cookie)
{
    *reinterpret_cast<std::uint32_t*>(static_cast<std::uintptr_t>(kCookie)) = saved_cookie;
    DAT_10029490 = saved_cookie;
    g_report_failure_calls = 0;
    Check(supplied_cookie, false);
    const int original_failures = g_report_failure_calls;
    DAT_10029490 = saved_cookie;
    g_report_failure_calls = 0;
    Check(supplied_cookie, true);
    const int candidate_failures = g_report_failure_calls;
    const int expected_failures = supplied_cookie == saved_cookie ? 0 : 1;
    return original_failures == candidate_failures && original_failures == expected_failures;
}
} // namespace

extern "C" void __cdecl ___report_gsfailure()
{
    ++g_report_failure_calls;
}

int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    auto* image = MapOriginal(argv[1]);
    if (!image || !PatchJump(kReportFailure, reinterpret_cast<const void*>(&___report_gsfailure)))
        return 3;
    constexpr std::uint32_t cookies[] = {0, 0xBB40E64E, 0xBB40E64F, 0x12345678, 0x87654321};
    for (const auto saved : cookies)
    {
        for (const auto supplied : cookies)
        {
            if (!RunCase(saved, supplied))
            {
                VirtualFree(image, 0, MEM_RELEASE);
                return 1;
            }
        }
    }
    VirtualFree(image, 0, MEM_RELEASE);
    static constexpr char message[] =
        "PASS: 0x100172d5 original-vs-candidate matched 25 cookie-check cases.\r\n";
    DWORD written = 0;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), message, sizeof(message) - 1, &written, nullptr);
    return 0;
}
