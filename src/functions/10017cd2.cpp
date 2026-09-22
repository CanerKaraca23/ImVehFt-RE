#include <cstdint>

extern "C" void* DAT_10029d70;

extern "C" void __stdcall LeaveCriticalSection(void* lpCriticalSection);

extern "C" void __cdecl FUN_10017cd2(int param_1)
{
    LeaveCriticalSection(
        reinterpret_cast<void**>(&DAT_10029d70)[param_1 * 2]);
}