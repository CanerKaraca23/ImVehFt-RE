#include <cstddef>
#include <cstdint>

using DWORD = std::uint32_t;
using UINT = std::uint32_t;
using BOOL = int;
using LPCSTR = const char*;
using LPVOID = void*;
using LPDWORD = DWORD*;

extern "C" void __cdecl FUN_100014c0(char*);
extern "C" void __fastcall FUN_1000a560(int);
extern "C" int __stdcall FUN_1000a4f0();
extern "C" void __stdcall FUN_10001770();
extern "C" void __stdcall FUN_10001e80();
extern "C" std::uint32_t __stdcall FUN_1000a800(std::uintptr_t, std::uintptr_t);
extern "C" int* __cdecl FUN_100076d0(int*, int*);
extern "C" std::uint32_t __fastcall FUN_10008b70(int);
extern "C" std::uint32_t __cdecl FUN_10008cb0(std::uint32_t, std::uint32_t);
extern "C" void __cdecl FUN_10008da0(std::uint32_t, std::uint32_t*);
extern "C" void __cdecl FUN_10008dd0(std::uint32_t, int);

extern "C" int __cdecl strcpy_s(char*, std::size_t, const char*);
extern "C" int __cdecl strcat_s(char*, std::size_t, const char*);
extern "C" UINT __stdcall GetPrivateProfileIntA(LPCSTR, LPCSTR, int, LPCSTR);
extern "C" BOOL __stdcall VirtualProtect(LPVOID, std::size_t, DWORD, LPDWORD);

