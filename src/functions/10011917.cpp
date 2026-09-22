#include <cstdint>

extern "C" std::uint32_t* __cdecl ___doserrno();
extern "C" int __cdecl __get_errno_from_oserr(std::uint32_t param_1);
extern "C" int* __cdecl __errno();

extern "C" void __cdecl __dosmaperr(std::uint32_t param_1)
{
    std::uint32_t* puVar1 = ___doserrno();
    *puVar1 = param_1;

    int iVar2 = __get_errno_from_oserr(param_1);

    int* piVar3 = __errno();
    *piVar3 = iVar2;
}