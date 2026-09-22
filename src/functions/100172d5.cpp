#include <cstdint>

extern "C" std::uintptr_t DAT_10029490;

extern "C" [[noreturn]] void __cdecl ___report_gsfailure();

extern "C" void __fastcall __security_check_cookie(
    std::uintptr_t _StackCookie)
{
    if (_StackCookie == DAT_10029490) {
        return;
    }

    ___report_gsfailure();
}