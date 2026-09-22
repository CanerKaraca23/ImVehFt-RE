#include <cstdint>

using RawDllMain = std::int32_t(__stdcall*)(
    std::uint32_t,
    std::int32_t,
    std::int32_t);

extern std::int32_t DAT_100399f0;
extern RawDllMain DAT_10022268;

extern "C" void __cdecl __SEH_prolog4();
extern "C" void __stdcall __SEH_epilog4();

extern "C" std::int32_t __stdcall __CRT_INIT_12(
    std::uint32_t,
    std::int32_t,
    std::int32_t);

extern "C" std::int32_t __stdcall FUN_10001db0(
    std::uint32_t,
    std::int32_t);

extern "C" std::int32_t __fastcall ___DllMainCRTStartup(
    std::int32_t param_1,
    std::int32_t param_2,
    std::uint32_t param_3)
{
    __SEH_prolog4();

    std::int32_t local_20 = 1;

    if ((param_2 == 0) && (DAT_100399f0 == 0))
    {
        local_20 = 0;
    }
    else
    {
        if ((param_2 == 1) || (param_2 == 2))
        {
            if (DAT_10022268 != nullptr)
            {
                local_20 = DAT_10022268(
                    param_3,
                    param_2,
                    param_1);
            }

            if ((local_20 == 0) ||
                (__CRT_INIT_12(param_3, param_2, param_1) == 0))
            {
                local_20 = 0;
                goto cleanup;
            }
        }

        local_20 = FUN_10001db0(param_3, param_2);

        if ((param_2 == 1) && (local_20 == 0))
        {
            FUN_10001db0(param_3, 0);
            __CRT_INIT_12(param_3, 0, param_1);

            if (DAT_10022268 != nullptr)
            {
                DAT_10022268(param_3, 0, param_1);
            }
        }

        if ((param_2 == 0) || (param_2 == 3))
        {
            if (__CRT_INIT_12(param_3, param_2, param_1) == 0)
            {
                local_20 = 0;
            }

            if ((local_20 != 0) && (DAT_10022268 != nullptr))
            {
                local_20 = DAT_10022268(
                    param_3,
                    param_2,
                    param_1);
            }
        }
    }

cleanup:
    __SEH_epilog4();
    return local_20;
}