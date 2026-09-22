#include <cstdint>
#include <intrin.h>

extern "C" bool __cdecl __handle_exc(
    std::uint32_t,
    double*,
    std::uint32_t);

extern "C" void __cdecl __raise_exc(
    std::uint32_t*,
    std::uint32_t*,
    std::uint32_t,
    int,
    std::uint32_t*,
    std::uint32_t*);

extern "C" int __stdcall __ctrlfp(void);
extern "C" std::uint32_t __stdcall FUN_1002044b(void);
extern "C" void __cdecl __set_errno_from_matherr(int);
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);

extern "C" std::uint32_t DAT_10029490;
extern "C" std::uint32_t DAT_100396d8;

void __cdecl __87except(
    int param_1,
    int* param_2,
    std::uint16_t* param_3)
{
    const std::uint32_t local_14 =
        DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) &
            ~static_cast<std::uintptr_t>(0x0f));

    const std::uint32_t local_98 = static_cast<std::uint32_t>(*param_3);

    std::uint32_t local_94;
    std::uint32_t local_90[12];
    std::uint64_t local_60;
    std::uint32_t local_50;

    const int iVar2 = *param_2;

    if (iVar2 == 1)
    {
        local_94 = 8;
    }
    else if (iVar2 == 2)
    {
        local_94 = 4;
    }
    else if (iVar2 == 3)
    {
        local_94 = 0x11;
    }
    else if (iVar2 == 4)
    {
        local_94 = 0x12;
    }
    else
    {
        if (iVar2 == 5)
        {
            local_94 = 8;
        }
        else if (iVar2 == 7)
        {
            *param_2 = 1;
            goto finish;
        }
        else
        {
            if (iVar2 != 8)
            {
                goto finish;
            }

            local_94 = 0x10;
        }
    }

    if (!__handle_exc(
            local_94,
            reinterpret_cast<double*>(param_2 + 6),
            local_98))
    {
        if ((param_1 == 0x10) ||
            (param_1 == 0x16) ||
            (param_1 == 0x1d))
        {
            local_60 = *reinterpret_cast<std::uint64_t*>(param_2 + 4);
            local_50 = (local_50 & 0xffffffe3U) | 3U;
        }
        else
        {
            local_50 = local_50 & 0xfffffffeU;
        }

        __raise_exc(
            local_90,
            const_cast<std::uint32_t*>(&local_98),
            local_94,
            param_1,
            reinterpret_cast<std::uint32_t*>(param_2 + 2),
            reinterpret_cast<std::uint32_t*>(param_2 + 6));
    }

finish:
    __ctrlfp();

    if ((*param_2 != 8) &&
        (DAT_100396d8 == 0) &&
        (FUN_1002044b() != 0))
    {
        __security_check_cookie(local_14);
        return;
    }

    __set_errno_from_matherr(*param_2);

    __security_check_cookie(local_14);
    return;
}