void __stdcall FUN_10002210(void)
{
    DWORD local_14;
    DWORD local_10;
    DWORD local_c;
    DWORD local_8;

    volatile auto& samp_fix = *reinterpret_cast<volatile std::uint8_t*>(0x1003AEF1);
    volatile auto& disable_beam_shape = *reinterpret_cast<volatile std::uint8_t*>(0x1003A6C7);
    volatile auto& turnlights_delay = *reinterpret_cast<volatile std::uint32_t*>(0x1003AED8);
    volatile auto& turnlights_delay_twice = *reinterpret_cast<volatile std::uint32_t*>(0x1003BC70);
    volatile auto& key_fog = *reinterpret_cast<volatile std::uint32_t*>(0x1003BC04);
    volatile auto& key_turnl_l = *reinterpret_cast<volatile std::uint32_t*>(0x1003BC24);
    volatile auto& key_turnl_r = *reinterpret_cast<volatile std::uint32_t*>(0x1003BC0C);
    volatile auto& key_turnl_2 = *reinterpret_cast<volatile std::uint32_t*>(0x1003BBBC);
    volatile auto& key_turnl_0 = *reinterpret_cast<volatile std::uint32_t*>(0x1003B6FC);
    volatile auto& key_headlight = *reinterpret_cast<volatile std::uint32_t*>(0x1003BC74);
    volatile auto& registered_vehicle_plugin =
        *reinterpret_cast<volatile std::uint32_t*>(0x1003C248);

    auto* ini_path = reinterpret_cast<char*>(0x1003A6C8);
    auto* base_path = reinterpret_cast<const char*>(0x1003A8C8);

    FUN_100014c0(const_cast<char*>(
        "This file was created by ImVehFt.asi\n"
        "Current plugin version: 2.1.1\n"));
    FUN_100014c0(const_cast<char*>("Reading ImVehFt.ini..."));

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    samp_fix = GetPrivateProfileIntA("MAIN", "SAMP_fix", 0, ini_path) != 0;

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    disable_beam_shape =
        GetPrivateProfileIntA("MAIN", "disable_beam_shape", 1, ini_path) != 0;

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    turnlights_delay =
        GetPrivateProfileIntA("MAIN", "turnlights_delay", 500, ini_path);
    turnlights_delay_twice = turnlights_delay * 2;

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    key_fog = GetPrivateProfileIntA("CONTROL", "key_fog", 0x4A, ini_path);

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    key_turnl_l =
        GetPrivateProfileIntA("CONTROL", "key_turnl_l", 0x5A, ini_path);

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    key_turnl_r =
        GetPrivateProfileIntA("CONTROL", "key_turnl_r", 0x43, ini_path);

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    key_turnl_2 =
        GetPrivateProfileIntA("CONTROL", "key_turnl_2", 0x58, ini_path);

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    key_turnl_0 =
        GetPrivateProfileIntA("CONTROL", "key_turnl_0", 0x10, ini_path);

    strcpy_s(ini_path, 0x200, base_path);
    strcat_s(ini_path, 0x200, "ImVehFt\\ImVehFt.ini");
    key_headlight =
        GetPrivateProfileIntA("CONTROL", "key_headlight", 0x47, ini_path);

    FUN_100014c0(const_cast<char*>("Finished."));
    FUN_100014c0(const_cast<char*>("Making ImVehFt memory patches..."));

#define VP(address, size, protection, old_protection) \
    VirtualProtect(reinterpret_cast<LPVOID>(address), size, protection, old_protection)

    VP(0x004C8415, 4, 0x40, &local_c);
    *reinterpret_cast<volatile std::uint32_t*>(0x004C8415) =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&FUN_100076d0));
    VP(0x004C8415, 4, local_c, &local_8);

    local_8 = 0xE8;
    VP(0x006D6617, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006D6617) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006D6617, 1, local_14, &local_10);
    VP(0x006D6618, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006D6618) = 0x0F930EB4;
    VP(0x006D6618, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x005B8FFD, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005B8FFD) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005B8FFD, 1, local_14, &local_10);
    VP(0x005B8FFE, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005B8FFE) = 0x0FA4F13E;
    VP(0x005B8FFE, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006D6494, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006D6494) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006D6494, 1, local_14, &local_10);
    VP(0x006D6495, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006D6495) = 0x0F92EC47;
    VP(0x006D6495, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x0053BFCC, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x0053BFCC) =
        static_cast<std::uint8_t>(local_8);
    VP(0x0053BFCC, 1, local_14, &local_10);
    VP(0x0053BFCD, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x0053BFCD) = 0x0FAC8B3F;
    VP(0x0053BFCD, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006D6A58, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006D6A58) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006D6A58, 1, local_14, &local_10);
    VP(0x006D6A59, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006D6A59) = 0x0F92D863;
    VP(0x006D6A59, 4, local_14, &local_10);

    FUN_1000a560(3);

    local_8 = 0xE9;
    VP(0x005D5BC7, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5BC7) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005D5BC7, 1, local_14, &local_10);
    VP(0x005D5BC8, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005D5BC8) = 0x0FA32BB4;
    VP(0x005D5BC8, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x005D5C1E, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5C1E) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005D5C1E, 1, local_14, &local_10);
    VP(0x005D5C1F, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005D5C1F) = 0x0FA32C0D;
    VP(0x005D5C1F, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x005D5AD1, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5AD1) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005D5AD1, 1, local_14, &local_10);
    VP(0x005D5AD2, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005D5AD2) = 0x0FA32E6A;
    VP(0x005D5AD2, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E198E, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E198E) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E198E, 1, local_14, &local_10);
    VP(0x006E198F, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E198F) = 0x0F9265FD;
    VP(0x006E198F, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E18DA, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E18DA) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E18DA, 1, local_14, &local_10);
    VP(0x006E18DB, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E18DB) = 0x0F926671;
    VP(0x006E18DB, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E1A2D, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E1A2D) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E1A2D, 1, local_14, &local_10);
    VP(0x006E1A2E, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E1A2E) = 0x0F92653E;
    VP(0x006E1A2E, 4, local_14, &local_10);

    VP(0x005D5BFD, 3, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint16_t*>(0x005D5BFD) = 0x9090;
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5BFF) = 0x90;
    VP(0x005D5BFD, 3, local_14, &local_10);

    VP(0x005D5D3D, 5, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005D5D3D) = 0x90909090;
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5D41) = 0x90;
    VP(0x005D5D3D, 5, local_14, &local_10);

    VP(0x006E18E5, 6, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E18E5) = 0x90909090;
    *reinterpret_cast<volatile std::uint16_t*>(0x006E18E9) = 0x9090;
    VP(0x006E18E5, 6, local_14, &local_10);

    VP(0x006E28E7, 5, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E28E7) = 0x90909090;
    *reinterpret_cast<volatile std::uint8_t*>(0x006E28EB) = 0x90;
    VP(0x006E28E7, 5, local_14, &local_10);

    VP(0x006E1D4F, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E1D4F) = 2;
    VP(0x006E1D4F, 1, local_14, &local_10);

    VP(0x004C900D, 5, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x004C900D) = 0x90909090;
    *reinterpret_cast<volatile std::uint8_t*>(0x004C9011) = 0x90;
    VP(0x004C900D, 5, local_14, &local_10);

    VP(0x0085C5F4, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x0085C5F4) =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&FUN_10008b70));
    VP(0x0085C5F4, 4, local_14, &local_10);

    VP(0x004C9148, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x004C9148) =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&FUN_10008cb0));
    VP(0x004C9148, 4, local_14, &local_10);

    if (samp_fix == 0)
    {
        VP(0x006FDF47, 1, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint8_t*>(0x006FDF47) = 3;
        VP(0x006FDF47, 1, local_14, &local_10);

        local_8 = 0xE8;
        VP(0x006FDED6, 1, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint8_t*>(0x006FDED6) =
            static_cast<std::uint8_t>(local_8);
        VP(0x006FDED6, 1, local_14, &local_10);
        VP(0x006FDED7, 4, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint32_t*>(0x006FDED7) = 0x0F905F65;
        VP(0x006FDED7, 4, local_14, &local_10);

        local_8 = 0xE8;
        VP(0x006FDF10, 1, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint8_t*>(0x006FDF10) =
            static_cast<std::uint8_t>(local_8);
        VP(0x006FDF10, 1, local_14, &local_10);
        VP(0x006FDF11, 4, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint32_t*>(0x006FDF11) = 0x0F90602B;
        VP(0x006FDF11, 4, local_14, &local_10);

        FUN_1000a560(8);
    }

    local_8 = 0xE9;
    VP(0x006AB350, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006AB350) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006AB350, 1, local_14, &local_10);
    VP(0x006AB351, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006AB351) = 0x0F957CDB;
    VP(0x006AB351, 4, local_14, &local_10);

    VP(0x006AB355, 5, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006AB355) = 0x90909090;
    *reinterpret_cast<volatile std::uint8_t*>(0x006AB359) = 0x90;
    VP(0x006AB355, 5, local_14, &local_10);

    FUN_1000a560(7);

    local_8 = 0xE8;
    VP(0x006F3AED, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006F3AED) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006F3AED, 1, local_14, &local_10);
    VP(0x006F3AEE, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006F3AEE) = 0x0F90F56E;
    VP(0x006F3AEE, 4, local_14, &local_10);

    VP(0x006F3AF2, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006F3AF2) = 0x90;
    VP(0x006F3AF2, 1, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006F3973, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006F3973) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006F3973, 1, local_14, &local_10);
    VP(0x006F3974, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006F3974) = 0x0F90F708;
    VP(0x006F3974, 4, local_14, &local_10);

    VP(0x006F3978, 7, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006F3978) = 0x90909090;
    *reinterpret_cast<volatile std::uint16_t*>(0x006F397C) = 0x9090;
    *reinterpret_cast<volatile std::uint8_t*>(0x006F397E) = 0x90;
    VP(0x006F3978, 7, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006E174B, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E174B) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E174B, 1, local_14, &local_10);
    VP(0x006E174C, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E174C) = 0x0F921CB0;
    VP(0x006E174C, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006E175E, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E175E) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E175E, 1, local_14, &local_10);
    VP(0x006E175F, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E175F) = 0x0F921C9D;
    VP(0x006E175F, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006E173C, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E173C) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E173C, 1, local_14, &local_10);
    VP(0x006E173D, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E173D) = 0x0F921F1F;
    VP(0x006E173D, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006E1773, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E1773) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E1773, 1, local_14, &local_10);
    VP(0x006E1774, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E1774) = 0x0F921EE8;
    VP(0x006E1774, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E27E6, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E27E6) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E27E6, 1, local_14, &local_10);
    VP(0x006E27E7, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E27E7) = 0x0F9209F5;
    VP(0x006E27E7, 4, local_14, &local_10);

    if (disable_beam_shape != 0)
    {
        VP(0x006A2ED3, 0x0C, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint32_t*>(0x006A2ED3) = 0x90909090;
        *reinterpret_cast<volatile std::uint32_t*>(0x006A2ED7) = 0x90909090;
        *reinterpret_cast<volatile std::uint32_t*>(0x006A2EDB) = 0x90909090;
        VP(0x006A2ED3, 0x0C, local_14, &local_10);

        VP(0x006A2EEB, 0x0C, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint32_t*>(0x006A2EEB) = 0x90909090;
        *reinterpret_cast<volatile std::uint32_t*>(0x006A2EEF) = 0x90909090;
        *reinterpret_cast<volatile std::uint32_t*>(0x006A2EF3) = 0x90909090;
        VP(0x006A2EEB, 0x0C, local_14, &local_10);

        VP(0x006BDE73, 0x12, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint32_t*>(0x006BDE73) = 0x90909090;
        *reinterpret_cast<volatile std::uint32_t*>(0x006BDE77) = 0x90909090;
        *reinterpret_cast<volatile std::uint32_t*>(0x006BDE7B) = 0x90909090;
        *reinterpret_cast<volatile std::uint32_t*>(0x006BDE7F) = 0x90909090;
        *reinterpret_cast<volatile std::uint16_t*>(0x006BDE83) = 0x9090;
        VP(0x006BDE73, 0x12, local_14, &local_10);
    }

    local_8 = 0xE8;
    VP(0x006E0DF7, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E0DF7) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E0DF7, 1, local_14, &local_10);
    VP(0x006E0DF8, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E0DF8) = 0x0F922544;
    VP(0x006E0DF8, 4, local_14, &local_10);

    FUN_100014c0(const_cast<char*>("Finished."));

    if (FUN_1000a4f0() == 0)
    {
        FUN_10001770();
        FUN_10001e80();
    }

    FUN_100014c0(const_cast<char*>("Registering vehicle plugin..."));

    registered_vehicle_plugin =
        FUN_1000a800(
            reinterpret_cast<std::uintptr_t>(&FUN_10008da0),
            reinterpret_cast<std::uintptr_t>(&FUN_10008dd0));

    FUN_100014c0(const_cast<char*>(
        "Finished (registered vehicle plugin %d)"));

#undef VP
}