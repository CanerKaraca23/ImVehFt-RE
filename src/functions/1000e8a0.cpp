#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
unsigned int __stdcall FUN_1000e8a0()
{
    extern unsigned int DAT_1003c3b4;

    using Callback = void (*)();
    using ReturnCallback = unsigned int (*)();

    const unsigned int state = DAT_1003c3b4;

    Callback* end_18 = *reinterpret_cast<Callback**>(state + 0x1c);

    for (Callback* callback_entry = *reinterpret_cast<Callback**>(state + 0x18);
         callback_entry != end_18;
         ++callback_entry)
    {
        if (*callback_entry != nullptr)
        {
            (*callback_entry)();
        }
    }

    unsigned int result;

    const ReturnCallback return_callback =
        *reinterpret_cast<ReturnCallback*>(state + 0x10);

    if (return_callback == nullptr)
    {
        result = 0U;
    }
    else
    {
        result = return_callback();
    }

    Callback* end_28 = *reinterpret_cast<Callback**>(state + 0x2c);

    for (Callback* callback_entry = *reinterpret_cast<Callback**>(state + 0x28);
         callback_entry != end_28;
         ++callback_entry)
    {
        if (*callback_entry != nullptr)
        {
            (*callback_entry)();
        }
    }

    return result;
}