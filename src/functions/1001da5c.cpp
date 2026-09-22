#include <cstddef>
#include <cstdint>

struct _CRT_FLOAT { float value; };
struct _CRT_DOUBLE { double value; };
struct _LDBL12 { std::uint8_t bytes[12]; };
struct pthreadlocinfo;
struct pthreadmbcinfo;
struct localeinfo_struct { pthreadlocinfo* locinfo; pthreadmbcinfo* mbcinfo; };
struct _LocaleUpdate { pthreadlocinfo* locinfo; pthreadmbcinfo* mbcinfo; void* ptd; std::uint8_t updated; _LocaleUpdate(_locale_t locale); };
static_assert(offsetof(_LocaleUpdate, locinfo) == 0x00);
static_assert(offsetof(_LocaleUpdate, mbcinfo) == 0x04);
static_assert(offsetof(_LocaleUpdate, ptd) == 0x08);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);

enum INTRNCVT_STATUS : std::int32_t
{
    INTRNCVT_OK = 0,
    INTRNCVT_OVERFLOW = 1,
    INTRNCVT_UNDERFLOW = 2
};

extern "C" std::uint32_t DAT_10029490;


extern "C" std::uint32_t __cdecl ___strgtold12_l(
    _LDBL12* value,
    char** end_ptr,
    char* string,
    std::int32_t flags_1,
    std::int32_t flags_2,
    std::int32_t flags_3,
    std::int32_t flags_4,
    void* locale_info);

extern "C" INTRNCVT_STATUS __cdecl FUN_1001e085(
    _LDBL12* value,
    _CRT_DOUBLE* result);

extern "C" void __fastcall __security_check_cookie(
    std::uintptr_t stack_cookie);

extern "C" int __cdecl FID_conflict___atoflt_l(
    _CRT_FLOAT* result,
    char* string,
    _locale_t locale)
{
    std::uintptr_t stack_cookie =
        static_cast<std::uintptr_t>(DAT_10029490) ^
        reinterpret_cast<std::uintptr_t>(&stack_cookie);

    char* end_ptr;
    _LocaleUpdate locale_info(locale);
    std::uint32_t conversion_status;
    _LDBL12 extended_value;

    conversion_status = ___strgtold12_l(
        &extended_value,
        &end_ptr,
        string,
        0,
        0,
        0,
        0,
        &locale_info);

    const INTRNCVT_STATUS conversion_result =
        FUN_1001e085(
            &extended_value,
            reinterpret_cast<_CRT_DOUBLE*>(result));

    int return_value;

    if ((conversion_status & 3u) == 0)
    {
        if (conversion_result == INTRNCVT_OVERFLOW)
        {
            if (locale_info.updated != '\0')
            {
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uintptr_t>(locale_info.ptd) + 0x70u) &=
                    0xfffffffdU;
            }

            return_value = 3;
        }
        else if (conversion_result == INTRNCVT_UNDERFLOW)
        {
            if (locale_info.updated != '\0')
            {
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uintptr_t>(locale_info.ptd) + 0x70u) &=
                    0xfffffffdU;
            }

            return_value = 4;
        }
        else
        {
            if (locale_info.updated != '\0')
            {
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uintptr_t>(locale_info.ptd) + 0x70u) &=
                    0xfffffffdU;
            }

            return_value = 0;
        }
    }
    else if ((conversion_status & 1u) == 0)
    {
        if ((conversion_status & 2u) == 0)
        {
            if (locale_info.updated != '\0')
            {
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uintptr_t>(locale_info.ptd) + 0x70u) &=
                    0xfffffffdU;
            }

            return_value = 0;
        }
        else
        {
            if (locale_info.updated != '\0')
            {
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uintptr_t>(locale_info.ptd) + 0x70u) &=
                    0xfffffffdU;
            }

            return_value = 3;
        }
    }
    else
    {
        if (locale_info.updated != '\0')
        {
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(locale_info.ptd) + 0x70u) &=
                0xfffffffdU;
        }

        return_value = 4;
    }

    __security_check_cookie(stack_cookie);
    return return_value;
}