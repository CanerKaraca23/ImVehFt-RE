#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
unsigned int __stdcall FUN_1000fd20(unsigned int param_1)
{
    using Callback = void (__cdecl *)(unsigned int);
    using ReturnCallback = unsigned int (__cdecl *)();

    extern unsigned int DAT_1003c3dc;

    auto* base = reinterpret_cast<unsigned char*>(
        static_cast<unsigned int>(DAT_1003c3dc));

    Callback* begin_18 = *reinterpret_cast<Callback**>(base + 0x18);
    Callback* end_1c = *reinterpret_cast<Callback**>(base + 0x1c);

    for (Callback* callback = begin_18; callback != end_1c; ++callback)
    {
        if (*callback != nullptr)
            (*callback)(param_1);
    }

    unsigned int result = 0;
    ReturnCallback callback_0c =
        *reinterpret_cast<ReturnCallback*>(base + 0x0c);

    if (callback_0c != nullptr)
        result = callback_0c();

    Callback* begin_28 = *reinterpret_cast<Callback**>(base + 0x28);
    Callback* end_2c = *reinterpret_cast<Callback**>(base + 0x2c);

    for (Callback* callback = begin_28; callback != end_2c; ++callback)
    {
        if (*callback != nullptr)
            (*callback)(param_1);
    }

    return result;
}