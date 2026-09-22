#include <cstdint>
#include <windows.h>

extern "C" void __cdecl ___addlocaleref(LONG* param_1);
extern "C" LONG* __cdecl ___removelocaleref(LONG* param_1);
extern "C" void __cdecl ___freetlocinfo(void* param_1);

extern "C" LONG DAT_10029b30;

extern "C" LONG* __cdecl __updatetlocinfoEx_nolock(
    std::uint32_t* param_1,
    LONG* param_2)
{
    LONG* pLVar1;

    if (param_2 == nullptr || param_1 == nullptr)
    {
        param_2 = nullptr;
    }
    else
    {
        pLVar1 = reinterpret_cast<LONG*>(
            static_cast<std::uintptr_t>(*param_1));

        if (pLVar1 != param_2)
        {
            *param_1 = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(param_2));

            ___addlocaleref(param_2);

            if (pLVar1 != nullptr &&
                (___removelocaleref(pLVar1), *pLVar1 == 0) &&
                pLVar1 != &DAT_10029b30)
            {
                ___freetlocinfo(pLVar1);
            }
        }
    }

    return param_2;
}