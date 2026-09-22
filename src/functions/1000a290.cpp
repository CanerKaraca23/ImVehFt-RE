#include <cstdint>

extern void* BasicCallbackManager_6195212_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable[];
extern "C" void __cdecl FUN_10010756(void* param_1);

struct FUN_1000a290_this {
    void* __thiscall FUN_1000a290(std::uint8_t param_1);
};

void* FUN_1000a290_this::FUN_1000a290(std::uint8_t param_1)
{
    void* self = static_cast<void*>(this);
    auto* bytes = static_cast<std::uint8_t*>(self);

    *reinterpret_cast<std::uint32_t*>(bytes) =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(
                BasicCallbackManager_6195212_0_0_0_0_SimpleSuperManagerThiscall_PatcherCALL1_THIS_vftable));

    if (*reinterpret_cast<std::uint32_t*>(bytes + 0x28) != 0)
    {
        FUN_10010756(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(
                *reinterpret_cast<std::uint32_t*>(bytes + 0x28))));
    }

    *reinterpret_cast<std::uint32_t*>(bytes + 0x28) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0x2C) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0x30) = 0;

    if (*reinterpret_cast<std::uint32_t*>(bytes + 0x18) != 0)
    {
        FUN_10010756(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(
                *reinterpret_cast<std::uint32_t*>(bytes + 0x18))));
    }

    *reinterpret_cast<std::uint32_t*>(bytes + 0x18) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0x1C) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0x20) = 0;

    if ((param_1 & 1u) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}