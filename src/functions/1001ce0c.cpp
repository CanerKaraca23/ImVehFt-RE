#include <cstdint>
#include <cstddef>
struct _ptiddata { std::uint8_t _reserved_00[0x90]; int _ProcessingThrow; };
static_assert(offsetof(_ptiddata, _ProcessingThrow) == 0x90);
extern "C" _ptiddata* __cdecl __getptd(void);
extern "C" void __cdecl _inconsistency(void);
extern "C" void __stdcall __CallSettingFrame_12(std::uint32_t, std::uint32_t, int);
extern "C" void __stdcall FUN_1001cece(void);

void __cdecl ___FrameUnwindToState(
    int param_1,
    unsigned int param_2,
    int param_3,
    int param_4)
{
    int state;
    int currentState;

    if (*reinterpret_cast<int*>(
            static_cast<unsigned int>(param_3) + 4u) < 0x81)
    {
        state = static_cast<int>(
            *reinterpret_cast<signed char*>(
                static_cast<unsigned int>(param_1) + 8u));
    }
    else
    {
        state = *reinterpret_cast<int*>(
            static_cast<unsigned int>(param_1) + 8u);
    }

    auto* ptd = __getptd();
    ptd->_ProcessingThrow = ptd->_ProcessingThrow + 1;

    while ((currentState = state) != param_4)
    {
        if ((currentState < 0) ||
            (*reinterpret_cast<int*>(
                static_cast<unsigned int>(param_3) + 4u) <= currentState))
        {
            _inconsistency();
        }

        auto* unwindMap = reinterpret_cast<int*>(
            static_cast<unsigned int>(
                *reinterpret_cast<unsigned int*>(
                    static_cast<unsigned int>(param_3) + 8u)));

        state = unwindMap[currentState * 2];

        if (unwindMap[currentState * 2 + 1] != 0)
        {
            *reinterpret_cast<int*>(
                static_cast<unsigned int>(param_1) + 8u) = state;

            __CallSettingFrame_12(
                unwindMap[currentState * 2 + 1],
                param_1,
                0x103);
        }
    }

    FUN_1001cece();

    if (currentState != param_4)
    {
        _inconsistency();
    }

    *reinterpret_cast<int*>(
        static_cast<unsigned int>(param_1) + 8u) = currentState;

    (void)param_2;
}