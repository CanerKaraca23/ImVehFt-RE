#include <cstdint>

extern "C" void __cdecl FUN_10009610_relocatable_entry();

extern std::uint32_t __stdcall FUN_1000d460();
extern std::uint32_t __stdcall FUN_1000d4c0();
extern std::uint32_t __stdcall FUN_1000d520();
extern std::uint32_t __stdcall FUN_1000d580();
extern std::uint32_t __stdcall FUN_1000d5e0();
extern std::uint32_t __stdcall FUN_1000d640();
extern std::uint32_t __stdcall FUN_1000d6a0();
extern std::uint32_t __stdcall FUN_1000d700();
extern std::uint32_t __stdcall FUN_1000d760();
extern std::uint32_t __stdcall FUN_1000d7c0();
extern std::uint32_t __stdcall FUN_1000d820();
extern std::uint32_t __stdcall FUN_1000d880();
extern std::uint32_t __stdcall FUN_1000d8e0();
extern std::uint32_t __stdcall FUN_1000d940();
extern std::uint32_t __stdcall FUN_1000d9a0();
extern std::uint32_t __stdcall FUN_1000da00();

void __fastcall FUN_10009790(
    std::int32_t param_1,
    [[maybe_unused]] std::uint32_t param_2,
    [[maybe_unused]] std::uint32_t param_3,
    [[maybe_unused]] std::uint32_t param_4,
    [[maybe_unused]] std::uint32_t param_5,
    [[maybe_unused]] std::uint32_t param_6,
    [[maybe_unused]] std::uint32_t param_7)
{
    const std::int32_t iVar1 = param_1 + 4;

    __asm {
        mov ecx, OFFSET FUN_1000d460
        mov edi, 7f9788h
        push 6
        push 0
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d4c0
        mov edi, 7f9710h
        push 6
        push 1
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d520
        mov edi, 7f935ch
        push 6
        push 2
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d580
        mov edi, 7f9248h
        push 6
        push 3
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d5e0
        mov edi, 7f9a16h
        push 6
        push 4
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d640
        mov edi, 7f839fh
        push 6
        push 5
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d6a0
        mov edi, 7f8327h
        push 6
        push 6
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d700
        mov edi, 7f81ffh
        push 6
        push 7
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d760
        mov edi, 7f8187h
        push 6
        push 8
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d7c0
        mov edi, 7f7aa4h
        push 6
        push 9
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d820
        mov edi, 7f8b7bh
        push 4
        push 0ah
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d880
        mov edi, 7f7990h
        push 6
        push 0bh
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d8e0
        mov edi, 7f9b43h
        push 6
        push 0ch
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d940
        mov edi, 7f8c88h
        push 4
        push 0dh
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000d9a0
        mov edi, 7f87c6h
        push 4
        push 0eh
        push iVar1
        call FUN_10009610_relocatable_entry
    }
    __asm {
        mov ecx, OFFSET FUN_1000da00
        mov edi, 7f86c4h
        push 4
        push 0fh
        push iVar1
        call FUN_10009610_relocatable_entry
    }
}
