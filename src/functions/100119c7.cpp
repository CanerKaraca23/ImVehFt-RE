#include <cstdint>

extern "C" std::uint32_t __fastcall __inc(std::uint32_t, void*);
extern "C" int __cdecl _isspace(int);

// __whiteout is a custom x86 entry: ECX and ESI are live-in registers, and
// the caller cleans the stream argument after this routine's plain RET.
extern "C" __declspec(naked) std::uint32_t __cdecl __whiteout(void)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        push ebx
    whiteout_loop:
        mov edx, dword ptr [ebp + 8]
        inc dword ptr [esi]
        call __inc
        mov ebx, eax
        cmp ebx, -1
        jz whiteout_return
        movzx eax, bl
        push eax
        call _isspace
        pop ecx
        test eax, eax
        jnz whiteout_loop
    whiteout_return:
        mov eax, ebx
        pop ebx
        pop ebp
        ret
    }
}