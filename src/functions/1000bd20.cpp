#include <cstdint>

extern std::uint32_t** DAT_1003c3cc;
extern std::uint32_t* DAT_100378d8;
extern std::uint32_t* DAT_100378dc;
extern std::uint32_t* DAT_100378e0;
extern std::uint32_t* PTR_vftable_100378b0;

struct __single_inheritance FUN_1000bca0_this {
    void __thiscall FUN_1000bca0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000bd20(std::uint32_t param_1)
{
    int iVar1;

    if (DAT_1003c3cc == nullptr) {
        DAT_1003c3cc =
            reinterpret_cast<std::uint32_t**>(&PTR_vftable_100378b0);

        using Initializer = decltype(&FUN_1000bca0_this::FUN_1000bca0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_100378b0) + 4u);
(reinterpret_cast<FUN_1000bca0_this*>(DAT_1003c3cc)->*initializer)(

            0x53ead3u,
            0,
            0,
            0,
            0);
    }

    if ((&param_1 < DAT_100378dc) &&
        (DAT_100378d8 <= &param_1)) {
        iVar1 = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(&param_1) -
            reinterpret_cast<std::uintptr_t>(DAT_100378d8));

        if (DAT_100378dc == DAT_100378e0) {
            FUN_1000cfe0();
        }

        if (DAT_100378dc != nullptr) {
            *DAT_100378dc = DAT_100378d8[iVar1 >> 2];
        }

        DAT_100378dc = DAT_100378dc + 1;
        return;
    }

    if (DAT_100378dc == DAT_100378e0) {
        FUN_1000cfe0();
    }

    if (DAT_100378dc != nullptr) {
        *DAT_100378dc = param_1;
    }

    DAT_100378dc = DAT_100378dc + 1;
}