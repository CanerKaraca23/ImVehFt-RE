#include <cstdint>
#include "gta_sa_address_access.hpp"

#pragma comment(linker, "/alternatename:__local_unwind4=___local_unwind4")

extern "C" std::uint32_t DAT_10029490;

extern "C" void __stdcall __NLG_Notify(unsigned long);
extern "C" void __stdcall FUN_10018f94();
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);
extern "C" void __cdecl __local_unwind4(
    std::uint32_t* param_1,
    int param_2,
    std::uint32_t param_3);

using UnwindHandler = std::uint32_t (__cdecl*)(void*, void*, void*, void*);

__declspec(naked) static std::uint32_t __cdecl imvehft_unwind_handler4(
    void*,
    void*,
    void*,
    void*)
{
    __asm
    {
        mov ecx, dword ptr [esp + 4]
        test dword ptr [ecx + 4], 6
        mov eax, 1
        jz handler_done
        mov eax, dword ptr [esp + 8]
        mov ecx, dword ptr [eax + 8]
        xor ecx, eax
        call __security_check_cookie
        push ebp
        mov ebp, dword ptr [eax + 18h]
        push dword ptr [eax + 0Ch]
        push dword ptr [eax + 10h]
        push dword ptr [eax + 14h]
        call __local_unwind4
        add esp, 0Ch
        pop ebp
        mov eax, dword ptr [esp + 8]
        mov edx, dword ptr [esp + 10h]
        mov dword ptr [edx], eax
        mov eax, 3
    handler_done:
        ret
    }
}

extern "C" void __cdecl __local_unwind4(
    std::uint32_t* param_1,
    int param_2,
    std::uint32_t param_3)
{
    struct RegistrationRecord
    {
        void* previous;
        UnwindHandler handler;
        std::uint32_t cookie;
    };

    RegistrationRecord registration{
        IMVEHFT_READ_EXCEPTION_LIST(),
        &imvehft_unwind_handler4,
        DAT_10029490 ^
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(&registration))
    };

    IMVEHFT_WRITE_EXCEPTION_LIST(&registration);

    while (true)
    {
        const std::uint32_t state =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(param_2) + 0x0Cu);

        if (state == 0xFFFFFFFEu ||
            (param_3 != 0xFFFFFFFEu && state <= param_3))
        {
            break;
        }

        auto* unwind_entry =
            reinterpret_cast<std::uint32_t*>(
                ((*reinterpret_cast<std::uint32_t*>(
                      static_cast<std::uintptr_t>(param_2) + 0x08u) ^
                  *param_1) +
                 0x10u) +
                state * 0x0Cu);

        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(param_2) + 0x0Cu) =
            unwind_entry[0];

        if (unwind_entry[1] == 0)
        {
            __NLG_Notify(0x101u);
            FUN_10018f94();
        }
    }

    IMVEHFT_WRITE_EXCEPTION_LIST(registration.previous);
}
