#include <cstdint>

extern "C" std::uint64_t __stdcall __aulldvrm(
    std::uint32_t param_1,
    std::uint32_t param_2,
    std::uint32_t param_3,
    std::uint32_t param_4)
{
    std::uint64_t uVar1;
    std::int64_t lVar2;
    std::uint32_t uVar3;
    int iVar4;
    std::uint32_t uVar5;
    std::uint32_t uVar6;
    std::uint32_t uVar7;
    std::uint32_t uVar8;
    std::uint32_t uVar9;

    uVar9 = param_1;
    uVar6 = param_4;
    uVar7 = param_2;
    uVar3 = param_3;

    if (param_4 == 0) {
        uVar3 = param_2 / param_3;

        iVar4 = static_cast<int>(
            ((((static_cast<std::uint64_t>(param_2) % param_3) << 32) |
              param_1) /
             param_3));
    } else {
        do {
            uVar5 = uVar6 >> 1;
            uVar3 = static_cast<std::uint32_t>(
                (((static_cast<std::uint64_t>((uVar6 & 1u) != 0) << 32) |
                  uVar3) >>
                 1));

            uVar8 = uVar7 >> 1;
            uVar9 = static_cast<std::uint32_t>(
                (((static_cast<std::uint64_t>((uVar7 & 1u) != 0) << 32) |
                  uVar9) >>
                 1));

            uVar6 = uVar5;
            uVar7 = uVar8;
        } while (uVar5 != 0);

        uVar1 =
            ((static_cast<std::uint64_t>(uVar8) << 32) | uVar9) /
            uVar3;

        iVar4 = static_cast<int>(uVar1);

        lVar2 = static_cast<std::int64_t>(
            static_cast<std::uint64_t>(param_3) *
            (uVar1 & 0xffffffffULL));

        uVar3 = static_cast<std::uint32_t>(
            static_cast<std::uint64_t>(lVar2) >> 32);

        const std::uint32_t scaled_divisor =
            static_cast<std::uint32_t>(iVar4) * param_4;

        uVar9 = uVar3 + scaled_divisor;

        const bool carry =
            (static_cast<std::uint64_t>(uVar3) + scaled_divisor) >
            0xffffffffULL;

        if (carry ||
            (param_2 < uVar9) ||
            (param_2 <= uVar9 &&
             (param_1 <
              static_cast<std::uint32_t>(lVar2)))) {
            iVar4 = iVar4 - 1;
        }

        uVar3 = 0;
    }

    return (static_cast<std::uint64_t>(uVar3) << 32) |
           static_cast<std::uint32_t>(iVar4);
}