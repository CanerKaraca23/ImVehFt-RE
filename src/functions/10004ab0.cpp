#include <cstdint>


extern "C" int __cdecl FID_conflict__sscanf(
    char* source,
    char* format,
    ...);

extern "C" void __stdcall FUN_10004000();

extern "C" void __cdecl FUN_10004ab0_impl(void* this_, std::uint32_t param_1)
{
    std::int32_t unaff_ESI;
    __asm mov unaff_ESI, esi
    if (*reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(unaff_ESI) + 0x350) != 0)
    {
        std::int32_t local_8 =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(this_));

        FID_conflict__sscanf(
            reinterpret_cast<char*>(
                reinterpret_cast<std::uintptr_t>(this_) + 8),
            const_cast<char*>("%d"),
            &local_8);

        auto* puVar1 = reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(unaff_ESI) +
            0x340 +
            local_8 * 0x14);

        puVar1[3] =
            *reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(unaff_ESI) + 0x350) + 8)
            + -0x18
            + local_8 * 0x18;

        *puVar1 = param_1;
        puVar1[4] = 0;
        *reinterpret_cast<std::uint16_t*>(puVar1 + 2) = 0;

        FUN_10004000();
    }
}

extern "C" void __cdecl FUN_10004ab0_impl(void* this_, std::uint32_t param_1);

extern "C" __declspec(naked) void FUN_10004ab0()
{
    __asm {
        push dword ptr [esp + 4]
        push ecx
        call FUN_10004ab0_impl
        add esp, 8
        ret
    }
}
