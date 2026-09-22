#include <cstdint>

using LPVOID = void*;
using SIZE_T = std::uint32_t;
using DWORD = std::uint32_t;
using BOOL = std::int32_t;

extern "C" BOOL __stdcall VirtualProtect(
    LPVOID,
    SIZE_T,
    DWORD,
    DWORD*
);

extern "C" void* __cdecl _memset(
    void*,
    int,
    SIZE_T
);

extern "C" void __cdecl FUN_10008e40(LPVOID param_1)
{
    SIZE_T unaff_ESI;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm mov unaff_ESI, esi
#elif defined(__i386__)
    __asm__ volatile("movl %%esi, %0" : "=r"(unaff_ESI));
#else
    register SIZE_T esi_value asm("esi");
    unaff_ESI = esi_value;
#endif

    LPVOID local_18 = nullptr;
    SIZE_T in_stack_ffffffec;
    DWORD local_10;
    bool local_c;
    DWORD local_8;

    if (unaff_ESI == 0)
    {
        local_c = false;
    }
    else
    {
        local_18 = param_1;
        BOOL result = VirtualProtect(param_1, unaff_ESI, 0x40, &local_10);
        local_c = result != 0;
        in_stack_ffffffec = unaff_ESI;
    }

    _memset(param_1, 0x90, unaff_ESI);

    if (local_c != false)
    {
        local_8 = local_10;
        VirtualProtect(local_18, in_stack_ffffffec, local_10, &local_8);
    }
}