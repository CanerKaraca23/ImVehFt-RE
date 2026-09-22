#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cwchar>

using errno_t = int;
using PVOID = void*;

struct localeinfo_struct {
    std::uint8_t opaque[0x100];
};

struct crt_file {
    std::uint8_t opaque_00[0x0c];
    std::uint32_t flag;
};

struct stream_state {
    std::uint8_t opaque_00[0x24];
    std::uint8_t flags;
};

extern "C" void __cdecl _LocaleUpdate(void*, _locale_t);
extern "C" int __cdecl __fileno(FILE*);
extern "C" int __cdecl __isleadbyte_l(std::uint32_t, localeinfo_struct*);
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" errno_t __cdecl _wctomb_s(int*, char*, std::size_t, wchar_t);
extern "C" std::size_t __cdecl _strlen(char*);
extern "C" int __cdecl __get_printf_count_output();
extern "C" void* __cdecl __malloc_crt(std::size_t);
extern "C" void __cdecl _free(void*);
extern "C" std::uint64_t __cdecl __aulldvrm(
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
extern "C" PVOID __stdcall DecodePointer(PVOID);
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);
extern "C" void __cdecl write_char();
extern "C" void __cdecl write_string();

extern std::uint8_t DAT_100226f0[];
extern std::uint8_t DAT_10022710[];
extern std::uint8_t DAT_10029450;
extern std::uint8_t* DAT_1003c420[];

extern PVOID PTR_LAB_10029d58;
extern PVOID PTR_LAB_10029d60;
extern PVOID PTR_LAB_10029d64;
extern const wchar_t* PTR_s__null__10029c24;
extern const wchar_t* PTR_u__null__10029c28;
extern std::uint32_t extraout_ECX;

int __cdecl __output_l(
    FILE* _File,
    char* _Format,
    _locale_t _Locale,
    char* _ArgList)
{
    std::uint8_t local_215 = 0;
    std::uint32_t local_214 = 0;
    int local_21c = 0;
    std::size_t local_224 = 0;
    int local_228 = 0;
    std::uint8_t local_230 = 0;
    int local_234 = 0;
    int local_238 = 0;
    int local_23c = 0;
    std::uint8_t* local_240 = nullptr;
    FILE* local_244 = _File;
    int local_248 = 0;
    int local_24c = 0;
    wchar_t* local_250 = nullptr;
    char local_254 = 0;
    int local_258 = 0;
    localeinfo_struct local_260{};
    int local_264 = 0;
    std::uint32_t local_268 = 0;
    int local_270 = 0;
    int local_274 = 0;
    std::uint32_t local_278 = 0;
    std::uint32_t local_27c = 0;
    wchar_t local_210[255]{};
    std::uint16_t local_11 = 0;
    char local_22f = 0;
    wchar_t* local_220 = nullptr;
    wchar_t* local_22c =
        reinterpret_cast<wchar_t*>(_ArgList);
    int function_result = 0;

    const std::uint32_t local_8 =
        *reinterpret_cast<std::uint32_t*>(0x10029490) ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_8));

    _LocaleUpdate(&local_260, _Locale);

    if (local_244 == nullptr)
        goto failure;

    if ((reinterpret_cast<crt_file*>(local_244)->flag & 0x40u) == 0) {
        const std::uint32_t file_number =
            static_cast<std::uint32_t>(__fileno(local_244));

        stream_state* state =
            (file_number == 0xffffffffu ||
             file_number == 0xfffffffeu)
                ? reinterpret_cast<stream_state*>(&DAT_10029450)
                : reinterpret_cast<stream_state*>(
                      DAT_1003c420[
                          static_cast<std::int32_t>(file_number) >> 5] +
                      static_cast<std::uintptr_t>(
                          file_number & 0x1f) *
                          0x40u);

        if ((state->flags & 0x7f) != 0)
            goto failure;

        state =
            (file_number == 0xffffffffu ||
             file_number == 0xfffffffeu)
                ? reinterpret_cast<stream_state*>(&DAT_10029450)
                : reinterpret_cast<stream_state*>(
                      DAT_1003c420[
                          static_cast<std::int32_t>(file_number) >> 5] +
                      static_cast<std::uintptr_t>(
                          file_number & 0x1f) *
                          0x40u);

        if ((state->flags & 0x80) != 0)
            goto failure;
    }

    if (_Format == nullptr)
        goto failure;

    local_215 = static_cast<std::uint8_t>(*_Format);
    local_264 = 0;
    local_228 = 0;
    local_224 = 0;
    local_250 = nullptr;

