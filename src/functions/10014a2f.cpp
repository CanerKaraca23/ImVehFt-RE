#include <cstdint>
#include <cstdlib>

extern "C" void __cdecl _free(void* memory);
extern "C" void __cdecl ___free_lconv_mon(void* locale);
extern "C" void __cdecl ___free_lconv_num(void* locale);
extern "C" void __cdecl ___free_lc_time(void* localeTime);

extern "C" void __cdecl ___freetlocinfo(void* param_1)
{
    void* const original = param_1;
    auto* const bytes = static_cast<std::uint8_t*>(param_1);

    auto& field_b0 = *reinterpret_cast<std::uint32_t*>(bytes + 0xB0);
    auto& field_b4 = *reinterpret_cast<std::uint32_t*>(bytes + 0xB4);
    auto& field_b8 = *reinterpret_cast<std::uint32_t*>(bytes + 0xB8);
    auto& field_bc = *reinterpret_cast<std::uint32_t*>(bytes + 0xBC);
    auto& field_c0 = *reinterpret_cast<std::uint32_t*>(bytes + 0xC0);
    auto& field_c4 = *reinterpret_cast<std::uint32_t*>(bytes + 0xC4);
    auto& field_cc = *reinterpret_cast<std::uint32_t*>(bytes + 0xCC);
    auto& field_d0 = *reinterpret_cast<std::uint32_t*>(bytes + 0xD0);
    auto& field_d4 = *reinterpret_cast<std::uint32_t*>(bytes + 0xD4);

    if (field_bc != 0 &&
        field_bc != 0x10029EA8 &&
        field_b0 != 0 &&
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(field_b0)) == 0)
    {
        if (field_b8 != 0 &&
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(field_b8)) == 0)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(field_b8)));

            ___free_lconv_mon(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(field_bc)));
        }

        if (field_b4 != 0 &&
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(field_b4)) == 0)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(field_b4)));

            ___free_lconv_num(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(field_bc)));
        }

        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(field_b0)));

        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(field_bc)));
    }

    if (field_c0 != 0 &&
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(field_c0)) == 0)
    {
        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(field_c4 - 0xFE)));

        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(field_cc - 0x80)));

        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(field_d0 - 0x80)));

        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(field_c0)));
    }

    auto* const locale_time = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(field_d4));

    if (locale_time != reinterpret_cast<std::uint32_t*>(0x100299C8) &&
        locale_time[0x2D] == 0)
    {
        ___free_lc_time(locale_time);

        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(field_d4)));
    }

    auto* entry = reinterpret_cast<std::uint32_t*>(bytes + 0x50);

    for (int count = 6; count != 0; --count)
    {
        if (reinterpret_cast<void*>(static_cast<std::uintptr_t>(entry[-2])) !=
                reinterpret_cast<void*>(0x100299C4) &&
            entry[0] != 0 &&
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(entry[0])) == 0)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(entry[0])));
        }

        if (entry[-1] != 0 &&
            entry[1] != 0 &&
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(entry[1])) == 0)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(entry[1])));
        }

        entry += 4;
    }

    _free(original);
}