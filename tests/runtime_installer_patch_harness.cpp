#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <array>

using DWORD = std::uint32_t;
using UINT = std::uint32_t;
using BOOL = int;
using LPCSTR = const char*;
using LPVOID = void*;
using LPDWORD = DWORD*;
using HANDLE = void*;

#pragma section(".gta", read, write)
__declspec(allocate(".gta")) std::uint8_t g_synthetic_gta_image[0x450000] = {};
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(
    LPCSTR, DWORD, DWORD, LPVOID, DWORD, DWORD, HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE, LPDWORD);
extern "C" __declspec(dllimport) BOOL __stdcall ReadFile(
    HANDLE, LPVOID, DWORD, LPDWORD, LPVOID);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) LPVOID __stdcall VirtualAlloc(
    LPVOID, std::size_t, DWORD, DWORD);
extern "C" __declspec(dllimport) BOOL __stdcall VirtualFree(
    LPVOID, std::size_t, DWORD);
#pragma comment(lib, "kernel32.lib")

void __stdcall FUN_10002210();

extern "C" {
void __cdecl FUN_100014c0(char*);
void __fastcall FUN_1000a560(int);
int __stdcall FUN_1000a4f0();
void __stdcall FUN_10001770();
void __stdcall FUN_10001e80();
std::uint32_t __stdcall FUN_1000a800(std::uintptr_t, std::uintptr_t);
int* __cdecl FUN_100076d0(int*, int*);
std::uint32_t __fastcall FUN_10008b70(int);
std::uint32_t __cdecl FUN_10008cb0(std::uint32_t, std::uint32_t);
void __cdecl FUN_10008da0(std::uint32_t, std::uint32_t*);
void __cdecl FUN_10008dd0(std::uint32_t, int);

std::uint8_t IVF_RELOC_TARGET_1003AEF1;
std::uint8_t IVF_RELOC_TARGET_1003A6C7;
std::uint8_t IVF_RELOC_TARGET_1003AED8;
std::uint8_t IVF_RELOC_TARGET_1003BC70;
std::uint8_t IVF_RELOC_TARGET_1003BC04;
std::uint8_t IVF_RELOC_TARGET_1003BC24;
std::uint8_t IVF_RELOC_TARGET_1003BC0C;
std::uint8_t IVF_RELOC_TARGET_1003BBBC;
std::uint8_t IVF_RELOC_TARGET_1003B6FC;
std::uint8_t IVF_RELOC_TARGET_1003BC74;
std::uint8_t IVF_RELOC_TARGET_1003C248;
std::uint8_t IVF_RELOC_TARGET_1003A6C8[0x200];
std::uint8_t IVF_RELOC_TARGET_1003A8C8[0x200];

#define IVF_INSTALLER_TARGET(address) \
    void __cdecl IVF_INSTALL_TARGET_##address() {}
IVF_INSTALLER_TARGET(10003030)
IVF_INSTALLER_TARGET(10003060)
IVF_INSTALLER_TARGET(10003080)
IVF_INSTALLER_TARGET(100031E0)
IVF_INSTALLER_TARGET(10003340)
IVF_INSTALLER_TARGET(10003400)
IVF_INSTALLER_TARGET(10003660)
IVF_INSTALLER_TARGET(10003E40)
IVF_INSTALLER_TARGET(10003F40)
IVF_INSTALLER_TARGET(100042C0)
IVF_INSTALLER_TARGET(10004B10)
IVF_INSTALLER_TARGET(100050E0)
IVF_INSTALLER_TARGET(100074D0)
IVF_INSTALLER_TARGET(10007F50)
IVF_INSTALLER_TARGET(10007F70)
IVF_INSTALLER_TARGET(10007F90)
IVF_INSTALLER_TARGET(10008140)
IVF_INSTALLER_TARGET(10008780)
IVF_INSTALLER_TARGET(10008830)
IVF_INSTALLER_TARGET(10008940)
#undef IVF_INSTALLER_TARGET
}

