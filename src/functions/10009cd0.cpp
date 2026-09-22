#include <cstdint>

extern void* BasicCallbackManager_7638537_7638600_0_0_0_SimpleSuperManager_PatcherCALL1_vftable;
extern void __cdecl FUN_10010756(void*);

struct FUN_10009cd0_this {
    void* __thiscall FUN_10009cd0(std::uint8_t param_1);
};

void* FUN_10009cd0_this::FUN_10009cd0(std::uint8_t param_1)
{
    void* self = static_cast<void*>(this);
    *reinterpret_cast<void***>(self) =
        reinterpret_cast<void**>(
            BasicCallbackManager_7638537_7638600_0_0_0_SimpleSuperManager_PatcherCALL1_vftable);

    void** field_28 = reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(self) + 0x28);

    if (*field_28 != nullptr)
    {
        FUN_10010756(*field_28);
    }

    field_28[0] = nullptr;
    field_28[1] = nullptr;
    field_28[2] = nullptr;

    void** field_18 = reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(self) + 0x18);

    if (*field_18 != nullptr)
    {
        FUN_10010756(*field_18);
    }

    field_18[0] = nullptr;
    field_18[1] = nullptr;
    field_18[2] = nullptr;

    if ((param_1 & 1u) != 0)
    {
        FUN_10010756(self);
    }

    return self;
}