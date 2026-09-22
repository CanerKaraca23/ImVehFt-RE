#include <cstddef>
#include <cstdint>
#include <cwchar>

extern "C" std::uint32_t DAT_10029490;

extern "C" void __cdecl ___dtold(
    std::uint32_t*,
    std::uint32_t*);

extern "C" int __cdecl $I10_OUTPUT(
    std::uint32_t,
    std::uint32_t,
    std::uint16_t,
    int,
    int,
    std::int16_t*);

extern "C" int __cdecl strcpy_s(
    char*,
    std::size_t,
    const char*);

extern "C" void __fastcall __security_check_cookie(
    std::uintptr_t);

extern "C" [[noreturn]] void __cdecl __invoke_watson(
    const wchar_t*,
    const wchar_t*,
    const wchar_t*,
    unsigned int,
    std::uintptr_t);

extern "C" int* __cdecl FUN_1001dd12(
    std::uint32_t param_1,
    std::uint32_t param_2,
    int* param_3,
    char* param_4,
    std::size_t param_5)
{
    struct Binary64Words {
        std::uint32_t low;
        std::uint32_t high;
    };

    struct Extended80 {
        std::uint32_t low;
        std::uint32_t high;
        std::uint16_t sign_exponent;
    };

    struct FormatterBuffer {
        std::int16_t exponent;
        char sign;
        std::uint8_t length;
        char text[24];
    };

    static_assert(sizeof(Binary64Words) == 8);
    static_assert(offsetof(Extended80, sign_exponent) == 8);
    static_assert(sizeof(Extended80) >= 10);
    static_assert(offsetof(FormatterBuffer, sign) == 2);
    static_assert(offsetof(FormatterBuffer, length) == 3);
    static_assert(offsetof(FormatterBuffer, text) == 4);
    static_assert(sizeof(FormatterBuffer) == 28);

    int* piVar1 = param_3;
    char* pcVar2 = param_4;
    Binary64Words binary64{param_1, param_2};
    Extended80 extended80{};
    FormatterBuffer formatted{};
    std::uint32_t local_8 =
        DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_8));

    ___dtold(
        reinterpret_cast<std::uint32_t*>(&extended80),
        reinterpret_cast<std::uint32_t*>(&binary64));

    int iVar3 = $I10_OUTPUT(
        extended80.low,
        extended80.high,
        extended80.sign_exponent,
        0x11,
        0,
        &formatted.exponent);

    piVar1[2] = iVar3;
    *piVar1 = static_cast<int>(formatted.sign);
    piVar1[1] = static_cast<int>(formatted.exponent);

    int eVar4 = strcpy_s(pcVar2, param_5, formatted.text);

    if (eVar4 == 0)
    {
        piVar1[3] = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(pcVar2));

        __security_check_cookie(
            static_cast<std::uintptr_t>(local_8) ^
            reinterpret_cast<std::uintptr_t>(&local_8));

        return piVar1;
    }

    __invoke_watson(nullptr, nullptr, nullptr, 0, 0);
}
