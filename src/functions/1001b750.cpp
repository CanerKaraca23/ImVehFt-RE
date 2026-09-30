#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using undefined4 = std::uint32_t;
using uint = std::uint32_t;
using undefined = unsigned char;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined8 = std::uint64_t;
#pragma warning(disable:4733)
struct EHExceptionRecord { std::uint32_t ExceptionCode; };
struct EHRegistrationNode;
struct _s_FuncInfo;
struct TranslatorGuardRN;
enum _EXCEPTION_DISPOSITION : int;
_EXCEPTION_DISPOSITION __cdecl TranslatorGuardHandler(
    EHExceptionRecord*, TranslatorGuardRN*, void*, void*);
typedef void (__cdecl code)(std::uint32_t, void*);
struct _ptiddata
{
    std::uint8_t reserved_00[0x80];
    code* _translator;
};
static_assert(offsetof(_ptiddata, _translator) == 0x80);
extern "C" _ptiddata* __cdecl __getptd(void);
extern std::uint32_t DAT_10029490;

extern "C" __declspec(naked) int __cdecl _CallSETranslator(
    EHExceptionRecord*, EHRegistrationNode*, void*, void*,
    _s_FuncInfo*, int, EHRegistrationNode*)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        sub esp, 38h
        push ebx
        cmp dword ptr [ebp+8], 123h
        jne translator_normal_path
        mov eax, OFFSET translator_exception_chain_restore
        mov ecx, dword ptr [ebp+0Ch]
        mov dword ptr [ecx], eax
        xor eax, eax
        inc eax
        jmp translator_return

    translator_normal_path:
        and dword ptr [ebp-28h], 0
        mov dword ptr [ebp-24h], OFFSET TranslatorGuardHandler
        mov eax, dword ptr [DAT_10029490]
        lea ecx, [ebp-28h]
        xor eax, ecx
        mov dword ptr [ebp-20h], eax
        mov eax, dword ptr [ebp+18h]
        mov dword ptr [ebp-1Ch], eax
        mov eax, dword ptr [ebp+0Ch]
        mov dword ptr [ebp-18h], eax
        mov eax, dword ptr [ebp+1Ch]
        mov dword ptr [ebp-14h], eax
        mov eax, dword ptr [ebp+20h]
        mov dword ptr [ebp-10h], eax
        and dword ptr [ebp-0Ch], 0
        and dword ptr [ebp-08h], 0
        and dword ptr [ebp-04h], 0
        mov dword ptr [ebp-0Ch], esp
        mov dword ptr [ebp-08h], ebp
        mov eax, fs:[0]
        mov dword ptr [ebp-28h], eax
        lea eax, [ebp-28h]
        mov fs:[0], eax
        mov dword ptr [ebp-38h], 1
        mov eax, dword ptr [ebp+8]
        mov dword ptr [ebp-34h], eax
        mov eax, dword ptr [ebp+10h]
        mov dword ptr [ebp-30h], eax
        call __getptd
        mov eax, dword ptr [eax+80h]
        mov dword ptr [ebp-2Ch], eax
        lea eax, [ebp-34h]
        push eax
        mov eax, dword ptr [ebp+8]
        push dword ptr [eax]
        call dword ptr [ebp-2Ch]
        pop ecx
        pop ecx
        and dword ptr [ebp-38h], 0

    translator_exception_chain_restore:
        cmp dword ptr [ebp-04h], 0
        jz translator_restore_fs_link
        mov ebx, fs:[0]
        mov eax, dword ptr [ebx]
        mov ebx, dword ptr [ebp-28h]
        mov dword ptr [ebx], eax
        mov fs:[0], ebx
        jmp translator_return_value

    translator_restore_fs_link:
        mov eax, dword ptr [ebp-28h]
        mov fs:[0], eax

    translator_return_value:
        mov eax, dword ptr [ebp-38h]

    translator_return:
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}
