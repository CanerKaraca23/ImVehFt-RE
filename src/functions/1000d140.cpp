#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#include <cstdint>
extern "C" void __stdcall thunk_FUN_10009580();
extern "C" __declspec(noreturn) void __stdcall FUN_100095f0();
extern "C" int __stdcall FUN_10009360();
extern "C" void __stdcall FUN_100094d0();
#include <cstdint>

void __stdcall FUN_1000d140()
{
    using HANDLE = void*;
    using LPVOID = void*;
    using DWORD = std::uint32_t;
    using BOOL = int;

    extern int __cdecl _atexit(void (__cdecl*)());
    extern HANDLE __stdcall OpenFileMappingA(DWORD, BOOL, const char*);
    extern LPVOID __stdcall MapViewOfFile(
        HANDLE, DWORD, DWORD, DWORD, DWORD);
    extern BOOL __stdcall HeapFree(HANDLE, DWORD, LPVOID);

    extern int DAT_1003c3fc;
    extern HANDLE DAT_1003c3e8;
    extern int* DAT_1003c3ec;

    const auto object = static_cast<std::uintptr_t>(
        static_cast<std::uint32_t>(FUN_10009360()));

    if (*reinterpret_cast<LPVOID*>(object + 0x40) == nullptr)
    {
        return;
    }

    if ((DAT_1003c3fc & 1) == 0)
    {
        DAT_1003c3fc = DAT_1003c3fc | 1;
        DAT_1003c3e8 = nullptr;
        DAT_1003c3ec = nullptr;
        _atexit(reinterpret_cast<void (__cdecl*)()>(thunk_FUN_10009580));
    }

    LPVOID memory = *reinterpret_cast<LPVOID*>(object + 0x40);
    int* mapped_view;
    HANDLE mapping_handle;

    if (DAT_1003c3ec == nullptr)
    {
        if (DAT_1003c3e8 == nullptr)
        {
            goto LAB_1000d1a6;
        }

LAB_1000d1c9:
        if ((DAT_1003c3ec != nullptr) ||
            (DAT_1003c3ec = static_cast<int*>(MapViewOfFile(
                 DAT_1003c3e8, 0xF001F, 0, 0, 0)),
             DAT_1003c3ec != nullptr))
        {
            mapped_view = DAT_1003c3ec;
            mapping_handle = DAT_1003c3e8;

            if ((DAT_1003c3e8 != nullptr) && (*DAT_1003c3ec == 0))
            {
                FUN_100095f0();
            }

            goto LAB_1000d1f9;
        }
    }
    else
    {
        mapped_view = DAT_1003c3ec;
        mapping_handle = DAT_1003c3e8;

        if (DAT_1003c3e8 != nullptr)
        {
            goto LAB_1000d218;
        }

LAB_1000d1a6:
        DAT_1003c3e8 = OpenFileMappingA(
            0xF001F, 0, "GTA_PLUGIN_SDK");

        mapped_view = DAT_1003c3ec;
        mapping_handle = DAT_1003c3e8;

        if (DAT_1003c3e8 != nullptr)
        {
            goto LAB_1000d1c9;
        }

LAB_1000d1f9:
        if ((mapped_view != nullptr) && (mapping_handle != nullptr))
        {
            goto LAB_1000d218;
        }
    }

    FUN_100094d0();

    mapped_view = DAT_1003c3ec;
    mapping_handle = DAT_1003c3e8;

LAB_1000d218:
    if ((mapped_view == nullptr) || (mapping_handle == nullptr))
    {
        FUN_100095f0();
    }

    HeapFree(
        reinterpret_cast<HANDLE>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(mapped_view[1]))),
        0,
        memory);

    *reinterpret_cast<std::uint32_t*>(object + 0x48) = 0;
    *reinterpret_cast<LPVOID*>(object + 0x40) = nullptr;
}