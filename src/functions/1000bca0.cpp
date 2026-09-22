#include <cstdint>

extern std::uint8_t LAB_1000cbe0[];
extern std::uint8_t LAB_1000cb90[];
extern std::uint8_t LAB_1000cb40[];
extern std::uint8_t LAB_1000caf0[];
extern std::uint8_t LAB_1000caa0[];

extern "C" void __stdcall FUN_1000c480(
    std::int32_t*, std::int32_t*, std::int32_t*, std::int32_t*, std::int32_t*);

static void FUN_1000c480_usercall(
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
        call FUN_1000c480
    }
}


struct __single_inheritance FUN_1000bca0_this {
    void __thiscall FUN_1000bca0(std::uint32_t param_1,
    int param_2,
    int param_3,
    int param_4,
    int param_5);
};

void FUN_1000bca0_this::FUN_1000bca0(std::uint32_t param_1,
    int param_2,
    int param_3,
    int param_4,
    int param_5)
{
    void* self = static_cast<void*>(this);





        struct FUN_1000c480_PatchPair { std::uint32_t patch; std::uint32_t target; };
    static_assert(sizeof(FUN_1000c480_PatchPair) == 8);
    FUN_1000c480_PatchPair pair_1{static_cast<std::uint32_t>(param_1), 0x1000caa0u};
    FUN_1000c480_PatchPair pair_2{static_cast<std::uint32_t>(param_2), 0x1000caf0u};
    FUN_1000c480_PatchPair pair_3{static_cast<std::uint32_t>(param_3), 0x1000cb40u};
    FUN_1000c480_PatchPair pair_4{static_cast<std::uint32_t>(param_4), 0x1000cb90u};
    FUN_1000c480_PatchPair pair_5{static_cast<std::uint32_t>(param_5), 0x1000cbe0u};
    FUN_1000c480_usercall(
        reinterpret_cast<std::int32_t*>(&pair_1),
        reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(self) + 4
        ),
        reinterpret_cast<std::int32_t*>(&pair_2),
        reinterpret_cast<std::int32_t*>(&pair_3),
        reinterpret_cast<std::int32_t*>(&pair_4),
        reinterpret_cast<std::int32_t*>(&pair_5));
}