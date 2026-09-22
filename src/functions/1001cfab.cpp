#include <cstdint>

struct EHExceptionRecord;
struct _s_ESTypeList;

extern "C" void __cdecl _inconsistency();
extern "C" [[noreturn]] void __cdecl terminate();

extern "C" std::uint32_t __cdecl ___TypeMatch(
    std::uint8_t*,
    std::uint8_t*,
    std::uint32_t*);

std::uint8_t __cdecl IsInExceptionSpec(
    EHExceptionRecord* param_1,
    _s_ESTypeList const* param_2)
{
    auto* exception_spec =
        reinterpret_cast<const std::int32_t*>(param_2);

    if (exception_spec == nullptr)
    {
        _inconsistency();
        terminate();
    }

    std::int32_t local_c = 0;
    std::uint8_t local_5 = 0;

    if (0 < *exception_spec)
    {
        do
        {
            auto* exception_type_list =
                reinterpret_cast<std::int32_t**>(
                    static_cast<std::uintptr_t>(
                        *reinterpret_cast<const std::uint32_t*>(
                            static_cast<std::uintptr_t>(
                                *reinterpret_cast<const std::uint32_t*>(
                                    reinterpret_cast<const std::uint8_t*>(
                                        param_1) + 0x1c)) + 0x0c)));

            std::int32_t remaining = **exception_type_list;

            if (0 < remaining)
            {
                do
                {
                    ++exception_type_list;

                    const int type_match = static_cast<int>(___TypeMatch(
                        reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(
                                exception_spec[1]) +
                            local_c * 0x10),
                        reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(
                                **exception_type_list)),
                        reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(
                                *reinterpret_cast<const std::uint32_t*>(
                                    reinterpret_cast<const std::uint8_t*>(
                                        param_1) + 0x1c)))));

                    if (type_match != 0)
                    {
                        local_5 = 1;
                        break;
                    }

                    remaining = remaining - 1;
                }
                while (0 < remaining);
            }

            local_c = local_c + 1;
        }
        while (local_c < *exception_spec);
    }

    return local_5;
}