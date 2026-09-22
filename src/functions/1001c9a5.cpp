#include <cstdint>

// Applies the caller-selected x87 rounding-control bits and masks exceptions.
// The original routine is a leaf thunk that deliberately reads its argument
// directly from the x86 stack and leaves stack cleanup to the caller.
extern "C" __declspec(naked) std::uint32_t __cdecl FUN_1001c9a5(void)
{
    __asm {
        mov edx, dword ptr [esp + 4]
        and edx, 0300h
        or edx, 07fh
        mov word ptr [esp + 6], dx
        fldcw word ptr [esp + 6]
        ret
    }
}
