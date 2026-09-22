#include <cstdint>

extern "C" __declspec(naked) std::uint32_t __stdcall FUN_1001c9bc(void)
{
    __asm {
        test eax, 080000h
        jz add_error_constant
        mov eax, 7
        ret

    add_error_constant:
        // Explicit FADD emits the same original x87 instruction as the prior bytes.
        fadd qword ptr ds:[100258e0h]
        mov eax, 1
        ret
    }
}