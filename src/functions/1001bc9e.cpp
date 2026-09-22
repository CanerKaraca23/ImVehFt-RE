#include <cstddef>
#include <cstdint>
#include <cstring>
#include <corecrt.h>

using uint = std::uint32_t;
using rsize_t = std::size_t;

struct localeinfo_struct {
    void* locinfo;
    void* mbcinfo;
};

struct _LocaleUpdate {
    void* locinfo;                 // [this + 0x00], confirmed by Ghidra
    void* mbcinfo;                 // [this + 0x04]
    void* ptd;                     // [this + 0x08]
    std::uint8_t updated;          // [this + 0x0c]
    std::uint8_t padding[3];
    explicit _LocaleUpdate(localeinfo_struct*);
};
static_assert(sizeof(_LocaleUpdate) == 0x10);
static_assert(offsetof(_LocaleUpdate, ptd) == 0x08);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);

extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" int __cdecl strcpy_s(char*, rsize_t, const char*);
extern "C" __declspec(noreturn) void __cdecl __invoke_watson(
    wchar_t*, wchar_t*, wchar_t*, unsigned int, std::uintptr_t);
extern "C" void* __cdecl FID_conflict__memcpy(void*, const void*, std::size_t);
extern "C" unsigned char DAT_1003c408;

static int __cdecl FUN_1001bc9e_impl(
    unsigned char* hidden_buffer,
    uint param_1,
    int param_2,
    int param_3,
    int* param_4,
    char param_5,
    localeinfo_struct* param_6)
{
    _LocaleUpdate locale_update(param_6);
    int error = 0;

    if (hidden_buffer == nullptr || param_1 == 0) {
        *(__errno()) = 0x16;
        FUN_1001189f();
        error = 0x16;
    } else {
        int normalized_precision = param_2;
        if (param_2 < 1) {
            normalized_precision = 0;
        }
        if (static_cast<unsigned int>(normalized_precision + 9) >= param_1) {
            *(__errno()) = 0x22;
            FUN_1001189f();
            error = 0x22;
        } else {
            unsigned char* cursor = hidden_buffer;
            const bool negative = *param_4 == '-';
            if (negative) {
                *cursor++ = '-';
            }

            // __shift is a register-ABI helper: EAX=buffer+sign,
            // EDI=(param_2 > 0). Its Ghidra body is strlen + the
            // overlap-aware FID_conflict:_memcpy helper.
            if (param_5 != '\0' && param_2 > 0) {
                FID_conflict__memcpy(cursor + 1, cursor, std::strlen(
                    reinterpret_cast<const char*>(cursor)) + 1);
            }

            if (param_2 > 0) {
                cursor[0] = cursor[1];
                const auto* locinfo_bytes = static_cast<const unsigned char*>(
                    locale_update.locinfo);
                void* decimal_table = *reinterpret_cast<void* const*>(
                    locinfo_bytes + 0xbc);
                const unsigned char* decimal_string =
                    *reinterpret_cast<const unsigned char* const*>(decimal_table);
                cursor[1] = *decimal_string;
                ++cursor;
            }

            char* const dst = reinterpret_cast<char*>(
                cursor + static_cast<unsigned int>(param_5 == '\0') + param_2);
            const auto used = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(dst) -
                reinterpret_cast<std::uintptr_t>(hidden_buffer));
            rsize_t remaining;
            if (param_1 == 0xffffffffU) {
                remaining = static_cast<rsize_t>(0xffffffffU);
            } else {
                remaining = static_cast<rsize_t>(param_1 - used);
            }

            if (strcpy_s(dst, remaining, "e+000") != 0) {
                __invoke_watson(nullptr, nullptr, nullptr, 0, 0);
            }
            if (param_3 != 0) {
                *dst = 'E';
            }

            if (*reinterpret_cast<char*>(param_4[3]) != '0') {
                int exponent = param_4[1] - 1;
                if (exponent < 0) {
                    exponent = -exponent;
                    dst[1] = '-';
                }
                if (exponent > 99) {
                    const int hundreds = exponent / 100;
                    exponent %= 100;
                    dst[2] = static_cast<char>(dst[2] + hundreds);
                }
                if (exponent > 9) {
                    const int tens = exponent / 10;
                    exponent %= 10;
                    dst[3] = static_cast<char>(dst[3] + tens);
                }
                dst[4] = static_cast<char>(dst[4] + exponent);
            }

            if ((DAT_1003c408 & 1) != 0 && dst[2] == '0') {
                FID_conflict__memcpy(dst + 2, dst + 3, 3);
            }
        }
    }

    if (locale_update.updated != 0) {
        *reinterpret_cast<std::uint32_t*>(
            static_cast<unsigned char*>(locale_update.ptd) + 0x70) &= 0xfffffffdU;
    }
    return error;
}

extern "C" __declspec(naked) int __cdecl FUN_1001bc9e(
    uint, int, int, int*, char, localeinfo_struct*)
{
    __asm {
        push ebp
        mov ebp, esp
        push dword ptr [ebp + 01Ch] // param_6
        push dword ptr [ebp + 018h] // param_5
        push dword ptr [ebp + 014h] // param_4
        push dword ptr [ebp + 010h] // param_3
        push dword ptr [ebp + 00Ch] // param_2
        push dword ptr [ebp + 008h] // param_1
        push eax                    // hidden output buffer
        call FUN_1001bc9e_impl
        add esp, 01Ch
        pop ebp
        ret
    }
}
