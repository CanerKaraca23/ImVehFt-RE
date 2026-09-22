#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void* ExceptionList;

extern "C" void __cdecl __NLG_Notify(unsigned int);

extern "C" void __stdcall FUN_10018f94();

extern "C" void __cdecl __local_unwind2(int param_1, unsigned int param_2)
{
    struct LocalUnwindRegistration
    {
        void* previous;
        void* handler;
    };

    struct UnwindEntry
    {
        unsigned int reserved_00;
        int is_cleanup;
        unsigned int reserved_08;
    };

    LocalUnwindRegistration registration{
        ExceptionList,
        reinterpret_cast<void*>(0x10018e80)
    };

    ExceptionList = &registration;

    while (true)
    {
        auto* unwindState =
            reinterpret_cast<unsigned int*>(
                static_cast<uintptr_t>(static_cast<unsigned int>(param_1)) + 0x0c);

        const unsigned int state = *unwindState;

        if (state == 0xffffffffu ||
            (param_2 != 0xffffffffu && state <= param_2))
        {
            break;
        }

        auto* entries =
            *reinterpret_cast<UnwindEntry**>(
                static_cast<uintptr_t>(static_cast<unsigned int>(param_1)) + 0x08);

        *unwindState = entries[state].reserved_00;

        if (entries[state].is_cleanup == 0)
        {
            __NLG_Notify(0x101u);
            FUN_10018f94();
        }
    }

    ExceptionList = registration.previous;
}