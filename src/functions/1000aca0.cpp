#include <cstdint>

extern void** DAT_1003c3a0;
extern void* PTR_vftable_10037610;

extern std::uint32_t* DAT_10037638;
extern std::uint32_t* DAT_1003763c;
extern std::uint32_t* DAT_10037640;

struct __single_inheritance FUN_1000ac20_this {
    void __thiscall FUN_1000ac20(std::uint32_t param_1, std::int32_t param_2, std::int32_t param_3, std::int32_t param_4, std::int32_t param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000aca0(std::uint32_t param_1)
{
    if (DAT_1003c3a0 == nullptr)
    {
        DAT_1003c3a0 = &PTR_vftable_10037610;

        using Initializer = decltype(&FUN_1000ac20_this::FUN_1000ac20);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037610) + 4u);
(reinterpret_cast<FUN_1000ac20_this*>(DAT_1003c3a0)->*initializer)(

            0x005BD779u,
            0,
            0,
            0,
            0);
    }

    const std::int32_t parameter_address =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(&param_1));

    const std::int32_t begin_address =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(DAT_10037638));

    const std::int32_t end_address =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(DAT_1003763c));

    if ((parameter_address < end_address) &&
        (begin_address <= parameter_address))
    {
        const std::int32_t offset =
            parameter_address - begin_address;

        if (DAT_1003763c == DAT_10037640)
        {
            FUN_1000cfe0();
        }

        if (DAT_1003763c != nullptr)
        {
            *DAT_1003763c = DAT_10037638[offset >> 2];
        }

        DAT_1003763c = DAT_1003763c + 1;
        return;
    }

    if (DAT_1003763c == DAT_10037640)
    {
        FUN_1000cfe0();
    }

    if (DAT_1003763c != nullptr)
    {
        *DAT_1003763c = param_1;
    }

    DAT_1003763c = DAT_1003763c + 1;
}