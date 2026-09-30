#if !defined(_MSC_VER) || !defined(_M_IX86)
#error These hook shims require the original MSVC-compatible x86 inline assembler.
#endif

// Supplemental hook bodies recovered from the bounded Ghidra CFGs for
// ImVehFt.asi. These are not among the 705 Ghidra function exports.
//
// Keep each body naked: the register/stack contract is part of the hook.
// Integration into a rebuilt image still requires relocation-aware installer
// targets and a verified mapping for the original ASI state at 0x1003xxxx.

extern "C" __declspec(naked) void __cdecl ImVehFtHook_10007F50()
{
    __asm {
        // FCOMP dword ptr [1003C258h]; XOR EAX,EAX; FNSTSW AX;
        // MOV BX,AX; MOV EDX,006E18EBh; JMP EDX.
        _emit 0D8h
        _emit 01Dh
        _emit 058h
        _emit 0C2h
        _emit 003h
        _emit 010h
        _emit 033h
        _emit 0C0h
        _emit 0DFh
        _emit 0E0h
        _emit 066h
        _emit 08Bh
        _emit 0D8h
        _emit 0BAh
        _emit 0EBh
        _emit 018h
        _emit 06Eh
        _emit 000h
        _emit 0FFh
        _emit 0E2h
    }
}

extern "C" __declspec(naked) void __cdecl ImVehFtHook_10003060()
{
    __asm {
        // PUSHAD; MOV [1003BC2Ch],ESI; MOV EAX,[1003BC2Ch];
        // CMP [EAX+594h],0Bh; JZ +7; AND byte ptr [EAX+428h],0EFh;
        // POPAD; RET.
        _emit 060h
        _emit 089h
        _emit 035h
        _emit 02Ch
        _emit 0BCh
        _emit 003h
        _emit 010h
        _emit 0A1h
        _emit 02Ch
        _emit 0BCh
        _emit 003h
        _emit 010h
        _emit 083h
        _emit 0B8h
        _emit 094h
        _emit 005h
        _emit 000h
        _emit 000h
        _emit 00Bh
        _emit 074h
        _emit 007h
        _emit 080h
        _emit 0A0h
        _emit 028h
        _emit 004h
        _emit 000h
        _emit 000h
        _emit 0EFh
        _emit 061h
        _emit 0C3h
    }
}

extern "C" __declspec(naked) void __cdecl ImVehFtHook_10003080()
{
    __asm {
        // PUSHAD; MOV [1003BC2Ch],ESI; MOV EAX,[1003BC2Ch];
        // CMP [EAX+594h],0Bh; JZ +13h; AND byte ptr [EAX+4A8h],0E7h;
        // MOV EAX,[1003BC2Ch]; AND byte ptr [EAX+428h],0BFh; POPAD; RET.
        _emit 060h
        _emit 089h
        _emit 035h
        _emit 02Ch
        _emit 0BCh
        _emit 003h
        _emit 010h
        _emit 0A1h
        _emit 02Ch
        _emit 0BCh
        _emit 003h
        _emit 010h
        _emit 083h
        _emit 0B8h
        _emit 094h
        _emit 005h
        _emit 000h
        _emit 000h
        _emit 00Bh
        _emit 074h
        _emit 013h
        _emit 080h
        _emit 0A0h
        _emit 0A8h
        _emit 004h
        _emit 000h
        _emit 000h
        _emit 0E7h
        _emit 0A1h
        _emit 02Ch
        _emit 0BCh
        _emit 003h
        _emit 010h
        _emit 080h
        _emit 0A0h
        _emit 028h
        _emit 004h
        _emit 000h
        _emit 000h
        _emit 0BFh
        _emit 061h
        _emit 0C3h
    }
}
