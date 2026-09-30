#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl FUN_10010756(void*);
struct FUN_1000a2f0_this {
    void* __thiscall FUN_1000a2f0(unsigned char param_1);
};

void* FUN_1000a2f0_this::FUN_1000a2f0(unsigned char param_1)
{
    void* self = static_cast<void*>(this);
    struct PatcherJMP1_THIS
    {
        void* vftable;
        unsigned char reserved_04[0x14];
        void* member_18;
        unsigned int member_1C;
        unsigned int member_20;
        unsigned int reserved_24;
        void* member_28;
        unsigned int member_2C;
        unsigned int member_30;
    };

    PatcherJMP1_THIS* object = static_cast<PatcherJMP1_THIS*>(self);

    object->vftable = reinterpret_cast<void*>(IVF_IMAGE_ADDRESS_10024E60);

    if (object->member_28 != 0)
        FUN_10010756(object->member_28);

    object->member_28 = 0;
    object->member_2C = 0;
    object->member_30 = 0;

    if (object->member_18 != 0)
        FUN_10010756(object->member_18);

    object->member_18 = 0;
    object->member_1C = 0;
    object->member_20 = 0;

    if ((param_1 & 1) != 0)
        FUN_10010756(self);

    return self;
}
