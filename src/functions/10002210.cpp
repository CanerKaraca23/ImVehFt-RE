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

extern "C" void __cdecl IVF_INSTALL_TARGET_10003030();
extern "C" void __cdecl IVF_INSTALL_TARGET_10003060();
extern "C" void __cdecl IVF_INSTALL_TARGET_10003080();
extern "C" void __cdecl IVF_INSTALL_TARGET_100031E0();
extern "C" void __cdecl IVF_INSTALL_TARGET_10003340();
extern "C" void __cdecl IVF_INSTALL_TARGET_10003400();
extern "C" void __cdecl IVF_INSTALL_TARGET_10003660();
extern "C" void __cdecl IVF_INSTALL_TARGET_10003E40();
extern "C" void __cdecl IVF_INSTALL_TARGET_10003F40();
extern "C" void __cdecl IVF_INSTALL_TARGET_100042C0();
extern "C" void __cdecl IVF_INSTALL_TARGET_10004B10();
extern "C" void __cdecl IVF_INSTALL_TARGET_100050E0();
extern "C" void __cdecl IVF_INSTALL_TARGET_100074D0();
extern "C" void __cdecl IVF_INSTALL_TARGET_10007F50();
extern "C" void __cdecl IVF_INSTALL_TARGET_10007F70();
extern "C" void __cdecl IVF_INSTALL_TARGET_10007F90();
extern "C" void __cdecl IVF_INSTALL_TARGET_10008140();
extern "C" void __cdecl IVF_INSTALL_TARGET_10008780();
extern "C" void __cdecl IVF_INSTALL_TARGET_10008830();
extern "C" void __cdecl IVF_INSTALL_TARGET_10008940();
extern "C" std::uint8_t IVF_RELOC_TARGET_1003AEF1;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003A6C7;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003AED8;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003BC70;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003BC04;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003BC24;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003BC0C;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003BBBC;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003B6FC;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003BC74;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003C248;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003A6C8;
extern "C" std::uint8_t IVF_RELOC_TARGET_1003A8C8;

#define REL32(opcode_address, target) \
    static_cast<std::uint32_t>( \
        reinterpret_cast<std::uintptr_t>(target) - \
        (static_cast<std::uintptr_t>(opcode_address) + 5u))

