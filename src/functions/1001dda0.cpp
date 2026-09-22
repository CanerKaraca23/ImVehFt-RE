#include <cstdint>

extern "C" std::uint64_t __stdcall __alldvrm(
    std::uint32_t param_1,
    std::uint32_t param_2,
    std::uint32_t param_3,
    std::uint32_t param_4)
{
    std::uint64_t uVar1;
    std::int32_t iVar4;
    std::uint32_t uVar3;
    std::uint32_t uVar5;
    std::uint32_t uVar6;
    std::uint32_t uVar7;
    std::uint32_t uVar8;
    std::uint32_t uVar9;
    bool bVar10;
    char cVar11;

    cVar11 = static_cast<char>(
        static_cast<std::int32_t>(param_2) < 0);

    if (cVar11 != 0)
    {
        bVar10 = param_1 != 0;
        param_1 = 0u - param_1;
        param_2 = 0u - static_cast<std::uint32_t>(bVar10) - param_2;
    }

    if (static_cast<std::int32_t>(param_4) < 0)
    {
        cVar11 = static_cast<char>(cVar11 + 1);
        bVar10 = param_3 != 0;
        param_3 = 0u - param_3;
        param_4 = 0u - static_cast<std::uint32_t>(bVar10) - param_4;
    }

    uVar7 = param_1;
    uVar3 = param_3;
    uVar5 = param_2;
    uVar9 = param_4;

    if (param_4 == 0)
    {
        uVar3 = param_2 / param_3;

        iVar4 = static_cast<std::int32_t>(
            ((static_cast<std::uint64_t>(param_2 % param_3) << 32) |
             static_cast<std::uint64_t>(param_1)) /
            static_cast<std::uint64_t>(param_3));
    }
    else
    {
        do
        {
            uVar8 = uVar9 >> 1;

            uVar3 = static_cast<std::uint32_t>(
                ((static_cast<std::uint64_t>(uVar9 & 1u) << 32) |
                 static_cast<std::uint64_t>(uVar3)) >> 1);

            uVar6 = uVar5 >> 1;

            uVar7 = static_cast<std::uint32_t>(
                ((static_cast<std::uint64_t>(uVar5 & 1u) << 32) |
                 static_cast<std::uint64_t>(uVar7)) >> 1);

            uVar5 = uVar6;
            uVar9 = uVar8;
        }
        while (uVar8 != 0);

        uVar1 =
            ((static_cast<std::uint64_t>(uVar6) << 32) |
             static_cast<std::uint64_t>(uVar7)) /
            static_cast<std::uint64_t>(uVar3);

        iVar4 = static_cast<std::int32_t>(uVar1);

        const std::uint64_t lVar2 =
            static_cast<std::uint64_t>(param_3) *
            (uVar1 & 0xffffffffull);

        uVar3 = static_cast<std::uint32_t>(lVar2 >> 32);

        const std::uint32_t correction =
            static_cast<std::uint32_t>(iVar4) * param_4;

        const std::uint32_t previous_uVar3 = uVar3;
        uVar7 = uVar3 + correction;

        const bool carry = uVar7 < previous_uVar3;

        if (carry ||
            (param_2 < uVar7) ||
            ((param_2 <= uVar7) &&
             (param_1 < static_cast<std::uint32_t>(lVar2))))
        {
            iVar4 = static_cast<std::int32_t>(
                static_cast<std::uint32_t>(iVar4) - 1u);
        }

        uVar3 = 0;
    }

    if (cVar11 == 1)
    {
        bVar10 = iVar4 != 0;
        iVar4 = static_cast<std::int32_t>(
            0u - static_cast<std::uint32_t>(iVar4));
        uVar3 = 0u - static_cast<std::uint32_t>(bVar10) - uVar3;
    }

    return (static_cast<std::uint64_t>(uVar3) << 32) |
           static_cast<std::uint32_t>(iVar4);
}