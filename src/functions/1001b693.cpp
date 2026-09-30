#include <cstdint>
#include "gta_sa_address_access.hpp"
#pragma warning(disable:4733)

struct EHRegistrationNode;
struct EHExceptionRecord;


extern "C" void __stdcall ImVehFt_Recovered_RtlUnwind(
    void* target_frame,
    void* target_ip,
    void* exception_record,
    void* return_value);

extern "C" __declspec(naked) void __stdcall _UnwindNestedFrames(
    EHRegistrationNode*, EHExceptionRecord*)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        push ecx
        push ecx
        push ebx
        push esi
        push edi
        mov esi, fs:[0]
        mov dword ptr [ebp-4], esi
        mov dword ptr [ebp-8], OFFSET unwind_nested_frames_continue
        push 0
        push dword ptr [ebp+0Ch]
        push dword ptr [ebp-8]
        push dword ptr [ebp+8]
        call ImVehFt_Recovered_RtlUnwind

    unwind_nested_frames_continue:
        mov eax, dword ptr [ebp+0Ch]
        mov eax, dword ptr [eax+4]
        and eax, 0FFFFFFFDh
        mov ecx, dword ptr [ebp+0Ch]
        mov dword ptr [ecx+4], eax
        mov edi, fs:[0]
        mov ebx, dword ptr [ebp-4]
        mov dword ptr [ebx], edi
        mov fs:[0], ebx
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret 8
    }
}
