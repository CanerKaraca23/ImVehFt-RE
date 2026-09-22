#include <cstdint>
#include <cstddef>
struct _ptiddata { std::uint8_t _reserved_00[0x90]; int _ProcessingThrow; };
static_assert(offsetof(_ptiddata, _ProcessingThrow) == 0x90);
extern "C" _ptiddata* __cdecl __getptd(void);
extern "C" void __cdecl _inconsistency(void);
extern "C" void __stdcall __CallSettingFrame_12(std::uint32_t, std::uint32_t, int);
extern "C" void __stdcall FUN_1001cece(void);

void __stdcall FUN_1001cece(void)
{
    _ptiddata* p_Var1 = __getptd();

    if (0 < p_Var1->_ProcessingThrow)
    {
        p_Var1 = __getptd();
        p_Var1->_ProcessingThrow = p_Var1->_ProcessingThrow + -1;
    }

    return;
}