#include <cstdint>

extern void* BasicCallbackManager_5500065_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;
extern "C" void __cdecl FUN_10010756(void*);

struct FUN_10009df0_this {
    void* __thiscall FUN_10009df0(std::uint8_t param_1);
};

void* FUN_10009df0_this::FUN_10009df0(std::uint8_t param_1)
{
    void* self = static_cast<void*>(this);
    auto* object = reinterpret_cast<std::uint8_t*>(self);

    *reinterpret_cast<void**>(object) =
        BasicCallbackManager_5500065_0_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;

    if (*reinterpret_cast<void**>(object + 0x28) != nullptr)
    {
        FUN_10010756(*reinterpret_cast<void**>(object + 0x28));
    }

    *reinterpret_cast<std::uint32_t*>(object + 0x28) = 0;
    *reinterpret_cast<std::uint32_t*>(object + 0x2C) = 0;
    *reinterpret_cast<std::uint32_t*>(object + 0x30) = 0;

    if (*reinterpret_cast<void**>(object + 0x18) != nullptr)
    {
        FUN_10010756(*reinterpret_cast<void**>(object + 0x18));
    }

    *reinterpret_cast<std::uint32_t*>(object + 0x18) = 0;
    *reinterpret_cast<std::uint32_t*>(object + 0x1C) = 0;
    *reinterpret_cast<std::uint32_t*>(object + 0x20) = 0;

    if ((param_1 & 1u) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}