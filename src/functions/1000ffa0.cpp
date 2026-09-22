#include <cstdint>

using Callback = void(__stdcall*)(std::uint32_t);
using ReturnCallback = std::uint32_t(__stdcall*)();

extern std::uintptr_t DAT_1003c3e0;

std::uint32_t __stdcall FUN_1000ffa0(std::uint32_t param_1)
{
    const std::uintptr_t base = DAT_1003c3e0;

    auto* end = *reinterpret_cast<Callback**>(base + 0x1cu);
    auto* begin = *reinterpret_cast<Callback**>(base + 0x18u);

    for (auto* callback = begin; callback != end; ++callback)
    {
        if (*callback != nullptr)
        {
            (*callback)(param_1);
        }
    }

    std::uint32_t local_8;
    const auto callback =
        *reinterpret_cast<ReturnCallback*>(base + 0x0cu);

    if (callback == nullptr)
    {
        local_8 = 0u;
    }
    else
    {
        local_8 = callback();
    }

    end = *reinterpret_cast<Callback**>(base + 0x2cu);
    begin = *reinterpret_cast<Callback**>(base + 0x28u);

    for (auto* post_callback = begin; post_callback != end; ++post_callback)
    {
        if (*post_callback != nullptr)
        {
            (*post_callback)(param_1);
        }
    }

    return local_8;
}