namespace {

int g_dispatch_calls = 0;
constexpr std::array<std::uintptr_t, 15> kGtaPatchPages = {
    0x004C8000, 0x004C9000, 0x0053B000, 0x005B8000, 0x005D5000,
    0x006A2000, 0x006AB000, 0x006BD000, 0x006D6000, 0x006E0000,
    0x006E1000, 0x006E2000, 0x006F3000, 0x006FD000, 0x0085C000,
};

struct Hook {
    std::uintptr_t opcode;
    std::uint8_t patchedOpcode;
    void(__cdecl* wrapper)();
};

const Hook kHooks[] = {
    {0x006D6617, 0xE8, &IVF_INSTALL_TARGET_100074D0},
    {0x005B8FFD, 0xE8, &IVF_INSTALL_TARGET_10008140},
    {0x006D6494, 0xE8, &IVF_INSTALL_TARGET_100050E0},
    {0x0053BFCC, 0xE8, &IVF_INSTALL_TARGET_10004B10},
    {0x006D6A58, 0xE8, &IVF_INSTALL_TARGET_100042C0},
    {0x005D5BC7, 0xE9, &IVF_INSTALL_TARGET_10008780},
    {0x005D5C1E, 0xE9, &IVF_INSTALL_TARGET_10008830},
    {0x005D5AD1, 0xE9, &IVF_INSTALL_TARGET_10008940},
    {0x006E198E, 0xE9, &IVF_INSTALL_TARGET_10007F90},
    {0x006E18DA, 0xE9, &IVF_INSTALL_TARGET_10007F50},
    {0x006E1A2D, 0xE9, &IVF_INSTALL_TARGET_10007F70},
    {0x006FDED6, 0xE8, &IVF_INSTALL_TARGET_10003E40},
    {0x006FDF10, 0xE8, &IVF_INSTALL_TARGET_10003F40},
    {0x006AB350, 0xE9, &IVF_INSTALL_TARGET_10003030},
    {0x006F3AED, 0xE8, &IVF_INSTALL_TARGET_10003060},
    {0x006F3973, 0xE8, &IVF_INSTALL_TARGET_10003080},
    {0x006E174B, 0xE8, &IVF_INSTALL_TARGET_10003400},
    {0x006E175E, 0xE8, &IVF_INSTALL_TARGET_10003400},
    {0x006E173C, 0xE8, &IVF_INSTALL_TARGET_10003660},
    {0x006E1773, 0xE8, &IVF_INSTALL_TARGET_10003660},
    {0x006E27E6, 0xE9, &IVF_INSTALL_TARGET_100031E0},
    {0x006E0DF7, 0xE8, &IVF_INSTALL_TARGET_10003340},
};

bool check_pointer_patch(std::uintptr_t slot, const void* expected)
{
    const auto actual = *reinterpret_cast<const std::uint32_t*>(slot);
    const auto expected32 = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(expected));
    if (actual != expected32)
    {
        std::fprintf(stderr, "pointer patch mismatch at 0x%08lX\n",
            static_cast<unsigned long>(slot));
        return false;
    }
    return true;
}

bool read_u16(const std::uint8_t* bytes, std::size_t size, std::size_t offset,
    std::uint16_t& value)
{
    if (offset > size || size - offset < 2) return false;
    value = static_cast<std::uint16_t>(bytes[offset]) |
        static_cast<std::uint16_t>(static_cast<std::uint16_t>(bytes[offset + 1]) << 8);
    return true;
}

bool read_u32(const std::uint8_t* bytes, std::size_t size, std::size_t offset,
    std::uint32_t& value)
{
    if (offset > size || size - offset < 4) return false;
    value = static_cast<std::uint32_t>(bytes[offset]) |
        (static_cast<std::uint32_t>(bytes[offset + 1]) << 8) |
        (static_cast<std::uint32_t>(bytes[offset + 2]) << 16) |
        (static_cast<std::uint32_t>(bytes[offset + 3]) << 24);
    return true;
}

