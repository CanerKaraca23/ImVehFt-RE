#include <cstdint>

extern void* BasicCallbackManager_4459021_5487817_5488269_5488583_6393605_SimpleSuperManager_PatcherCALL1_vftable[];

extern "C" void __cdecl FUN_10010756(void* param_1);

struct FUN_10009af0_this {
    void* __thiscall FUN_10009af0(std::uint8_t param_1);
};

void* FUN_10009af0_this::FUN_10009af0(std::uint8_t param_1)
{
    void* this_ptr = static_cast<void*>(this);
    *reinterpret_cast<void***>(this_ptr) =
        BasicCallbackManager_4459021_5487817_5488269_5488583_6393605_SimpleSuperManager_PatcherCALL1_vftable;

    auto* member_28 = reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 0x28);

    if (*member_28 != nullptr)
        FUN_10010756(*member_28);

    *member_28 = nullptr;
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 0x2C) = 0;
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 0x30) = 0;

    auto* member_18 = reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 0x18);

    if (*member_18 != nullptr)
        FUN_10010756(*member_18);

    *member_18 = nullptr;
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 0x1C) = 0;
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(this_ptr) + 0x20) = 0;

    if ((param_1 & 1U) != 0)
        FUN_10010756(this_ptr);

    return this_ptr;
}