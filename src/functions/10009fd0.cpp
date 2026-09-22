#include <cstdint>

extern void* BasicCallbackManager_5497491_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;
extern "C" void __cdecl FUN_10010756(void*);

struct FUN_10009fd0_this {
    void* __thiscall FUN_10009fd0(std::uint8_t param_1);
};

void* FUN_10009fd0_this::FUN_10009fd0(std::uint8_t param_1)
{
    void* self = static_cast<void*>(this);
    auto* bytes = static_cast<std::uint8_t*>(self);
    auto& field_18 = *reinterpret_cast<void**>(bytes + 0x18);
    auto& field_1C = *reinterpret_cast<std::uint32_t*>(bytes + 0x1C);
    auto& field_20 = *reinterpret_cast<std::uint32_t*>(bytes + 0x20);
    auto& field_28 = *reinterpret_cast<void**>(bytes + 0x28);
    auto& field_2C = *reinterpret_cast<std::uint32_t*>(bytes + 0x2C);
    auto& field_30 = *reinterpret_cast<std::uint32_t*>(bytes + 0x30);

    *reinterpret_cast<void**>(self) =
        BasicCallbackManager_5497491_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (field_28 != nullptr)
    {
        FUN_10010756(field_28);
    }

    field_28 = nullptr;
    field_2C = 0;
    field_30 = 0;

    if (field_18 != nullptr)
    {
        FUN_10010756(field_18);
    }

    field_18 = nullptr;
    field_1C = 0;
    field_20 = 0;

    if ((param_1 & 1u) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}