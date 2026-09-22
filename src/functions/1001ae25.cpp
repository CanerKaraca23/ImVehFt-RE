#include <Windows.h>
#include <cstdint>
#include <intrin.h>

extern "C" void __stdcall FUN_100172cd();

extern "C" [[noreturn]] void __cdecl ___report_gsfailure()
{
    extern volatile std::uint32_t _DAT_1003a4b0;
    extern volatile void* _DAT_1003a4b4;
    extern volatile std::uint32_t _DAT_1003a3f0;
    extern volatile std::uint32_t _DAT_1003a398;
    extern volatile std::uint32_t _DAT_1003a39c;
    extern volatile std::uint32_t _DAT_1003a3a4;
    extern volatile std::uint16_t _DAT_1003a47c;
    extern volatile std::uint16_t _DAT_1003a480;
    extern volatile std::uint16_t _DAT_1003a484;
    extern volatile std::uint16_t _DAT_1003a488;
    extern volatile std::uint32_t _DAT_1003a48c;
    extern volatile std::uint32_t _DAT_1003a490;
    extern volatile std::uint32_t _DAT_1003a494;
    extern volatile std::uint32_t _DAT_1003a498;
    extern volatile std::uint32_t _DAT_1003a49c;
    extern volatile std::uint32_t _DAT_1003a4a0;
    extern volatile std::uint32_t _DAT_1003a4a4;
    extern volatile std::uint32_t DAT_1003a4a8;
    extern volatile std::uint16_t _DAT_1003a4ac;
    extern volatile std::uint16_t _DAT_1003a4b8;
    extern volatile std::uint32_t DAT_1003a3e8;
    extern volatile std::uint32_t DAT_10029490;
    extern volatile std::uint32_t DAT_10029494;
    extern volatile void* PTR_DAT_10024208;

    std::uint32_t in_EAX;
    std::uint32_t in_ECX;
    std::uint32_t in_EDX;
    std::uint32_t unaff_EBX;
    std::uint32_t unaff_EBP;
    std::uint32_t unaff_ESI;
    std::uint32_t unaff_EDI;
    std::uint32_t eflags;

    std::uint16_t in_ES;
    std::uint16_t in_CS;
    std::uint16_t in_SS;
    std::uint16_t in_DS;
    std::uint16_t in_FS;
    std::uint16_t in_GS;

    std::uint32_t local_32c;
    std::uint32_t local_328;

    __asm
    {
        mov in_EAX, eax
        mov in_ECX, ecx
        mov in_EDX, edx
        mov unaff_EBX, ebx
        mov unaff_EBP, ebp
        mov unaff_ESI, esi
        mov unaff_EDI, edi

        pushfd
        popfd

        mov ax, es
        mov in_ES, ax
        mov ax, cs
        mov in_CS, ax
        mov ax, ss
        mov in_SS, ax
        mov ax, ds
        mov in_DS, ax
        mov ax, fs
        mov in_FS, ax
        mov ax, gs
        mov in_GS, ax
    }

    const std::uint32_t return_address =
        *reinterpret_cast<const std::uint32_t*>(_AddressOfReturnAddress());

    const std::uint32_t stack0 =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_32c));

    const std::uint32_t stack0xfffffffc = stack0 - 4u;
    const std::uint32_t stack0x00000004 = stack0 + 4u;

    std::uint32_t parity_value = stack0 & 0xffu;
    parity_value ^= parity_value >> 4;
    parity_value ^= parity_value >> 2;
    parity_value ^= parity_value >> 1;

    _DAT_1003a4b0 =
        static_cast<std::uint32_t>((eflags >> 14) & 1u) * 0x4000u |
        static_cast<std::uint32_t>(
            ((stack0xfffffffc ^ 0x328u) &
             (stack0xfffffffc ^
              (stack0xfffffffc - 0x328u)) &
             0x80000000u) != 0u) * 0x800u |
        static_cast<std::uint32_t>((eflags >> 9) & 1u) * 0x200u |
        static_cast<std::uint32_t>((eflags >> 8) & 1u) * 0x100u |
        static_cast<std::uint32_t>(
            static_cast<std::int32_t>(stack0) < 0) * 0x80u |
        static_cast<std::uint32_t>(stack0 == 0x32cu) * 0x40u |
        static_cast<std::uint32_t>((eflags >> 4) & 1u) * 0x10u |
        static_cast<std::uint32_t>((parity_value & 1u) == 0u) * 4u |
        static_cast<std::uint32_t>(stack0xfffffffc < 0x328u) |
        static_cast<std::uint32_t>((eflags >> 21) & 1u) * 0x200000u |
        static_cast<std::uint32_t>((eflags >> 20) & 1u) * 0x100000u |
        static_cast<std::uint32_t>((eflags >> 19) & 1u) * 0x80000u |
        static_cast<std::uint32_t>((eflags >> 18) & 1u) * 0x40000u;

    _DAT_1003a4b4 =
        reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(stack0x00000004));

    _DAT_1003a3f0 = 0x10001u;
    _DAT_1003a398 = 0xc0000409u;
    _DAT_1003a39c = 1u;

    local_32c = DAT_10029490;
    local_328 = DAT_10029494;

    _DAT_1003a3a4 = return_address;

    _DAT_1003a47c = in_GS;
    _DAT_1003a480 = in_FS;
    _DAT_1003a484 = in_ES;
    _DAT_1003a488 = in_DS;
    _DAT_1003a48c = unaff_EDI;
    _DAT_1003a490 = unaff_ESI;
    _DAT_1003a494 = unaff_EBX;
    _DAT_1003a498 = in_EDX;
    _DAT_1003a49c = in_ECX;
    _DAT_1003a4a0 = in_EAX;
    _DAT_1003a4a4 = unaff_EBP;
    DAT_1003a4a8 = return_address;
    _DAT_1003a4ac = in_CS;
    _DAT_1003a4b8 = in_SS;

    DAT_1003a3e8 = IsDebuggerPresent();

    FUN_100172cd();

    SetUnhandledExceptionFilter(nullptr);

    UnhandledExceptionFilter(
        reinterpret_cast<_EXCEPTION_POINTERS*>(&PTR_DAT_10024208));

    if (DAT_1003a3e8 == 0u)
        FUN_100172cd();

    TerminateProcess(GetCurrentProcess(), 0xc0000409u);
    __assume(0);
}