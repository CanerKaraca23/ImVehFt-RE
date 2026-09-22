#include <cstdint>

extern std::uint8_t LAB_1000c8b0[];
extern std::uint8_t LAB_1000c8a0[];
extern std::uint8_t LAB_1000c890[];
extern std::uint8_t LAB_1000c880[];
extern std::uint8_t LAB_1000c870[];

extern "C" void __stdcall FUN_1000cdc0(
    std::int32_t*, std::int32_t*, std::int32_t*, std::int32_t*, std::int32_t*);

static void FUN_1000cdc0_usercall(
    std::int32_t* eax_input,
    std::int32_t* output,
    std::int32_t* pair_2,
    std::int32_t* pair_3,
    std::int32_t* pair_4,
    std::int32_t* pair_5)
{
    __asm {
        mov eax, eax_input
        push pair_5
        push pair_4
        push pair_3
        push pair_2
        push output
        call FUN_1000cdc0
    }
}


struct __single_inheritance FUN_1000b260_this { void __thiscall FUN_1000b260(std::uint32_t param_1,
    int param_2,
    int param_3,
    int param_4,
    int param_5); };

void FUN_1000b260_this::FUN_1000b260(std::uint32_t param_1,
    int param_2,
    int param_3,
    int param_4,
    int param_5)
{
    void* self = static_cast<void*>(this);





        struct FUN_1000cdc0_PatchPair { std::uint32_t patch; std::uint32_t target; };
    static_assert(sizeof(FUN_1000cdc0_PatchPair) == 8);
    FUN_1000cdc0_PatchPair patch_1{static_cast<std::uint32_t>(param_1), 0x1000c870u};
    FUN_1000cdc0_PatchPair patch_2{static_cast<std::uint32_t>(param_2), 0x1000c880u};
    FUN_1000cdc0_PatchPair patch_3{static_cast<std::uint32_t>(param_3), 0x1000c890u};
    FUN_1000cdc0_PatchPair patch_4{static_cast<std::uint32_t>(param_4), 0x1000c8a0u};
    FUN_1000cdc0_PatchPair patch_5{static_cast<std::uint32_t>(param_5), 0x1000c8b0u};
    FUN_1000cdc0_usercall(
        reinterpret_cast<std::int32_t*>(&patch_1),
        reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uintptr_t>(self) + 4
        ),
        reinterpret_cast<std::int32_t*>(&patch_2),
        reinterpret_cast<std::int32_t*>(&patch_3),
        reinterpret_cast<std::int32_t*>(&patch_4),
        reinterpret_cast<std::int32_t*>(&patch_5));
}