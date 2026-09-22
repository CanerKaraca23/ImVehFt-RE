#include <cstdint>

extern "C" void ___security_init_cookie();

extern "C" int __fastcall ___DllMainCRTStartup(
    std::int32_t param_1,
    std::int32_t param_2,
    std::uint32_t param_3);

void __stdcall entry(
    std::uint32_t param_1,
    std::int32_t param_2,
    std::int32_t param_3)
{
    if (param_2 == 1)
    {
        ___security_init_cookie();
    }

    ___DllMainCRTStartup(param_3, param_2, param_1);
}