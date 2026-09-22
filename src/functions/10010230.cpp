#include <cstddef>

extern "C" void* __cdecl FUN_10010893(std::size_t size);

extern "C" __declspec(naked) void __cdecl FUN_10010230(std::size_t)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        pop ebp
        jmp FUN_10010893
    }
}
