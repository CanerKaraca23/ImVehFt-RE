#include <windows.h>
#include <cstdint>

extern "C" void __stdcall FUN_100095f0();
extern "C" void __stdcall FUN_100094d0();

struct FUN_10009430_this {
    int __thiscall FUN_10009430(char param_1);
};

int FUN_10009430_this::FUN_10009430(char param_1)
{
    void* this_ptr = static_cast<void*>(this);
    auto* base = static_cast<unsigned char*>(this_ptr);
    HANDLE& mapping_handle = *reinterpret_cast<HANDLE*>(base);
    LPVOID& mapping_view = *reinterpret_cast<LPVOID*>(base + 4);

    if (mapping_view == nullptr)
    {
        if (mapping_handle == nullptr)
            goto LAB_10009448;

LAB_10009460:
        if (mapping_view == nullptr)
        {
            mapping_view = MapViewOfFile(
                mapping_handle,
                0xF001F,
                0,
                0,
                0);
        }

        if (mapping_view != nullptr &&
            mapping_handle != nullptr &&
            *reinterpret_cast<int*>(mapping_view) == 0)
        {
            FUN_100095f0();
        }
    }
    else
    {
        if (mapping_handle != nullptr)
            goto LAB_100094A9;

LAB_10009448:
        mapping_handle = OpenFileMappingA(
            0xF001F,
            FALSE,
            "GTA_PLUGIN_SDK");

        if (mapping_handle != nullptr)
            goto LAB_10009460;
    }

    if (param_1 == '\0' &&
        (mapping_view == nullptr || mapping_handle == nullptr))
    {
        FUN_100094d0();
    }

LAB_100094A9:
    if (mapping_view != nullptr && mapping_handle != nullptr)
        return 1;

    return 0;
}