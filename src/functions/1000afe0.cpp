#include <cstdint>

extern std::uint8_t LAB_1000c810[];
extern std::uint8_t LAB_1000c800[];
extern std::uint8_t LAB_1000c7f0[];
extern std::uint8_t LAB_1000c7e0[];
extern std::uint8_t LAB_1000c7d0[];

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


struct __single_inheritance FUN_1000afe0_this {
    void __thiscall FUN_1000afe0(std::uint32_t param_1,
    int param_2,
    int param_3,
    int param_4,
    int param_5);
};

void FUN_1000afe0_this::FUN_1000afe0(std::uint32_t param_1,
    int param_2,
    int param_3,
    int param_4,
    int param_5)
{
    void* self = static_cast<void*>(this);
    struct LocalState
    {
        std::uint8_t* callback_5;
        std::uint32_t value_1;
        std::uint8_t* callback_4;
        int value_2;
        std::uint8_t* callback_3;
        int value_3;
        std::uint8_t* callback_2;
        int value_4;
        std::uint8_t* callback_1;
        int value_5;
    } state{
        LAB_1000c810,
        param_1,
        LAB_1000c800,
        param_2,
        LAB_1000c7f0,
        param_3,
        LAB_1000c7e0,
        param_4,
        LAB_1000c7d0,
        param_5
    };

        struct FUN_1000c480_PatchPair { std::uint32_t patch; std::uint32_t target; };
    static_assert(sizeof(FUN_1000c480_PatchPair) == 8);
    FUN_1000c480_PatchPair pair_1{static_cast<std::uint32_t>(param_1), 0x1000c7d0u};
    FUN_1000c480_PatchPair pair_2{static_cast<std::uint32_t>(param_2), 0x1000c7e0u};
    FUN_1000c480_PatchPair pair_3{static_cast<std::uint32_t>(param_3), 0x1000c7f0u};
    FUN_1000c480_PatchPair pair_4{static_cast<std::uint32_t>(param_4), 0x1000c800u};
    FUN_1000c480_PatchPair pair_5{static_cast<std::uint32_t>(param_5), 0x1000c810u};
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