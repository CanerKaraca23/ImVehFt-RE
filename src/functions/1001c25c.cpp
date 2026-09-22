#include <cstddef>
#include <cstdint>
#include <cstring>
#include <corecrt.h>

using rsize_t = std::size_t;
struct localeinfo_struct { void* locinfo; void* mbcinfo; };
struct _LocaleUpdate {
    void* locinfo;
    void* mbcinfo;
    void* ptd;
    std::uint8_t updated;
    std::uint8_t padding[3];
    explicit _LocaleUpdate(localeinfo_struct*);
};
static_assert(sizeof(_LocaleUpdate) == 0x10);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);

extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" std::size_t __cdecl _strlen(const char*);
extern "C" void* __cdecl FID_conflict__memcpy(void*, const void*, std::size_t);
extern "C" void* __cdecl _memset(void*, int, std::size_t);

static std::uint32_t __cdecl __cftof2_l_impl(
    int* input_record,
    char* buffer,
    int param_1,
    std::size_t param_2,
    char param_3,
    localeinfo_struct* param_4)
{
    const int precision_slot = input_record[1];
    _LocaleUpdate locale_update(param_4);

    if (buffer == nullptr || param_1 == 0) {
        *__errno() = 0x16;
        FUN_1001189f();
        if (locale_update.updated != 0) {
            *reinterpret_cast<std::uint32_t*>(
                static_cast<unsigned char*>(locale_update.ptd) + 0x70) &= 0xfffffffdU;
        }
        return 0x16;
    }

    if (param_3 != '\0' &&
        static_cast<std::uint32_t>(precision_slot) - 1U == param_2) {
        const std::uint32_t sign_offset = *input_record == 0x2d ? 1U : 0U;
        *reinterpret_cast<std::uint16_t*>(
            reinterpret_cast<std::uintptr_t>(buffer) + sign_offset +
            (static_cast<std::uint32_t>(precision_slot) - 1U)) = 0x30;
    }

    char* cursor = buffer;
    if (*input_record == 0x2d) {
        *cursor++ = '-';
    }

    char* decimal_position;
    if (precision_slot < 1) {
        decimal_position = cursor + 1;
        const std::size_t length = _strlen(cursor);
        FID_conflict__memcpy(decimal_position, cursor, length + 1);
        *cursor = '0';
    } else {
        decimal_position = cursor + precision_slot;
    }

    if (param_2 > 0) {
        const std::size_t length = _strlen(decimal_position);
        FID_conflict__memcpy(decimal_position + 1, decimal_position, length + 1);

        const auto* locinfo_bytes = static_cast<const unsigned char*>(locale_update.locinfo);
        void* decimal_table = *reinterpret_cast<void* const*>(locinfo_bytes + 0xbc);
        const unsigned char* decimal_string =
            *reinterpret_cast<const unsigned char* const*>(decimal_table);
        *decimal_position = static_cast<char>(*decimal_string);

        if (precision_slot < 0) {
            const std::uint32_t shift = 0U - static_cast<std::uint32_t>(precision_slot);
            if (param_3 != '\0' || static_cast<int>(shift) <= static_cast<int>(param_2)) {
                param_2 = shift;
            }
            if (param_2 != 0) {
                FID_conflict__memcpy(
                    decimal_position + 1 + param_2,
                    decimal_position + 1,
                    _strlen(decimal_position + 1) + 1);
            }
            _memset(decimal_position + 1, 0x30, param_2);
        }
    }

    if (locale_update.updated != 0) {
        *reinterpret_cast<std::uint32_t*>(
            static_cast<unsigned char*>(locale_update.ptd) + 0x70) &= 0xfffffffdU;
    }
    return 0;
}

extern "C" __declspec(naked) std::uint32_t __cdecl __cftof2_l(
    int, std::size_t, char, localeinfo_struct*)
{
    __asm {
        push ebp
        mov ebp, esp
        push dword ptr [ebp + 014h] // locale
        push dword ptr [ebp + 010h] // flag
        push dword ptr [ebp + 00Ch] // size
        push dword ptr [ebp + 008h] // capacity
        push ecx                    // buffer in ECX
        push eax                    // input record in EAX
        call __cftof2_l_impl
        add esp, 018h
        pop ebp
        ret                         // caller removes the four stack arguments
    }
}
