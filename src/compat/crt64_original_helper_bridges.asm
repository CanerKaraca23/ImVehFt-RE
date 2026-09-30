; x86 CRT arithmetic bridges for the exact original-image helpers.
; The final placement resolver must bind ___alldvrm@16 to 0x1001DDA0 and
; ___aulldvrm@16 to 0x1001A900, not to diagnostic-link addresses.

.386
.model flat
option casemap:none

EXTERN ___alldvrm@16:PROC
EXTERN ___aulldvrm@16:PROC

PUBLIC _ivf_crt_alldiv_from_alldvrm@16
PUBLIC _ivf_crt_allrem_from_alldvrm@16
PUBLIC _ivf_crt_aulldiv_from_aulldvrm@16

.code

; These bridges use the helper's 32-bit stack ABI: two 64-bit values,
; low dword then high dword for each value; callee removes 16 argument bytes.
; Save EBX because the quotient/remainder helpers use it as a return register.

_ivf_crt_alldiv_from_alldvrm@16 PROC
    push ebx
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    call ___alldvrm@16
    pop ebx
    ret 10h
_ivf_crt_alldiv_from_alldvrm@16 ENDP

_ivf_crt_allrem_from_alldvrm@16 PROC
    push ebx
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    call ___alldvrm@16
    mov edx, ebx
    mov eax, ecx
    pop ebx
    ret 10h
_ivf_crt_allrem_from_alldvrm@16 ENDP

_ivf_crt_aulldiv_from_aulldvrm@16 PROC
    push ebx
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    push dword ptr [esp + 14h]
    call ___aulldvrm@16
    pop ebx
    ret 10h
_ivf_crt_aulldiv_from_aulldvrm@16 ENDP

END
