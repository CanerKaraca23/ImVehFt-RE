extern "C" void __cdecl FUN_10003fb0(unsigned int, unsigned int);
extern "C" void __cdecl FUN_10003fe0(int, int);

extern "C" __declspec(naked) void __stdcall FUN_10003f80()
{
    __asm {
        push edi
        push OFFSET FUN_10003fe0
        push esi
        mov eax, 07F1200h
        call eax
        push edi
        push OFFSET FUN_10003fb0
        push esi
        mov ecx, 07F0DC0h
        call ecx
        add esp, 18h
        mov eax, esi
        ret
    }
}
