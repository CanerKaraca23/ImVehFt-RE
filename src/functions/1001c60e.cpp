#include <bit>
#include <emmintrin.h>

using float10 = long double;
#define ROUND(value) _mm_cvtsd_si32(_mm_set_sd((value)))
extern double DAT_10025850, DAT_10025858, DAT_10025870;
extern double _DAT_10025860, _UNK_10025868, _DAT_10025878;
extern double _DAT_10025820, _DAT_10025810, _DAT_10025840, _DAT_10025830;
extern double _UNK_10025828, _UNK_10025818, _UNK_10025848, _UNK_10025838;
extern double _DAT_10025890;
extern double DAT_10025010, DAT_10025018, DAT_10025020, DAT_10025028;
struct ReagentMathError
{
    float10 __thiscall FUN_1001b3cf();
};
struct ReagentMathFunction
{
    float10 __thiscall FUN_1001c60e();
};

float10 ReagentMathFunction::FUN_1001c60e()
{
    std::uint16_t uVar1;
    int iVar2;
    double in_XMM0_Qa;
    double dVar3;
    double dVar4;
    double dVar5;
    double dVar6;
    double dVar7;
    double dVar8;
    double dVar9;
    double dVar10;
    double dVar11;
    double dVar12;
    double dVar13;
    double dVar14;
    double dVar15;
    double dVar16;

    __asm { movsd QWORD PTR [in_XMM0_Qa], xmm0 }

    uVar1 =
        static_cast<std::uint16_t>(
            (static_cast<std::uint16_t>(
                std::bit_cast<std::uint64_t>(in_XMM0_Qa) >> 0x30) &
             0x7fffU) +
            0xcfd0U);

    if (uVar1 < 0x10c6U)
    {
        dVar8 = (DAT_10025850 * in_XMM0_Qa + DAT_10025858) - DAT_10025858;

        iVar2 =
            (static_cast<int>(ROUND(DAT_10025850 * in_XMM0_Qa)) +
             0x1c7600U &
             0x3f) *
            0x20;

        dVar9 = _DAT_10025860 * dVar8;
        dVar3 = in_XMM0_Qa - DAT_10025870 * dVar8;
        dVar13 = in_XMM0_Qa - DAT_10025870 * dVar8;
        dVar14 = dVar13 - dVar9;
        dVar4 = dVar3 - dVar9;
        dVar6 = dVar3 - _UNK_10025868 * dVar8;
        dVar5 = dVar4 * dVar4;
        dVar7 = dVar6 * dVar6;

        dVar10 =
            *reinterpret_cast<double*>(
                reinterpret_cast<std::byte*>(&DAT_10025010) + iVar2) +
            *reinterpret_cast<double*>(
                reinterpret_cast<std::byte*>(&DAT_10025028) + iVar2);

        dVar11 =
            *reinterpret_cast<double*>(
                reinterpret_cast<std::byte*>(&DAT_10025028) + iVar2) *
            dVar14;

        dVar15 =
            dVar14 *
            *reinterpret_cast<double*>(
                reinterpret_cast<std::byte*>(&DAT_10025010) + iVar2);

        dVar12 =
            dVar11 +
            *reinterpret_cast<double*>(
                reinterpret_cast<std::byte*>(&DAT_10025018) + iVar2);

        dVar16 = dVar15 + dVar12;

        return static_cast<float10>(
            dVar16 +
            (dVar8 * _DAT_10025878 - ((dVar13 - dVar14) - dVar9)) *
                (*reinterpret_cast<double*>(
                     reinterpret_cast<std::byte*>(&DAT_10025018) + iVar2) *
                     dVar14 -
                 dVar10) +
            *reinterpret_cast<double*>(
                reinterpret_cast<std::byte*>(&DAT_10025020) + iVar2) +
            (*reinterpret_cast<double*>(
                 reinterpret_cast<std::byte*>(&DAT_10025018) + iVar2) -
             dVar12) +
            dVar11 +
            (dVar12 - dVar16) +
            dVar15 +
            (_DAT_10025820 * dVar5 + _DAT_10025810 +
             (_DAT_10025840 * dVar3 * dVar4 + _DAT_10025830) * dVar5 * dVar5) *
                dVar10 *
                dVar14 *
                dVar5 +
            (_UNK_10025828 * dVar7 + _UNK_10025818 +
             (_UNK_10025848 * dVar3 * dVar6 + _UNK_10025838) * dVar7 * dVar7) *
                *reinterpret_cast<double*>(
                    reinterpret_cast<std::byte*>(&DAT_10025018) + iVar2) *
                dVar7);
    }

    if (static_cast<std::int16_t>(uVar1) < 0x10c6)
    {
        if ((uVar1 >> 4) == 0xcfdU)
        {
            return static_cast<float10>(in_XMM0_Qa * _DAT_10025890);
        }

        return static_cast<float10>(in_XMM0_Qa);
    }

    return reinterpret_cast<ReagentMathError*>(this)->FUN_1001b3cf();
}