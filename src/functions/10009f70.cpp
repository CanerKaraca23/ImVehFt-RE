#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct FUN_10009f70_this {
    void* __thiscall FUN_10009f70(unsigned char param_1);
};

void* FUN_10009f70_this::FUN_10009f70(unsigned char param_1)
{
    void* self = static_cast<void*>(this);
    struct Object
    {
        unsigned int vftable;
        unsigned char padding_04[0x14];
        unsigned int field_18;
        unsigned int field_1C;
        unsigned int field_20;
        unsigned char padding_24[4];
        unsigned int field_28;
        unsigned int field_2C;
        unsigned int field_30;
    };

    extern unsigned int
        BasicCallbackManager_5499603_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable[];
    extern void __cdecl FUN_10010756(void*);

    Object* object = static_cast<Object*>(self);

    object->vftable = reinterpret_cast<unsigned int>(
        &BasicCallbackManager_5499603_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable);

    if (object->field_28 != 0)
    {
        FUN_10010756(reinterpret_cast<void*>(object->field_28));
    }

    object->field_28 = 0;
    object->field_2C = 0;
    object->field_30 = 0;

    if (object->field_18 != 0)
    {
        FUN_10010756(reinterpret_cast<void*>(object->field_18));
    }

    object->field_18 = 0;
    object->field_1C = 0;
    object->field_20 = 0;

    if ((param_1 & 1) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}