#include <cstdint>

extern unsigned char LAB_1000ca40[];
extern unsigned char LAB_1000ca30[];
extern unsigned char LAB_1000ca20[];
extern unsigned char LAB_1000ca10[];
extern unsigned char LAB_1000ca00[];

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


struct __single_inheritance FUN_1000bae0_this {
    void __thiscall FUN_1000bae0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

void FUN_1000bae0_this::FUN_1000bae0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5)
{
    void* self = static_cast<void*>(this);
    int local_30;
    unsigned char* local_2c;
    int local_28;
    unsigned char* local_24;
    int local_20;
    unsigned char* local_1c;
    int local_18;
    unsigned char* local_14;
    std::uint32_t local_10;
    unsigned char* local_0c;

    local_30 = param_5;
    local_28 = param_4;
    local_20 = param_3;
    local_18 = param_2;
    local_10 = param_1;
    local_2c = LAB_1000ca40;
    local_24 = LAB_1000ca30;
    local_1c = LAB_1000ca20;
    local_14 = LAB_1000ca10;
    local_0c = LAB_1000ca00;

        struct FUN_1000c480_PatchPair { std::uint32_t patch; std::uint32_t target; };
    static_assert(sizeof(FUN_1000c480_PatchPair) == 8);
    FUN_1000c480_PatchPair pair_1{static_cast<std::uint32_t>(param_1), 0x1000ca00u};
    FUN_1000c480_PatchPair pair_2{static_cast<std::uint32_t>(param_2), 0x1000ca10u};
    FUN_1000c480_PatchPair pair_3{static_cast<std::uint32_t>(param_3), 0x1000ca20u};
    FUN_1000c480_PatchPair pair_4{static_cast<std::uint32_t>(param_4), 0x1000ca30u};
    FUN_1000c480_PatchPair pair_5{static_cast<std::uint32_t>(param_5), 0x1000ca40u};
    FUN_1000c480_usercall(
        reinterpret_cast<std::int32_t*>(&pair_1),
        reinterpret_cast<int*>(
            reinterpret_cast<std::uintptr_t>(self) + 4u
        ),
        reinterpret_cast<std::int32_t*>(&pair_2),
        reinterpret_cast<std::int32_t*>(&pair_3),
        reinterpret_cast<std::int32_t*>(&pair_4),
        reinterpret_cast<std::int32_t*>(&pair_5));
}