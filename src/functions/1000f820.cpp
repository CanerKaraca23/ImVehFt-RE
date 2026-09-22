#include <cstdint>

std::uint32_t __stdcall FUN_1000f820(std::uint32_t param_1)
{
    using Callback = void (*)(std::uint32_t); // Calling convention unresolved.
    using ReturnCallback = std::uint32_t (*)(); // Calling convention unresolved.

    struct FunctionRegistry
    {
        std::uint8_t padding_00[0x0c];
        std::uint32_t callback_0c;
        std::uint8_t padding_10[0x08];
        std::uint32_t callbacks_begin_18;
        std::uint32_t callbacks_end_1c;
        std::uint8_t padding_20[0x08];
        std::uint32_t late_callbacks_begin_28;
        std::uint32_t late_callbacks_end_2c;
    };

    extern std::uint32_t DAT_1003c3d4;

    const auto object_address =
        static_cast<std::uintptr_t>(DAT_1003c3d4);
    auto* object =
        reinterpret_cast<FunctionRegistry*>(object_address);

    auto* first_end = reinterpret_cast<Callback*>(
        static_cast<std::uintptr_t>(object->callbacks_end_1c));

    for (auto* callback = reinterpret_cast<Callback*>(
             static_cast<std::uintptr_t>(object->callbacks_begin_18));
         callback != first_end;
         callback += 1)
    {
        if (*callback != nullptr)
        {
            (*callback)(param_1);
        }
    }

    const auto return_callback = reinterpret_cast<ReturnCallback>(
        static_cast<std::uintptr_t>(object->callback_0c));

    const std::uint32_t result =
        return_callback == nullptr ? 0U : return_callback();

    auto* late_end = reinterpret_cast<Callback*>(
        static_cast<std::uintptr_t>(object->late_callbacks_end_2c));

    for (auto* callback = reinterpret_cast<Callback*>(
             static_cast<std::uintptr_t>(object->late_callbacks_begin_28));
         callback != late_end;
         callback += 1)
    {
        if (*callback != nullptr)
        {
            (*callback)(param_1);
        }
    }

    return result;
}