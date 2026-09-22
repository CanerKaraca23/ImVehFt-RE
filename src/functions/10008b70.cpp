#include <cstdint>

extern std::uint16_t DAT_00B4E478;

extern "C" std::uint32_t __fastcall FUN_10008b70(std::int32_t param_1)
{
    using GetContextFn = std::uint32_t (__cdecl*)();
    using SetValueFn = void (__cdecl*)(std::uint32_t, std::int32_t);
    using GetIndexFn = std::int32_t (__cdecl*)();
    using GetHandleFn = std::uint32_t (__cdecl*)(std::uint32_t);
    using ApplyFn = std::int32_t (__cdecl*)(std::uint32_t, std::uint32_t);
    using CreateFn = std::uint32_t (__cdecl*)(std::int32_t);
    using ConfigureFn = void (__cdecl*)(std::uint32_t, std::int32_t);
    using SubmitFn = void (__cdecl*)(std::uint32_t, std::uint32_t);
    using FinalizeFn = void (__cdecl*)(
        std::uint32_t, std::uint32_t, std::int32_t);

    volatile GetContextFn getContext =
        reinterpret_cast<GetContextFn>(0x004C5140);
    const std::uint32_t context = getContext();

    const std::int32_t state =
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(param_1) + 0x5C);

    if (*reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(state) + 0x30C) == 0)
    {
        DAT_00B4E478 = 0xFFFF;
    }
    else
    {
        const std::int32_t mode =
            *reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(param_1) + 0x3C);

        if (mode == 9 || mode == 10 || mode < 5)
        {
            volatile SetValueFn setValue =
                reinterpret_cast<SetValueFn>(0x004C53C0);
            setValue(context, 1);
        }

        volatile GetIndexFn getIndexFirst =
            reinterpret_cast<GetIndexFn>(0x004C8040);
        std::int32_t index = getIndexFirst();

        if (index != -1)
        {
            const std::int32_t entry =
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(state) +
                    0x2F4 + index * 4);

            if (entry != 0)
            {
                volatile GetHandleFn getHandleFirst =
                    reinterpret_cast<GetHandleFn>(0x0072FB30);
                const std::uint32_t value =
                    getHandleFirst(
                        *reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(entry) + 4));

                volatile ApplyFn applyFirst =
                    reinterpret_cast<ApplyFn>(0x004C5400);
                const std::int32_t result =
                    applyFirst(context, value);

                if (result != 0)
                {
                    volatile CreateFn createFirst =
                        reinterpret_cast<CreateFn>(0x00749E60);
                    const std::uint32_t object = createFirst(entry);

                    volatile ConfigureFn configureFirst =
                        reinterpret_cast<ConfigureFn>(0x0074BF20);
                    configureFirst(object, result);

                    volatile SubmitFn submitFirst =
                        reinterpret_cast<SubmitFn>(0x0074A490);
                    submitFirst(context, object);
                }
            }
        }

        DAT_00B4E478 =
            static_cast<std::uint16_t>(
                (DAT_00B4E478 & 0xFF00u) |
                static_cast<std::uint8_t>(index));

        volatile GetIndexFn getIndexSecond =
            reinterpret_cast<GetIndexFn>(0x004C8120);
        index = getIndexSecond();

        if (index != -1)
        {
            const std::int32_t entry =
                *reinterpret_cast<std::int32_t*>(
                    static_cast<std::uintptr_t>(state) +
                    0x2F4 + index * 4);

            if (entry != 0)
            {
                volatile GetHandleFn getHandleSecond =
                    reinterpret_cast<GetHandleFn>(0x0072FB30);
                const std::uint32_t value =
                    getHandleSecond(
                        *reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(entry) + 4));

                volatile ApplyFn applySecond =
                    reinterpret_cast<ApplyFn>(0x004C5400);
                const std::int32_t result =
                    applySecond(context, value);

                if (result != 0)
                {
                    volatile CreateFn createSecond =
                        reinterpret_cast<CreateFn>(0x00749E60);
                    const std::uint32_t object = createSecond(entry);

                    volatile ConfigureFn configureSecond =
                        reinterpret_cast<ConfigureFn>(0x0074BF20);
                    configureSecond(object, result);

                    volatile SubmitFn submitSecond =
                        reinterpret_cast<SubmitFn>(0x0074A490);
                    submitSecond(context, object);
                }
            }
        }

        DAT_00B4E478 =
            static_cast<std::uint16_t>(
                (static_cast<std::uint16_t>(
                     static_cast<std::uint8_t>(index)) << 8) |
                (DAT_00B4E478 & 0x00FFu));
    }

    volatile FinalizeFn finalize =
        reinterpret_cast<FinalizeFn>(0x00749B70);
    finalize(context, 0x004C9410, 0);

    return context;
}