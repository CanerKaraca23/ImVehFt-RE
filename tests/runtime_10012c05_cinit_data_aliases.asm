.386
.model flat
option casemap:none

EXTERN _CinitNonwritableStub:PROC
EXTERN _CinitInitpStub@0:PROC
EXTERN _CinitAtexitStub:PROC

.code
PUBLIC ___IsNonwritableInCurrentImage
___IsNonwritableInCurrentImage PROC
    jmp _CinitNonwritableStub
___IsNonwritableInCurrentImage ENDP

PUBLIC ___initp_misc_cfltcvt_tab@0
___initp_misc_cfltcvt_tab@0 PROC
    jmp _CinitInitpStub@0
___initp_misc_cfltcvt_tab@0 ENDP

PUBLIC __atexit
__atexit PROC
    jmp _CinitAtexitStub
__atexit ENDP

.data
ALIGN 4

PUBLIC _DAT_100221b8
PUBLIC _DAT_100221d0
_DAT_100221b8 LABEL DWORD
    DWORD 6 DUP (0)
_DAT_100221d0 LABEL DWORD

ALIGN 4
PUBLIC _DAT_10022154
PUBLIC _DAT_100221b4
_DAT_10022154 LABEL DWORD
    DWORD 24 DUP (0)
_DAT_100221b4 LABEL DWORD

ALIGN 4
PUBLIC _PTR___fpmath_10025004
_PTR___fpmath_10025004 DWORD 0

PUBLIC _DAT_1003d554
_DAT_1003d554 DWORD 0

END
