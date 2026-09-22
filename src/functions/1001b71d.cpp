#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>

using _EXCEPTION_DISPOSITION = int;
struct EHExceptionRecord;
struct EHRegistrationNode;
struct _CONTEXT;
struct _s_FuncInfo;
struct CatchGuardRN {
    std::uint8_t _pad_00_08[8];
    std::uintptr_t security_cookie;
    _s_FuncInfo* _field_0x0c;
    EHRegistrationNode* _field_0x10;
    int _field_0x14;
};
static_assert(offsetof(CatchGuardRN, security_cookie) == 0x08);
static_assert(offsetof(CatchGuardRN, _field_0x0c) == 0x0c);
static_assert(offsetof(CatchGuardRN, _field_0x10) == 0x10);
static_assert(offsetof(CatchGuardRN, _field_0x14) == 0x14);
_EXCEPTION_DISPOSITION __cdecl CatchGuardHandler(
    EHExceptionRecord* param_1,
    CatchGuardRN* param_2,
    void* param_3,
    void* )
{
    extern std::uintptr_t __security_cookie;
    extern void __fastcall __security_check_cookie(std::uintptr_t);
    extern _EXCEPTION_DISPOSITION __cdecl ___InternalCxxFrameHandler(
        EHExceptionRecord*,
        EHRegistrationNode*,
        _CONTEXT*,
        void*,
        _s_FuncInfo*,
        int,
        EHRegistrationNode*,
        unsigned char);

    std::uintptr_t stack_cookie =
        __security_cookie ^
        reinterpret_cast<std::uintptr_t>(&stack_cookie);

    _EXCEPTION_DISPOSITION result = ___InternalCxxFrameHandler(
        param_1,
        param_2->_field_0x10,
        static_cast<_CONTEXT*>(param_3),
        nullptr,
        param_2->_field_0x0c,
        param_2->_field_0x14,
        reinterpret_cast<EHRegistrationNode*>(param_2),
        '\0');

    __security_check_cookie(
        stack_cookie ^
        reinterpret_cast<std::uintptr_t>(&stack_cookie));

    return result;
}