next_format:
    if (local_215 == 0 || local_228 < 0) {
        if (local_254 == '\0') {
            function_result = local_228;
            goto function_exit;
        }

        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(local_258) + 0x70) &=
            0xfffffffdu;

        function_result = local_228;
        goto function_exit;
    }

    {
        std::uint8_t* next =
            reinterpret_cast<std::uint8_t*>(_Format + 1);
        std::uint32_t table_index = 0;

        if (static_cast<std::uint8_t>(local_215 - 0x20) < 0x59) {
            table_index =
                static_cast<std::uint32_t>(
                    static_cast<std::int8_t>(
                        DAT_100226f0[
                            static_cast<std::int8_t>(local_215)])) &
                0x0f;
        }

        local_264 =
            static_cast<std::int8_t>(
                DAT_10022710[
                    table_index * 8u +
                    static_cast<std::uint32_t>(local_264)]) >>
            4;

        local_240 = next;

        switch (local_264) {
        case 0:
literal:
            local_23c = 0;

            if (__isleadbyte_l(local_215, &local_260) != 0) {
                write_char();
                local_240 =
                    reinterpret_cast<std::uint8_t*>(_Format + 2);

                if (*next == 0)
                    goto failure;
            }

            write_char();
            break;

        case 1:
            local_21c = -1;
            local_270 = 0;
            local_248 = 0;
            local_238 = 0;
            local_234 = 0;
            local_214 = 0;
            local_23c = 0;
            break;

        case 2:
            if (local_215 == 0x20)
                local_214 |= 2;
            else if (local_215 == 0x23)
                local_214 |= 0x80;
            else if (local_215 == 0x2b)
                local_214 |= 1;
            else if (local_215 == 0x2d)
                local_214 |= 4;
            else if (local_215 == 0x30)
                local_214 |= 8;
            break;

        case 3:
            if (local_215 == 0x2a) {
                local_22c =
                    reinterpret_cast<wchar_t*>(_ArgList + 4);
                local_238 =
                    *reinterpret_cast<int*>(_ArgList);

                if (local_238 < 0) {
                    local_214 |= 4;
                    local_238 = -local_238;
                }
            } else {
                local_238 =
                    local_238 * 10 - 0x30 +
                    static_cast<int>(
                        static_cast<char>(local_215));
            }
            break;

        case 4:
            local_21c = 0;
            break;

        case 5:
            if (local_215 == 0x2a) {
                local_22c =
                    reinterpret_cast<wchar_t*>(_ArgList + 4);
                local_21c =
                    *reinterpret_cast<int*>(_ArgList);

                if (local_21c < 0)
                    local_21c = -1;
            } else {
                local_21c =
                    local_21c * 10 - 0x30 +
                    static_cast<int>(
                        static_cast<char>(local_215));
            }
            break;

        case 6:
            if (local_215 == 'I') {
                const std::uint8_t c = *next;

                if (c == '6' && _Format[2] == '4') {
                    local_214 |= 0x8000;
                    local_240 =
                        reinterpret_cast<std::uint8_t*>(_Format + 3);
                } else if (c == '3' && _Format[2] == '2') {
                    local_214 &= 0xffff7fffu;
                    local_240 =
                        reinterpret_cast<std::uint8_t*>(_Format + 3);
                } else if (c != 'd' && c != 'i' &&
                           c != 'o' && c != 'u' &&
                           c != 'x' && c != 'X') {
                    local_264 = 0;
                    goto literal;
                }
            } else if (local_215 == 'h') {
                local_214 |= 0x20;
            } else if (local_215 == 'l') {
                if (*next == 'l') {
                    local_214 |= 0x1000;
                    local_240 =
                        reinterpret_cast<std::uint8_t*>(_Format + 2);
                } else {
                    local_214 |= 0x10;
                }
            } else if (local_215 == 'w') {
                local_214 |= 0x800;
            }
            break;

        case 7:
            if (local_215 == 'd' || local_215 == 'i') {
                local_214 |= 0x40;
                local_224 = 10;
                goto integer_conversion;
            }

            if (local_215 == 'u') {
                local_224 = 10;
                goto integer_conversion;
            }

            if (local_215 == 'x') {
                local_24c = 0x27;
                local_224 = 0x10;
                goto integer_conversion;
            }

            if (local_215 == 'X') {
                local_24c = 7;
                local_224 = 0x10;
                goto integer_conversion;
            }

            if (local_215 == 'p') {
                local_21c = 8;
                local_24c = 7;
                local_224 = 0x10;

                if ((local_214 & 0x80) != 0) {
                    local_22f =
                        static_cast<char>(local_24c) + 'Q';
                    local_230 = 0x30;
                    local_234 = 2;
                }

                goto integer_conversion;
            }

            if (local_215 == 'o') {
                local_224 = 8;

                if ((local_214 & 0x80) != 0)
                    local_214 |= 0x200;

                goto integer_conversion;
            }

            if (local_215 == 'n') {
                int* output =
                    *reinterpret_cast<int**>(_ArgList);

                local_22c =
                    reinterpret_cast<wchar_t*>(_ArgList + 4);

                if (__get_printf_count_output() == 0)
                    goto failure;

                if ((local_214 & 0x20) == 0)
                    *output = local_228;
                else
                    *reinterpret_cast<std::uint16_t*>(output) =
                        static_cast<std::uint16_t>(local_228);

                local_248 = 1;
                break;
            }

            if (local_215 == 'S') {
                if ((local_214 & 0x830) == 0)
                    local_214 |= 0x800;
                goto string_conversion;
            }

            if (local_215 == 'A') {
                local_215 =
                    static_cast<std::uint8_t>(local_215 + 0x20);
                local_270 = 1;
                goto floating_conversion;
            }

            if (local_215 == 'C') {
                if ((local_214 & 0x830) == 0)
                    local_214 |= 0x800;
                goto character_conversion;
            }

            if (local_215 == 'E' || local_215 == 'G') {
                local_215 =
                    static_cast<std::uint8_t>(local_215 + 0x20);
                local_270 = 1;
                goto floating_conversion;
            }

            if (local_215 == 'Z')
                goto z_conversion;

            if (local_215 == 'a' ||
                local_215 == 'e' ||
                local_215 == 'g')
                goto floating_conversion;

            if (local_215 == 'c')
                goto character_conversion;

            if (local_215 == 's')
                goto string_conversion;

            break;

        default:
            break;
        }

        if (local_264 == 7 &&
            (local_215 == 's' || local_215 == 'S'))
            goto string_conversion;

        if (local_264 == 7 &&
            (local_215 == 'c' || local_215 == 'C'))
            goto character_conversion;

        if (local_264 == 7 &&
            local_215 == 'Z')
            goto z_conversion;

        if (local_264 == 7 &&
            (local_215 == 'a' || local_215 == 'A' ||
             local_215 == 'e' || local_215 == 'E' ||
             local_215 == 'g' || local_215 == 'G'))
            goto floating_conversion;

        goto emit;

character_conversion:
        if ((local_214 & 0x830) == 0)
            local_214 |= 0x800;

        local_22c =
            reinterpret_cast<wchar_t*>(_ArgList + 4);

        if ((local_214 & 0x810) == 0) {
            reinterpret_cast<char*>(local_210)[0] =
                static_cast<char>(
                    *reinterpret_cast<wchar_t*>(_ArgList));
            local_224 = 1;
        } else {
            const errno_t error =
                _wctomb_s(
                    reinterpret_cast<int*>(&local_224),
                    reinterpret_cast<char*>(local_210),
                    0x200,
                    *reinterpret_cast<wchar_t*>(_ArgList));

            if (error != 0)
                local_248 = 1;
        }

        local_220 = local_210;
        goto emit;

string_conversion:
        if ((local_214 & 0x830) == 0)
            local_214 |= 0x800;

        {
            int remaining = local_21c;

            if (remaining == -1)
                remaining = 0x7fffffff;

            local_22c =
                reinterpret_cast<wchar_t*>(_ArgList + 4);
            local_220 =
                *reinterpret_cast<wchar_t**>(_ArgList);

            if ((local_214 & 0x810) == 0) {
                if (local_220 == nullptr)
                    local_220 =
                        const_cast<wchar_t*>(
                            PTR_s__null__10029c24);

                wchar_t* cursor = local_220;

                for (; remaining != 0;
                     --remaining,
                     cursor = reinterpret_cast<wchar_t*>(
                         reinterpret_cast<char*>(cursor) + 1)) {
                    if (*reinterpret_cast<char*>(cursor) == '\0')
                        break;
                }

                local_224 =
                    reinterpret_cast<char*>(cursor) -
                    reinterpret_cast<char*>(local_220);
            } else {
                if (local_220 == nullptr)
                    local_220 =
                        const_cast<wchar_t*>(
                            PTR_u__null__10029c28);

                local_23c = 1;
                wchar_t* cursor = local_220;

                for (; remaining != 0; --remaining, ++cursor) {
                    if (*cursor == L'\0')
                        break;
                }

                local_224 =
                    (reinterpret_cast<char*>(cursor) -
                     reinterpret_cast<char*>(local_220)) >>
                    1;
            }
        }

        goto emit;

z_conversion:
        {
            std::int16_t* descriptor =
                *reinterpret_cast<std::int16_t**>(_ArgList);

            local_22c =
                reinterpret_cast<wchar_t*>(_ArgList + 4);
            local_220 =
                const_cast<wchar_t*>(
                    PTR_s__null__10029c24);

            if (descriptor == nullptr ||
                *reinterpret_cast<wchar_t**>(
                    descriptor + 2) == nullptr) {
                local_224 =
                    _strlen(
                        reinterpret_cast<char*>(local_220));
                goto emit;
            }

            local_224 =
                static_cast<std::size_t>(*descriptor);
            local_220 =
                *reinterpret_cast<wchar_t**>(
                    descriptor + 2);

            if ((local_214 & 0x800) == 0) {
                local_23c = 0;
            } else {
                local_224 =
                    static_cast<int>(local_224) / 2;
                local_23c = 1;
            }
        }

        goto emit;

floating_conversion:
        local_214 |= 0x40;
        local_268 = 0x200;

        {
            wchar_t* output = local_210;
            std::uint32_t capacity = local_268;

            if (local_21c < 0) {
                local_21c = 6;
            } else if (local_21c == 0) {
                if (local_215 == 'g')
                    local_21c = 1;
            } else {
                if (local_21c > 0x200)
                    local_21c = 0x200;

                if (local_21c > 0xa3) {
                    capacity =
                        static_cast<std::uint32_t>(
                            local_21c + 0x15d);
                    local_220 = local_210;
                    local_250 =
                        static_cast<wchar_t*>(
                            __malloc_crt(capacity));
                    output = local_250;

                    if (local_250 == nullptr) {
                        local_21c = 0xa3;
                        output = local_210;
                        capacity = local_268;
                    }
                }
            }

            using formatter_type = void(__cdecl*)(
                void*, wchar_t*, std::uint32_t, int, int, int,
                localeinfo_struct*);

            auto formatter =
                reinterpret_cast<formatter_type>(
                    DecodePointer(PTR_LAB_10029d58));

            local_27c =
                *reinterpret_cast<std::uint32_t*>(_ArgList);
            local_278 =
                *reinterpret_cast<std::uint32_t*>(_ArgList + 4);
            local_22c =
                reinterpret_cast<wchar_t*>(_ArgList + 8);

            formatter(
                &local_27c,
                output,
                capacity,
                static_cast<int>(
                    static_cast<char>(local_215)),
                local_21c,
                local_270,
                &local_260);

            if ((local_214 & 0x80) != 0 &&
                local_21c == 0) {
                using trim_type =
                    void(__cdecl*)(wchar_t*, localeinfo_struct*);

                auto trim =
                    reinterpret_cast<trim_type>(
                        DecodePointer(PTR_LAB_10029d64));

                trim(output, &local_260);
            }

            if (local_215 == 'g' &&
                (local_214 & 0x80) == 0) {
                using trim_type =
                    void(__cdecl*)(wchar_t*, localeinfo_struct*);

                auto trim =
                    reinterpret_cast<trim_type>(
                        DecodePointer(PTR_LAB_10029d60));

                trim(output, &local_260);
            }

            local_220 = output;

            if (*output == L'-') {
                local_214 |= 0x100;
                local_220 = output + 1;
            }

            local_224 =
                _strlen(reinterpret_cast<char*>(local_220));
        }

        goto emit;

integer_conversion:
        {
            std::uint32_t low;
            std::uint32_t high;

            if ((local_214 & 0x8000) == 0 &&
                (local_214 & 0x1000) == 0) {
                local_22c =
                    reinterpret_cast<wchar_t*>(_ArgList + 4);

                if ((local_214 & 0x20) == 0) {
                    low =
                        *reinterpret_cast<std::uint32_t*>(
                            _ArgList);

                    if ((local_214 & 0x40) == 0)
                        high = 0;
                    else
                        high =
                            static_cast<std::uint32_t>(
                                *reinterpret_cast<std::int32_t*>(
                                    _ArgList) >>
                                0x1f);
                } else {
                    if ((local_214 & 0x40) == 0)
                        low =
                            static_cast<std::uint32_t>(
                                *reinterpret_cast<std::uint16_t*>(
                                    _ArgList));
                    else
                        low =
                            static_cast<std::uint32_t>(
                                *reinterpret_cast<std::int16_t*>(
                                    _ArgList));

                    high =
                        static_cast<std::uint32_t>(
                            static_cast<std::int32_t>(low) >>
                            0x1f);
                }
            } else {
                low =
                    *reinterpret_cast<std::uint32_t*>(
                        _ArgList);
                high =
                    *reinterpret_cast<std::uint32_t*>(
                        _ArgList + 4);
                local_22c =
                    reinterpret_cast<wchar_t*>(_ArgList + 8);
            }

            if ((local_214 & 0x40) != 0 &&
                static_cast<std::int32_t>(high) < 1 &&
                static_cast<std::int32_t>(high) < 0) {
                const bool borrow = low != 0;
                low = 0U - low;
                high =
                    0U - (high +
                          static_cast<std::uint32_t>(borrow));
                local_214 |= 0x100;
            }

            const std::uint64_t value =
                (static_cast<std::uint64_t>(high) << 32) |
                low;

            if ((local_214 & 0x9000) == 0)
                high = 0;

            if (local_21c < 0) {
                local_21c = 1;
            } else {
                local_214 &= 0xfffffff7u;

                if (local_21c > 0x200)
                    local_21c = 0x200;
            }

            if (low == 0 && high == 0)
                local_234 = 0;

            char* digit =
                reinterpret_cast<char*>(&local_11);

            std::uint64_t current_value = value;
            std::uint32_t divisor_high = high;
            int iVar9 = 0;

            for (;;) {
                const std::uint32_t quotient_high =
                    divisor_high;

                iVar9 = local_21c - 1;

                if (local_21c < 1 &&
                    static_cast<std::uint32_t>(
                        current_value) == 0 &&
                    quotient_high == 0)
                    break;

                local_21c = iVar9;

                current_value =
                    __aulldvrm(
                        static_cast<std::uint32_t>(
                            current_value),
                        quotient_high,
                        static_cast<std::uint32_t>(
                            local_224),
                        static_cast<std::uint32_t>(
                            static_cast<std::int32_t>(
                                local_224) >>
                            0x1f));

                iVar9 =
                    static_cast<int>(extraout_ECX) + 0x30;

                int output_digit = iVar9;

                if (0x39 < output_digit)
                    output_digit += local_24c;

                *digit =
                    static_cast<char>(output_digit);
                --digit;

                divisor_high =
                    static_cast<std::uint32_t>(
                        current_value >> 32);
                local_268 = quotient_high;
            }

            local_224 =
                reinterpret_cast<char*>(&local_11) - digit;
            local_220 =
                reinterpret_cast<wchar_t*>(digit + 1);
            local_21c = iVar9;

            if ((local_214 & 0x200) != 0 &&
                (local_224 == 0 ||
                 *reinterpret_cast<char*>(local_220) != '0')) {
                *digit = '0';
                local_224 =
                    reinterpret_cast<char*>(&local_11) -
                    digit + 1;
                local_220 =
                    reinterpret_cast<wchar_t*>(digit);
            }
        }

emit:
        if (local_248 == 0) {
            if ((local_214 & 0x40) != 0) {
                if ((local_214 & 0x100) == 0) {
                    if ((local_214 & 1) == 0) {
                        if ((local_214 & 2) == 0)
                            goto no_sign;

                        local_230 = 0x20;
                    } else {
                        local_230 = 0x2b;
                    }
                } else {
                    local_230 = 0x2d;
                }

                local_234 = 1;
            }

no_sign:
            {
                std::uint32_t padding =
                    (local_238 -
                     static_cast<int>(local_224)) -
                    local_234;

                local_268 = padding;

                if ((local_214 & 0x0c) == 0) {
                    do {
                        if (static_cast<int>(padding) < 1)
                            break;

                        padding--;
                        write_char();
                    } while (local_228 != -1);
                }

                write_string();

                if ((local_214 & 8) != 0 &&
                    (local_214 & 4) == 0) {
                    do {
                        if (static_cast<int>(local_268) < 1)
                            break;

                        local_268--;
                        write_char();
                    } while (local_228 != -1);
                }

                if (local_23c == 0 ||
                    static_cast<int>(local_224) < 1) {
                    write_string();
                } else {
                    std::size_t count = local_224;
                    wchar_t* cursor = local_220;

                    do {
                        count--;

                        const errno_t error =
                            _wctomb_s(
                                &local_274,
                                reinterpret_cast<char*>(
                                    reinterpret_cast<std::uint8_t*>(
                                        &local_11) + 1),
                                6,
                                *cursor);

                        if (error != 0 ||
                            local_274 == 0) {
                            local_228 = -1;
                            break;
                        }

                        write_string();
                        cursor++;
                    } while (count != 0);
                }

                if (local_228 >= 0 &&
                    (local_214 & 4) != 0) {
                    do {
                        if (static_cast<int>(local_268) < 1)
                            break;

                        write_char();
                        local_268--;
                    } while (local_228 != -1);
                }
            }
        }
    }

    if (local_250 != nullptr) {
        _free(local_250);
        local_250 = nullptr;
    }

    local_215 = *local_240;
    _Format =
        reinterpret_cast<char*>(local_240);
    _ArgList =
        reinterpret_cast<char*>(local_22c);

    goto next_format;

failure:
    *__errno() = 0x16;
    FUN_1001189f();

    if (local_254 != '\0') {
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(local_258) + 0x70) &=
            0xfffffffdu;
    }

    function_result = -1;

function_exit:
    __security_check_cookie(local_8);
    return function_result;
}
