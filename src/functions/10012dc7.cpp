#include <cstddef>
#include <cstdint>

extern "C" void __cdecl FUN_10017cd2(std::int32_t param_1);

extern "C" __declspec(naked) void __stdcall FUN_10012dc7(void)
{
    // Ghidra shows this as a frameless helper that reads its caller's EBP+0x10.
    // Keep the incoming EBP and caller-cleaned stack ABI rather than substituting
    // this function's own frame or return-address-relative storage.
    __asm {
        cmp dword ptr [ebp + 10h], 0
        jz no_call
        push 8
        call FUN_10017cd2
        pop ecx
    no_call:
        ret
    }
}