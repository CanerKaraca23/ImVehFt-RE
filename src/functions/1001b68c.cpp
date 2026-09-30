extern "C" __declspec(naked) void __stdcall FID_conflict__CallMemberFunction1(
    unsigned int,
    void*)
{
    __asm {
        pop eax
        pop ecx
        xchg dword ptr [esp], eax
        jmp eax
    }
}
