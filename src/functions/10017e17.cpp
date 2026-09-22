#include <cstddef>
#include <cstdint>

struct _ptiddata
{
    std::uint8_t reserved_0000_007b[0x7c];
    void (__cdecl* _unexpected)(void);
};
static_assert(offsetof(_ptiddata, _unexpected) == 0x7c);

extern "C" _ptiddata* __cdecl __getptd(void);
extern "C" [[noreturn]] void __cdecl terminate(void);

extern "C" void __stdcall FUN_10017e17(void)
{
    _ptiddata* threadData = __getptd();

    if (threadData->_unexpected != nullptr) {
        (*threadData->_unexpected)();
    }

    terminate();
}