bool copy_pe_page(const std::uint8_t* fileBytes, std::size_t fileSize,
    std::uint32_t peOffset, std::uint32_t sectionTable, std::uint16_t sectionCount,
    std::uint32_t sizeOfHeaders, std::uintptr_t pageAddress)
{
    constexpr std::size_t kPageSize = 0x1000;
    constexpr std::uintptr_t kPreferredImageBase = 0x00400000;
    auto* const destination = reinterpret_cast<std::uint8_t*>(pageAddress);
    const auto pageRva = static_cast<std::uint32_t>(pageAddress - kPreferredImageBase);
    std::memset(destination, 0, kPageSize);

    std::size_t offset = 0;
    while (offset < kPageSize)
    {
        const auto currentRva = pageRva + static_cast<std::uint32_t>(offset);
        std::uint32_t fileOffset = 0;
        std::size_t available = kPageSize - offset;
        bool fileBacked = false;
        if (currentRva < sizeOfHeaders)
        {
            fileOffset = currentRva;
            available = (sizeOfHeaders - currentRva < available)
                ? sizeOfHeaders - currentRva : available;
            fileBacked = true;
        }
        else
        {
            for (std::uint16_t i = 0; i < sectionCount; ++i)
            {
                const auto sectionOffset = static_cast<std::size_t>(sectionTable) +
                    static_cast<std::size_t>(i) * 40;
                std::uint32_t virtualSize = 0;
                std::uint32_t virtualAddress = 0;
                std::uint32_t rawSize = 0;
                std::uint32_t rawOffset = 0;
                if (!read_u32(fileBytes, fileSize, sectionOffset + 8, virtualSize) ||
                    !read_u32(fileBytes, fileSize, sectionOffset + 12, virtualAddress) ||
                    !read_u32(fileBytes, fileSize, sectionOffset + 16, rawSize) ||
                    !read_u32(fileBytes, fileSize, sectionOffset + 20, rawOffset))
                {
                    return false;
                }
                const auto sectionExtent = virtualSize > rawSize ? virtualSize : rawSize;
                if (currentRva < virtualAddress ||
                    currentRva - virtualAddress >= sectionExtent)
                {
                    continue;
                }
                const auto delta = currentRva - virtualAddress;
                const auto sectionAvailable = sectionExtent - delta;
                if (sectionAvailable < available) available = sectionAvailable;
                if (delta < rawSize)
                {
                    fileOffset = rawOffset + delta;
                    const auto rawAvailable = rawSize - delta;
                    if (rawAvailable < available) available = rawAvailable;
                    fileBacked = true;
                }
                break;
            }
        }

        if (available == 0) return false;
        if (fileBacked)
        {
            if (fileOffset > fileSize || fileSize - fileOffset < available) return false;
            std::memcpy(destination + offset, fileBytes + fileOffset, available);
        }
        offset += available;
    }
    (void)peOffset;
    return true;
}