void __stdcall FUN_10002210(void)
{
    DWORD local_14;
    DWORD local_10;
    DWORD local_c;
    DWORD local_8;

    volatile auto& samp_fix = *reinterpret_cast<volatile std::uint8_t*>(&IVF_RELOC_TARGET_1003AEF1);
    volatile auto& disable_beam_shape = *reinterpret_cast<volatile std::uint8_t*>(&IVF_RELOC_TARGET_1003A6C7);
    volatile auto& turnlights_delay = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003AED8);
    volatile auto& turnlights_delay_twice = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003BC70);
    volatile auto& key_fog = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003BC04);
    volatile auto& key_turnl_l = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003BC24);
    volatile auto& key_turnl_r = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003BC0C);
    volatile auto& key_turnl_2 = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003BBBC);
    volatile auto& key_turnl_0 = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003B6FC);
    volatile auto& key_headlight = *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003BC74);
    volatile auto& registered_vehicle_plugin =
        *reinterpret_cast<volatile std::uint32_t*>(&IVF_RELOC_TARGET_1003C248);

    auto* ini_path = reinterpret_cast<char*>(&IVF_RELOC_TARGET_1003A6C8);
    auto* base_path = reinterpret_cast<const char*>(&IVF_RELOC_TARGET_1003A8C8);

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
    *reinterpret_cast<volatile std::uint32_t*>(0x006D6618) =
        REL32(0x006D6617, &IVF_INSTALL_TARGET_100074D0);
    VP(0x006D6618, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x005B8FFD, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005B8FFD) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005B8FFD, 1, local_14, &local_10);
    VP(0x005B8FFE, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005B8FFE) =
        REL32(0x005B8FFD, &IVF_INSTALL_TARGET_10008140);
    VP(0x005B8FFE, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006D6494, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006D6494) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006D6494, 1, local_14, &local_10);
    VP(0x006D6495, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006D6495) =
        REL32(0x006D6494, &IVF_INSTALL_TARGET_100050E0);
    VP(0x006D6495, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x0053BFCC, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x0053BFCC) =
        static_cast<std::uint8_t>(local_8);
    VP(0x0053BFCC, 1, local_14, &local_10);
    VP(0x0053BFCD, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x0053BFCD) =
        REL32(0x0053BFCC, &IVF_INSTALL_TARGET_10004B10);
    VP(0x0053BFCD, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006D6A58, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006D6A58) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006D6A58, 1, local_14, &local_10);
    VP(0x006D6A59, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006D6A59) =
        REL32(0x006D6A58, &IVF_INSTALL_TARGET_100042C0);
    VP(0x006D6A59, 4, local_14, &local_10);

    FUN_1000a560(3);

    local_8 = 0xE9;
    VP(0x005D5BC7, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5BC7) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005D5BC7, 1, local_14, &local_10);
    VP(0x005D5BC8, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005D5BC8) =
        REL32(0x005D5BC7, &IVF_INSTALL_TARGET_10008780);
    VP(0x005D5BC8, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x005D5C1E, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5C1E) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005D5C1E, 1, local_14, &local_10);
    VP(0x005D5C1F, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005D5C1F) =
        REL32(0x005D5C1E, &IVF_INSTALL_TARGET_10008830);
    VP(0x005D5C1F, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x005D5AD1, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x005D5AD1) =
        static_cast<std::uint8_t>(local_8);
    VP(0x005D5AD1, 1, local_14, &local_10);
    VP(0x005D5AD2, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x005D5AD2) =
        REL32(0x005D5AD1, &IVF_INSTALL_TARGET_10008940);
    VP(0x005D5AD2, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E198E, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E198E) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E198E, 1, local_14, &local_10);
    VP(0x006E198F, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E198F) =
        REL32(0x006E198E, &IVF_INSTALL_TARGET_10007F90);
    VP(0x006E198F, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E18DA, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E18DA) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E18DA, 1, local_14, &local_10);
    VP(0x006E18DB, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E18DB) =
        REL32(0x006E18DA, &IVF_INSTALL_TARGET_10007F50);
    VP(0x006E18DB, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E1A2D, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E1A2D) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E1A2D, 1, local_14, &local_10);
    VP(0x006E1A2E, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E1A2E) =
        REL32(0x006E1A2D, &IVF_INSTALL_TARGET_10007F70);
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
        *reinterpret_cast<volatile std::uint32_t*>(0x006FDED7) =
            REL32(0x006FDED6, &IVF_INSTALL_TARGET_10003E40);
        VP(0x006FDED7, 4, local_14, &local_10);

        local_8 = 0xE8;
        VP(0x006FDF10, 1, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint8_t*>(0x006FDF10) =
            static_cast<std::uint8_t>(local_8);
        VP(0x006FDF10, 1, local_14, &local_10);
        VP(0x006FDF11, 4, 0x40, &local_14);
        *reinterpret_cast<volatile std::uint32_t*>(0x006FDF11) =
            REL32(0x006FDF10, &IVF_INSTALL_TARGET_10003F40);
        VP(0x006FDF11, 4, local_14, &local_10);

        FUN_1000a560(8);
    }

    local_8 = 0xE9;
    VP(0x006AB350, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006AB350) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006AB350, 1, local_14, &local_10);
    VP(0x006AB351, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006AB351) =
        REL32(0x006AB350, &IVF_INSTALL_TARGET_10003030);
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
    *reinterpret_cast<volatile std::uint32_t*>(0x006F3AEE) =
        REL32(0x006F3AED, &IVF_INSTALL_TARGET_10003060);
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
    *reinterpret_cast<volatile std::uint32_t*>(0x006F3974) =
        REL32(0x006F3973, &IVF_INSTALL_TARGET_10003080);
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
    *reinterpret_cast<volatile std::uint32_t*>(0x006E174C) =
        REL32(0x006E174B, &IVF_INSTALL_TARGET_10003400);
    VP(0x006E174C, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006E175E, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E175E) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E175E, 1, local_14, &local_10);
    VP(0x006E175F, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E175F) =
        REL32(0x006E175E, &IVF_INSTALL_TARGET_10003400);
    VP(0x006E175F, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006E173C, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E173C) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E173C, 1, local_14, &local_10);
    VP(0x006E173D, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E173D) =
        REL32(0x006E173C, &IVF_INSTALL_TARGET_10003660);
    VP(0x006E173D, 4, local_14, &local_10);

    local_8 = 0xE8;
    VP(0x006E1773, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E1773) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E1773, 1, local_14, &local_10);
    VP(0x006E1774, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E1774) =
        REL32(0x006E1773, &IVF_INSTALL_TARGET_10003660);
    VP(0x006E1774, 4, local_14, &local_10);

    local_8 = 0xE9;
    VP(0x006E27E6, 1, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint8_t*>(0x006E27E6) =
        static_cast<std::uint8_t>(local_8);
    VP(0x006E27E6, 1, local_14, &local_10);
    VP(0x006E27E7, 4, 0x40, &local_14);
    *reinterpret_cast<volatile std::uint32_t*>(0x006E27E7) =
        REL32(0x006E27E6, &IVF_INSTALL_TARGET_100031E0);
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
    *reinterpret_cast<volatile std::uint32_t*>(0x006E0DF8) =
        REL32(0x006E0DF7, &IVF_INSTALL_TARGET_10003340);
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
#undef REL32
}
