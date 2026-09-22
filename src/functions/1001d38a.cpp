#include <cstdint>

using Address32 = std::uint32_t;

extern "C" char __cdecl ___BuildCatchObjectHelper(
    std::int32_t,
    std::int32_t*,
    std::uint32_t*,
    std::uint8_t*);

extern "C" std::int32_t __cdecl ___AdjustPointer(
    std::int32_t,
    std::int32_t*);

extern "C" void __stdcall FID_conflict__CallMemberFunction1(
    std::int32_t*,
    void*);

void __cdecl ___BuildCatchObject(
    std::int32_t param_1,
    std::int32_t* param_2,
    std::uint32_t* param_3,
    std::uint8_t* param_4)
{
    // Ghidra-injected compiler machinery: SEH_prolog4.
    // Exact frame operands are encoded by the binary's function prolog.

    std::int32_t* piVar2 = param_2;

    if ((*param_3 & 0x80000000U) == 0U)
    {
        const Address32 adjusted_address =
            param_3[2] +
            0x0CU +
            static_cast<Address32>(
                static_cast<std::int32_t>(
                    static_cast<Address32>(
                        reinterpret_cast<std::uintptr_t>(param_2))));

        piVar2 = reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(adjusted_address));
    }

    const char cVar1 =
        ___BuildCatchObjectHelper(param_1, param_2, param_3, param_4);

    if (cVar1 == 1)
    {
        ___AdjustPointer(
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(
                    static_cast<Address32>(param_1) + 0x18U)),
            reinterpret_cast<std::int32_t*>(param_4 + 8));

        FID_conflict__CallMemberFunction1(
            piVar2,
            *reinterpret_cast<void**>(param_4 + 0x18));
    }
    else if (cVar1 == 2)
    {
        ___AdjustPointer(
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(
                    static_cast<Address32>(param_1) + 0x18U)),
            reinterpret_cast<std::int32_t*>(param_4 + 8));

        FID_conflict__CallMemberFunction1(
            piVar2,
            *reinterpret_cast<void**>(param_4 + 0x18));
    }

    // Ghidra-injected compiler machinery: EH_epilog3
    // This is the replacement for the __SEH_epilog4 symbol.
}