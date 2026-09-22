#include <cstdint>

extern void* BasicCallbackManager_5499603_0_0_0_0_cbPostFXManager_vftable[];
extern "C" void __cdecl FUN_10010756(void*);

struct FUN_1000a110_this {
    void* __thiscall FUN_1000a110(std::uint8_t param_1);
};

void* FUN_1000a110_this::FUN_1000a110(std::uint8_t param_1)
{
    void* self = static_cast<void*>(this);
#pragma pack(push, 1)
    struct Object
    {
        void** vftable;
        std::uint8_t field_04[0x14];
        void* field_18;
        std::uint32_t field_1C;
        std::uint32_t field_20;
        std::uint32_t field_24;
        void* field_28;
        std::uint32_t field_2C;
        std::uint32_t field_30;
    };
#pragma pack(pop)

    auto* object = static_cast<Object*>(self);

    object->vftable =
        BasicCallbackManager_5499603_0_0_0_0_cbPostFXManager_vftable;

    if (object->field_28 != nullptr)
    {
        FUN_10010756(object->field_28);
    }

    object->field_28 = nullptr;
    object->field_2C = 0;
    object->field_30 = 0;

    if (object->field_18 != nullptr)
    {
        FUN_10010756(object->field_18);
    }

    object->field_18 = nullptr;
    object->field_1C = 0;
    object->field_20 = 0;

    if ((param_1 & 1U) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}