bool load_gta_patch_pages(const char* path)
{
    constexpr DWORD kGenericRead = 0x80000000;
    constexpr DWORD kFileShareRead = 1;
    constexpr DWORD kOpenExisting = 3;
    constexpr DWORD kFileAttributeNormal = 0x80;
    constexpr DWORD kMemCommitReserve = 0x3000;
    constexpr DWORD kPageReadWrite = 0x04;
    constexpr std::uint32_t kPeSignature = 0x00004550;
    constexpr std::uint16_t kI386 = 0x014C;
    constexpr std::uint16_t kPe32 = 0x010B;
    constexpr std::uint32_t kImageBase = 0x00400000;
    constexpr std::uint32_t kRequiredImageSize = 0x0085D000 - kImageBase;

    const auto file = CreateFileA(path, kGenericRead, kFileShareRead, nullptr,
        kOpenExisting, kFileAttributeNormal, nullptr);
    if (file == reinterpret_cast<HANDLE>(static_cast<std::intptr_t>(-1)))
    {
        std::fprintf(stderr, "could not open GTA executable: %s\n", path);
        return false;
    }
    const auto fileSize = GetFileSize(file, nullptr);
    if (fileSize == 0xFFFFFFFFu || fileSize < 0x100)
    {
        CloseHandle(file);
        std::fprintf(stderr, "invalid GTA executable size: %lu\n",
            static_cast<unsigned long>(fileSize));
        return false;
    }
    auto* const bytes = static_cast<std::uint8_t*>(VirtualAlloc(nullptr, fileSize,
        kMemCommitReserve, kPageReadWrite));
    if (bytes == nullptr)
    {
        CloseHandle(file);
        std::fprintf(stderr, "could not allocate read-only source buffer for GTA PE\n");
        return false;
    }
    DWORD bytesRead = 0;
    const auto readSucceeded = ReadFile(file, bytes, fileSize, &bytesRead, nullptr);
    CloseHandle(file);
    if (!readSucceeded || bytesRead != fileSize)
    {
        VirtualFree(bytes, 0, 0x8000);
        std::fprintf(stderr, "could not read complete GTA executable\n");
        return false;
    }

    std::uint32_t peOffset = 0;
    std::uint32_t signature = 0;
    std::uint16_t machine = 0;
    std::uint16_t sectionCount = 0;
    std::uint16_t optionalSize = 0;
    if (!read_u32(bytes, fileSize, 0x3C, peOffset) ||
        !read_u32(bytes, fileSize, peOffset, signature) ||
        !read_u16(bytes, fileSize, peOffset + 4, machine) ||
        !read_u16(bytes, fileSize, peOffset + 6, sectionCount) ||
        !read_u16(bytes, fileSize, peOffset + 20, optionalSize))
    {
        VirtualFree(bytes, 0, 0x8000);
        std::fprintf(stderr, "truncated GTA PE headers\n");
        return false;
    }
    const auto optional = static_cast<std::size_t>(peOffset) + 24;
    std::uint16_t optionalMagic = 0;
    std::uint32_t imageBase = 0;
    std::uint32_t sizeOfImage = 0;
    std::uint32_t sizeOfHeaders = 0;
    if (signature != kPeSignature || machine != kI386 ||
        optionalSize < 64 ||
        !read_u16(bytes, fileSize, optional, optionalMagic) ||
        !read_u32(bytes, fileSize, optional + 28, imageBase) ||
        !read_u32(bytes, fileSize, optional + 56, sizeOfImage) ||
        !read_u32(bytes, fileSize, optional + 60, sizeOfHeaders) ||
        optionalMagic != kPe32 || imageBase != kImageBase ||
        sizeOfImage < kRequiredImageSize)
    {
        VirtualFree(bytes, 0, 0x8000);
        std::fprintf(stderr, "GTA PE architecture/base/image-size mismatch\n");
        return false;
    }
    const auto sectionTable = static_cast<std::uint32_t>(optional + optionalSize);
    if (static_cast<std::size_t>(sectionTable) +
        static_cast<std::size_t>(sectionCount) * 40 > fileSize)
    {
        VirtualFree(bytes, 0, 0x8000);
        std::fprintf(stderr, "truncated GTA PE section table\n");
        return false;
    }
    const auto sectionBegin = reinterpret_cast<std::uintptr_t>(g_synthetic_gta_image);
    const auto sectionEnd = sectionBegin + sizeof(g_synthetic_gta_image);
    for (std::uintptr_t page : kGtaPatchPages)
    {
        if (page < sectionBegin || page + 0x1000 > sectionEnd)
        {
            VirtualFree(bytes, 0, 0x8000);
            std::fprintf(stderr, "synthetic GTA image section does not cover page 0x%08lX\n",
                static_cast<unsigned long>(page));
            return false;
        }
        if (!copy_pe_page(bytes, fileSize, peOffset, sectionTable, sectionCount,
                sizeOfHeaders, page))
        {
            VirtualFree(bytes, 0, 0x8000);
            std::fprintf(stderr, "could not map original GTA bytes at 0x%08lX\n",
                static_cast<unsigned long>(page));
            return false;
        }
    }
    VirtualFree(bytes, 0, 0x8000);
    return true;
}

}

