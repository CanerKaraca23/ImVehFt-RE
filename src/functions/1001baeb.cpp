#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct _LocaleUpdate
{
    unsigned long locale_info;
    unsigned long reserved_04;
    unsigned long locale_control;
    char cleanup_required;
    unsigned char reserved_0D[3];

    _LocaleUpdate(_locale_t);
};
static_assert(offsetof(_LocaleUpdate, locale_info) == 0x00);
static_assert(offsetof(_LocaleUpdate, reserved_04) == 0x04);
static_assert(offsetof(_LocaleUpdate, locale_control) == 0x08);
static_assert(offsetof(_LocaleUpdate, cleanup_required) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);

extern "C" int __cdecl _tolower(int);
extern "C" int __cdecl _isdigit(int);

extern "C" void __cdecl __forcdecpt_l(char* _Buf, _locale_t _Locale)
{
    struct LocaleInfo
    {
        unsigned char padding_000[0xBC];
        unsigned long** field_0xBC;
    };

    struct LocaleControl
    {
        unsigned char padding_000[0x70];
        unsigned long flags_0x70;
    };


    _LocaleUpdate locale_update(_Locale);

    int iVar3 = _tolower(static_cast<int>(*_Buf));
    bool bVar4 = iVar3 == 0x65;

    while (!bVar4)
    {
        _Buf = _Buf + 1;
        iVar3 = _isdigit(static_cast<unsigned int>(
            static_cast<unsigned char>(*_Buf)));
        bVar4 = iVar3 == 0;
    }

    iVar3 = _tolower(static_cast<int>(*_Buf));

    if (iVar3 == 0x78)
        _Buf = _Buf + 2;

    unsigned char bVar2 = static_cast<unsigned char>(*_Buf);

    const auto* locale_info =
        reinterpret_cast<const LocaleInfo*>(
            static_cast<unsigned long>(locale_update.locale_info));

    *_Buf = *reinterpret_cast<const unsigned char*>(
        *locale_info->field_0xBC);

    do
    {
        _Buf = _Buf + 1;

        const unsigned char bVar1 =
            static_cast<unsigned char>(*_Buf);

        *_Buf = static_cast<char>(bVar2);
        bVar2 = bVar1;
    }
    while (*_Buf != '\0');

    if (locale_update.cleanup_required != '\0')
    {
        auto* locale_control =
            reinterpret_cast<LocaleControl*>(
                static_cast<unsigned long>(
                    locale_update.locale_control));

        locale_control->flags_0x70 =
            locale_control->flags_0x70 & 0xFFFFFFFDu;
    }
}