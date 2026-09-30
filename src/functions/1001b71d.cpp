#include <cstdint>
#include <cstddef>

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
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);
extern std::uint32_t __cdecl ___InternalCxxFrameHandler(
    EHExceptionRecord*,
    EHRegistrationNode*,
    _CONTEXT*,
    void*,
    _s_FuncInfo*,
    int,
    EHRegistrationNode*,
    unsigned char);

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "CatchGuardHandler requires the MSVC x86 inline-assembly ABI"
#endif

__declspec(naked) _EXCEPTION_DISPOSITION __cdecl CatchGuardHandler(
    EHExceptionRecord*,
    CatchGuardRN*,
    void*,
    void*)
{
    __asm
    {
        mov edi, edi
        push ebp
        mov ebp, esp
        push esi
        cld
        mov esi, dword ptr [ebp + 0Ch]
        mov ecx, dword ptr [esi + 8]
        xor ecx, esi
        call __security_check_cookie
        push 0
        push esi
        push dword ptr [esi + 14h]
        push dword ptr [esi + 0Ch]
        push 0
        push dword ptr [ebp + 10h]
        push dword ptr [esi + 10h]
        push dword ptr [ebp + 8]
        call ___InternalCxxFrameHandler
        add esp, 20h
        pop esi
        pop ebp
        ret
    }
}