extern "C" void __cdecl FUN_100014c0(char*) {}
extern "C" void __fastcall FUN_1000a560(int) { ++g_dispatch_calls; }
extern "C" int __stdcall FUN_1000a4f0() { return 0; }
extern "C" void __stdcall FUN_10001770() {}
extern "C" void __stdcall FUN_10001e80() {}
extern "C" std::uint32_t __stdcall FUN_1000a800(std::uintptr_t, std::uintptr_t) { return 0; }
extern "C" int* __cdecl FUN_100076d0(int*, int*) { return nullptr; }
extern "C" std::uint32_t __fastcall FUN_10008b70(int) { return 0; }
extern "C" std::uint32_t __cdecl FUN_10008cb0(std::uint32_t, std::uint32_t) { return 0; }
extern "C" void __cdecl FUN_10008da0(std::uint32_t, std::uint32_t*) {}
extern "C" void __cdecl FUN_10008dd0(std::uint32_t, int) {}

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "This harness must be built for x86.");
    const auto syntheticBegin = reinterpret_cast<std::uintptr_t>(g_synthetic_gta_image);
    const auto syntheticEnd = syntheticBegin + sizeof(g_synthetic_gta_image);
    for (std::uintptr_t page : kGtaPatchPages)
    {
        if (page < syntheticBegin || page + 0x1000 > syntheticEnd)
        {
            std::fprintf(stderr, "synthetic GTA image section does not cover patch page 0x%08lX (range %08lX..%08lX)\n",
                static_cast<unsigned long>(page),
                static_cast<unsigned long>(syntheticBegin),
                static_cast<unsigned long>(syntheticEnd));
            return 4;
        }
    }
    if (argc != 2 || !load_gta_patch_pages(argv[1])) return 5;
    std::memcpy(IVF_RELOC_TARGET_1003A8C8, "C:\\ImVehFtTest\\", 16);

    FUN_10002210();

    bool ok = true;
    for (const auto& hook : kHooks)
    {
        const auto* const patch = reinterpret_cast<const std::uint8_t*>(hook.opcode);
        std::int32_t displacement = 0;
        std::memcpy(&displacement, patch + 1, sizeof(displacement));
        const auto decoded = static_cast<std::uintptr_t>(
            static_cast<std::int64_t>(hook.opcode + 5) + displacement);
        const auto expected = reinterpret_cast<std::uintptr_t>(hook.wrapper);
        if (patch[0] != hook.patchedOpcode || decoded != expected)
        {
            std::fprintf(stderr,
                "hook patch mismatch at 0x%08lX: opcode=%02X target=%08lX expected=%08lX\n",
                static_cast<unsigned long>(hook.opcode), patch[0],
                static_cast<unsigned long>(decoded), static_cast<unsigned long>(expected));
            ok = false;
        }
    }

    ok = check_pointer_patch(0x004C8415, reinterpret_cast<const void*>(&FUN_100076d0)) && ok;
    ok = check_pointer_patch(0x0085C5F4, reinterpret_cast<const void*>(&FUN_10008b70)) && ok;
    ok = check_pointer_patch(0x004C9148, reinterpret_cast<const void*>(&FUN_10008cb0)) && ok;
    if (g_dispatch_calls == 0)
    {
        std::fprintf(stderr, "mode-dispatch stub was not exercised\n");
        ok = false;
    }

    if (!ok)
    {
        return 1;
    }
    std::fprintf(stderr, "PASS actual FUN_10002210 object: %zu/%zu rel32 hook patches, 3 function-pointer patches, real VirtualProtect on synthetic memory, %d mode dispatches\n",
        sizeof(kHooks) / sizeof(kHooks[0]), sizeof(kHooks) / sizeof(kHooks[0]),
        g_dispatch_calls);
    return 0;
}
