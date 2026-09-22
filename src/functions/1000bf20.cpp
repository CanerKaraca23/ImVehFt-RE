#include <cstddef>
#include <cstdint>

extern std::uint8_t LAB_1000ccc0[];
extern std::uint8_t LAB_1000ccb0[];
extern std::uint8_t LAB_1000cca0[];
extern std::uint8_t LAB_1000cc90[];
extern std::uint8_t LAB_1000cc80[];

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


struct __single_inheritance FUN_1000bf20_this {
    void __thiscall FUN_1000bf20(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

void FUN_1000bf20_this::FUN_1000bf20(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5)
{
    void* self = static_cast<void*>(this);
    struct Object
    {
        std::uint8_t field_00[4];
        std::int32_t field_04;
    };

    static_assert(offsetof(Object, field_04) == 0x04);

    int local_30;
    std::uint8_t* local_2c;
    int local_28;
    std::uint8_t* local_24;
    int local_20;
    std::uint8_t* local_1c;
    int local_18;
    std::uint8_t* local_14;
    std::uint32_t local_10;
    std::uint8_t* local_c;

    local_30 = param_5;
    local_28 = param_4;
    local_20 = param_3;
    local_18 = param_2;
    local_10 = param_1;

    local_2c = LAB_1000ccc0;
    local_24 = LAB_1000ccb0;
    local_1c = LAB_1000cca0;
    local_14 = LAB_1000cc90;
    local_c = LAB_1000cc80;

        struct FUN_1000c480_PatchPair { std::uint32_t patch; std::uint32_t target; };
    static_assert(sizeof(FUN_1000c480_PatchPair) == 8);
    FUN_1000c480_PatchPair pair_1{static_cast<std::uint32_t>(param_1), 0x1000cc80u};
    FUN_1000c480_PatchPair pair_2{static_cast<std::uint32_t>(param_2), 0x1000cc90u};
    FUN_1000c480_PatchPair pair_3{static_cast<std::uint32_t>(param_3), 0x1000cca0u};
    FUN_1000c480_PatchPair pair_4{static_cast<std::uint32_t>(param_4), 0x1000ccb0u};
    FUN_1000c480_PatchPair pair_5{static_cast<std::uint32_t>(param_5), 0x1000ccc0u};
    FUN_1000c480_usercall(
        reinterpret_cast<std::int32_t*>(&pair_1),
        &reinterpret_cast<Object*>(self)->field_04,
        reinterpret_cast<std::int32_t*>(&pair_2),
        reinterpret_cast<std::int32_t*>(&pair_3),
        reinterpret_cast<std::int32_t*>(&pair_4),
        reinterpret_cast<std::int32_t*>(&pair_5));
}