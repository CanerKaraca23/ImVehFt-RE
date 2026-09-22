#include <cstdint>

extern "C" void* ExceptionList;
extern "C" std::uint32_t DAT_10029490;

extern "C" void __stdcall __NLG_Notify(unsigned long);
extern "C" void __stdcall FUN_10018f94();

void __cdecl __local_unwind4(
    std::uint32_t* param_1,
    int param_2,
    std::uint32_t param_3)
{
    struct RegistrationRecord
    {
        void* previous;
        void* handler;
        std::uint32_t cookie;
    };

    RegistrationRecord registration{
        ExceptionList,
        reinterpret_cast<void*>(0x10013A10u),
        DAT_10029490 ^
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(&registration))
    };

    ExceptionList = &registration;

    while (true)
    {
        const std::uint32_t state =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(param_2) + 0x0Cu);

        if (state == 0xFFFFFFFEu ||
            (param_3 != 0xFFFFFFFEu && state <= param_3))
        {
            break;
        }

        auto* unwind_entry =
            reinterpret_cast<std::uint32_t*>(
                ((*reinterpret_cast<std::uint32_t*>(
                      static_cast<std::uintptr_t>(param_2) + 0x08u) ^
                  *param_1) +
                 0x10u) +
                state * 0x0Cu);

        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(param_2) + 0x0Cu) =
            unwind_entry[0];

        if (unwind_entry[1] == 0)
        {
            __NLG_Notify(0x101u);
            FUN_10018f94();
        }
    }

    ExceptionList = registration.previous;
}