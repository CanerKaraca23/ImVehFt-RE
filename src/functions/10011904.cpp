#include <cstdint>

extern "C" void* __cdecl __getptd_noexit(void);

extern "C" std::uint32_t* __cdecl ___doserrno(void)
{
    struct _tiddata
    {
        std::uint32_t _tdoserrno;
    };

    extern std::uint32_t DAT_100291cc;

    _tiddata* p_Var1 =
        static_cast<_tiddata*>(__getptd_noexit());

    if (p_Var1 == nullptr)
    {
        return &DAT_100291cc;
    }

    return &p_Var1->_tdoserrno;
}