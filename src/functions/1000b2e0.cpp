#include <cstdint>

using FunctionPointer = void(__cdecl*)(std::uint32_t, int, int, int, int);

extern void** DAT_1003c3b4;
extern std::uint32_t* DAT_10037740;
extern std::uint32_t* DAT_10037744;
extern std::uint32_t* DAT_10037748;
extern std::uint32_t PTR_vftable_10037728;

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000b2e0(std::uint32_t param_1)
{
    if (DAT_1003c3b4 == nullptr) {
        DAT_1003c3b4 =
            reinterpret_cast<void**>(&PTR_vftable_10037728);

        auto function = *reinterpret_cast<void(__thiscall**)(
            void*,
            std::uint32_t,
            std::uint32_t,
            std::uint32_t,
            std::uint32_t
        )>(PTR_vftable_10037728 + 4u);

        function(reinterpret_cast<void*>(0x58aa2d), 0, 0, 0, 0);
    }

    const auto parameter_address =
        reinterpret_cast<std::uintptr_t>(&param_1);
    const auto begin_address =
        reinterpret_cast<std::uintptr_t>(DAT_10037740);
    const auto end_address =
        reinterpret_cast<std::uintptr_t>(DAT_10037744);

    if ((parameter_address < end_address) &&
        (begin_address <= parameter_address)) {
        const std::int32_t index =
            static_cast<std::int32_t>(
                parameter_address - begin_address);

        if (DAT_10037744 == DAT_10037748) {
            FUN_1000cfe0();
        }

        if (DAT_10037744 != nullptr) {
            *DAT_10037744 = DAT_10037740[index >> 2];
        }

        DAT_10037744 = DAT_10037744 + 1;
        return;
    }

    if (DAT_10037744 == DAT_10037748) {
        FUN_1000cfe0();
    }

    if (DAT_10037744 != nullptr) {
        *DAT_10037744 = param_1;
    }

    DAT_10037744 = DAT_10037744 + 1;
}