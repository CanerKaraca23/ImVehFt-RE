#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall __NLG_Notify(unsigned long )
{
    __asm
    {
        mov ecx, dword ptr [esp + 4]
        mov dword ptr ds:IVF_RELOC_TARGET_10029E98, ecx
        mov dword ptr ds:IVF_RELOC_TARGET_10029E94, eax
        mov dword ptr ds:IVF_RELOC_TARGET_10029E9C, ebp
        ret 4
    }
}
