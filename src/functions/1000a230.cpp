#include <cstdint>

extern void* BasicCallbackManager_6193234_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;
extern void __cdecl FUN_10010756(void*);

struct FUN_1000a230_this {
    void* __thiscall FUN_1000a230(std::uint8_t param_1);
};

void* FUN_1000a230_this::FUN_1000a230(std::uint8_t param_1)
{
    void* self = static_cast<void*>(this);
    *reinterpret_cast<void**>(self) =
        BasicCallbackManager_6193234_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable;

    auto* object = reinterpret_cast<std::uint8_t*>(self);

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

    if ((param_1 & 1U) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}