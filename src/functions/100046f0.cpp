#include <cstddef>
#include <cstdint>

extern "C" std::uint32_t* (__cdecl* const FUN_100072fb30)(
    std::uint32_t param_1);

extern "C" int __cdecl strncmp(
    char* str1,
    char* str2,
    std::size_t max_count);

extern "C" std::uint32_t* __cdecl FUN_10010ed0(
    std::uint32_t* param_1,
    char* param_2);

extern "C" int __cdecl FID_conflict__sscanf(
    char* source,
    char* format,
    ...);

extern "C" void __stdcall FUN_10004000();

extern "C" std::uint32_t __cdecl FUN_100046f0(
    std::uint32_t param_1,
    int param_2)
{
    std::uint32_t* name =
        FUN_100072fb30(param_1);

    std::uint32_t local_1c = 0;
    std::uint32_t local_18 = 3;
    std::uint32_t local_14;
    std::uint32_t local_10;
    std::uint32_t local_c;
    std::uint32_t local_8 = 0;

    if (*reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(param_2) + 800u) > 0x31u)
    {
        return 1;
    }

    int comparison = strncmp(
        reinterpret_cast<char*>(name),
        const_cast<char*>("indicator"),
        9);

    char type;

    if (comparison == 0 ||
        (comparison = strncmp(
             reinterpret_cast<char*>(name),
             const_cast<char*>("turnl"),
             5),
         comparison == 0))
    {
        local_8 = 0;
        local_c = 0xf0;
        local_10 = 0xb4;
        local_14 = 0;
        local_1c = 5;

        std::uint32_t* suffix =
            FUN_10010ed0(name, const_cast<char*>("_lf"));

        if (suffix == nullptr)
        {
            suffix =
                FUN_10010ed0(name, const_cast<char*>("_rf"));

            if (suffix == nullptr)
            {
                suffix =
                    FUN_10010ed0(name, const_cast<char*>("_lr"));

                if (suffix == nullptr)
                {
                    suffix =
                        FUN_10010ed0(name, const_cast<char*>("_rr"));

                    if (suffix == nullptr)
                    {
                        suffix =
                            FUN_10010ed0(name, const_cast<char*>("_lm"));

                        if (suffix == nullptr)
                        {
                            suffix =
                                FUN_10010ed0(name, const_cast<char*>("_rm"));

                            type = '\x0e';

                            if (suffix == nullptr)
                            {
                                type = *reinterpret_cast<char*>(
                                    static_cast<std::uintptr_t>(param_2) + 3u);
                            }
                        }
                        else
                        {
                            type = '\v';
                        }
                    }
                    else
                    {
                        type = '\f';
                    }
                }
                else
                {
                    type = '\x0f';
                }
            }
            else
            {
                type = '\r';
            }
        }
        else
        {
            type = '\n';
        }
    }
    else
    {
        comparison = strncmp(
            reinterpret_cast<char*>(name),
            const_cast<char*>("breakl"),
            6);

        if (comparison == 0)
        {
            local_8 = 1;
            local_c = 200;
            local_10 = 0;
            local_14 = 0;

            std::uint32_t* suffix =
                FUN_10010ed0(name, const_cast<char*>("_l"));

            if (suffix == nullptr)
            {
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(param_2) + 0x325u) = 1;
                type = '\x05';
            }
            else
            {
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(param_2) + 0x324u) = 1;
                type = '\x04';
            }
        }
        else
        {
            comparison = strncmp(
                reinterpret_cast<char*>(name),
                const_cast<char*>("fogl"),
                4);

            if (comparison == 0)
            {
                local_8 = 0;
                local_c = 200;
                local_10 = 200;
                local_14 = 0xdc;
                local_18 = 6;

                std::uint32_t* suffix =
                    FUN_10010ed0(name, const_cast<char*>("_l"));

                type = static_cast<char>(
                    '\t' - (suffix != nullptr));
            }
            else
            {
                comparison = strncmp(
                    reinterpret_cast<char*>(name),
                    const_cast<char*>("revl"),
                    4);

                if (comparison == 0 ||
                    (comparison = strncmp(
                         reinterpret_cast<char*>(name),
                         const_cast<char*>("reversingl"),
                         10),
                     comparison == 0) ||
                    (comparison = strncmp(
                         reinterpret_cast<char*>(name),
                         const_cast<char*>("revl"),
                         4),
                     comparison == 0) ||
                    (comparison = strncmp(
                         reinterpret_cast<char*>(name),
                         const_cast<char*>("reversingl"),
                         10),
                     comparison == 0))
                {
                    local_8 = 1;
                    local_c = 0xff;
                    local_10 = 0xff;
                    local_14 = 0xff;

                    std::uint32_t* suffix =
                        FUN_10010ed0(name, const_cast<char*>("_l"));

                    type = static_cast<char>(
                        '\a' - (suffix != nullptr));
                }
                else
                {
                    comparison = strncmp(
                        reinterpret_cast<char*>(name),
                        const_cast<char*>("light_n"),
                        7);

                    if (comparison != 0)
                    {
                        return 0;
                    }

                    local_8 = 2;
                    local_c = 0xff;
                    local_10 = 0xff;
                    local_14 = 0xff;
                    type = '\x10';
                }
            }
        }
    }

    const std::uintptr_t record =
        static_cast<std::uintptr_t>(param_2) +
        (*reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(param_2) + 800u) * 0x10u);

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(param_2) + 800u) += 1;

    *reinterpret_cast<std::uint32_t*>(record) = param_1;

    std::uint32_t* prm =
        FUN_10010ed0(name, const_cast<char*>("prm"));

    if (prm != nullptr)
    {
        name = FUN_10010ed0(
            name,
            const_cast<char*>("prm"));

        FID_conflict__sscanf(
            reinterpret_cast<char*>(name),
            const_cast<char*>("prm%2X%2X%2X%1X%1X%1X"),
            &local_c,
            &local_10,
            &local_14,
            &local_8,
            &local_18,
            &local_1c);
    }

    *reinterpret_cast<char*>(record + 0xd) = type;
    *reinterpret_cast<std::uint8_t*>(record + 0x8) =
        static_cast<std::uint8_t>(local_18);
    *reinterpret_cast<std::uint8_t*>(record + 0x9) =
        static_cast<std::uint8_t>(local_1c);
    *reinterpret_cast<std::uint8_t*>(record + 0x6) =
        static_cast<std::uint8_t>(local_8);
    *reinterpret_cast<std::uint8_t*>(record + 0xa) =
        static_cast<std::uint8_t>(local_c);
    *reinterpret_cast<std::uint8_t*>(record + 0xb) =
        static_cast<std::uint8_t>(local_10);
    *reinterpret_cast<std::uint8_t*>(record + 0xc) =
        static_cast<std::uint8_t>(local_14);

    FUN_10004000();
    return 1;
}