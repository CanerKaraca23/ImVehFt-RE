#include <cstdint>

extern "C" unsigned char LAB_1000c720;
extern "C" unsigned char LAB_1000c710;
extern "C" unsigned char LAB_1000c700;
extern "C" unsigned char LAB_1000c6f0;
extern "C" unsigned char LAB_1000c6e0;

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


struct __single_inheritance FUN_1000ac20_this {
    void __thiscall FUN_1000ac20(std::uint32_t param_1, std::int32_t param_2, std::int32_t param_3, std::int32_t param_4, std::int32_t param_5);
};

void FUN_1000ac20_this::FUN_1000ac20(std::uint32_t param_1, std::int32_t param_2, std::int32_t param_3, std::int32_t param_4, std::int32_t param_5)
{
    void* self = static_cast<void*>(this);
    std::int32_t local_30;
    std::uint8_t* local_2c;
    std::int32_t local_28;
    std::uint8_t* local_24;
    std::int32_t local_20;
    std::uint8_t* local_1c;
    std::int32_t local_18;
    std::uint8_t* local_14;
    std::uint32_t local_10;
    std::uint8_t* local_c;

    local_30 = param_5;
    local_28 = param_4;
    local_20 = param_3;
    local_18 = param_2;
    local_10 = param_1;
    local_2c = reinterpret_cast<std::uint8_t*>(&LAB_1000c720);
    local_24 = reinterpret_cast<std::uint8_t*>(&LAB_1000c710);
    local_1c = reinterpret_cast<std::uint8_t*>(&LAB_1000c700);
    local_14 = reinterpret_cast<std::uint8_t*>(&LAB_1000c6f0);
    local_c = reinterpret_cast<std::uint8_t*>(&LAB_1000c6e0);

    (void)local_10;
    (void)local_2c;
    (void)local_24;
    (void)local_1c;
    (void)local_14;
    (void)local_c;

        struct FUN_1000c480_PatchPair { std::uint32_t patch; std::uint32_t target; };
    static_assert(sizeof(FUN_1000c480_PatchPair) == 8);
    FUN_1000c480_PatchPair pair_1{static_cast<std::uint32_t>(param_1), 0x1000c6e0u};
    FUN_1000c480_PatchPair pair_2{static_cast<std::uint32_t>(param_2), 0x1000c6f0u};
    FUN_1000c480_PatchPair pair_3{static_cast<std::uint32_t>(param_3), 0x1000c700u};
    FUN_1000c480_PatchPair pair_4{static_cast<std::uint32_t>(param_4), 0x1000c710u};
    FUN_1000c480_PatchPair pair_5{static_cast<std::uint32_t>(param_5), 0x1000c720u};
    FUN_1000c480_usercall(
        reinterpret_cast<std::int32_t*>(&pair_1),
        reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(self) + 4u
        ),
        reinterpret_cast<std::int32_t*>(&pair_2),
        reinterpret_cast<std::int32_t*>(&pair_3),
        reinterpret_cast<std::int32_t*>(&pair_4),
        reinterpret_cast<std::int32_t*>(&pair_5));
}