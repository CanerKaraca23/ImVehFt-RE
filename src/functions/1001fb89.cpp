#include <cstdint>

extern "C" std::uint32_t __fastcall ___hw_cw_sse2(
    std::uint32_t ,
    std::uint32_t param_2)
{
    std::uint32_t uVar1 = 0;
    std::uint32_t uVar2;

    if ((param_2 & 0x10u) != 0) {
        uVar1 = 0x80u;
    }
    if ((param_2 & 8u) != 0) {
        uVar1 = uVar1 | 0x200u;
    }
    if ((param_2 & 4u) != 0) {
        uVar1 = uVar1 | 0x400u;
    }
    if ((param_2 & 2u) != 0) {
        uVar1 = uVar1 | 0x800u;
    }
    if ((param_2 & 1u) != 0) {
        uVar1 = uVar1 | 0x1000u;
    }
    if ((param_2 & 0x80000u) != 0) {
        uVar1 = uVar1 | 0x100u;
    }

    uVar2 = param_2 & 0x300u;
    if (uVar2 != 0) {
        if (uVar2 == 0x100u) {
            uVar1 = uVar1 | 0x2000u;
        }
        else if (uVar2 == 0x200u) {
            uVar1 = uVar1 | 0x4000u;
        }
        else if (uVar2 == 0x300u) {
            uVar1 = uVar1 | 0x6000u;
        }
    }

    uVar2 = param_2 & 0x3000000u;
    if (uVar2 == 0x1000000u) {
        uVar1 = uVar1 | 0x8040u;
    }
    else {
        if (uVar2 == 0x2000000u) {
            return uVar1 | 0x40u;
        }
        if (uVar2 == 0x3000000u) {
            return uVar1 | 0x8000u;
        }
    }

    return uVar1;
}