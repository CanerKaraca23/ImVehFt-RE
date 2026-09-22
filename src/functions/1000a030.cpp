#include <cstdint>

extern std::uint32_t BasicCallbackManager_0_0_0_0_0_cbResetDeviceManager_vftable[];
extern "C" void __cdecl FUN_10010756(void*);

struct FUN_1000a030_this {
    void* __thiscall FUN_1000a030(std::uint8_t param_1);
};

void* FUN_1000a030_this::FUN_1000a030(std::uint8_t param_1)
{
    void* self = static_cast<void*>(this);
    struct Object
    {
        std::uint32_t vftable;
        std::uint8_t field_04[0x40];
        std::uint32_t field_44;
        std::uint32_t field_48;
        std::uint32_t field_4C;
        std::uint8_t field_50[4];
        std::uint32_t field_54;
        std::uint32_t field_58;
        std::uint32_t field_5C;
    };

    auto* object = reinterpret_cast<Object*>(self);

    object->vftable = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(
            BasicCallbackManager_0_0_0_0_0_cbResetDeviceManager_vftable));

    if (object->field_54 != 0)
    {
        FUN_10010756(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(object->field_54)));
    }

    object->field_54 = 0;
    object->field_58 = 0;
    object->field_5C = 0;

    if (object->field_44 != 0)
    {
        FUN_10010756(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(object->field_44)));
    }

    object->field_44 = 0;
    object->field_48 = 0;
    object->field_4C = 0;

    if ((param_1 & 1u) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}