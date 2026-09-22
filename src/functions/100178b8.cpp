#include <cstddef>
#include <cstdint>
#include <cwchar>

using UINT = std::uint32_t;
using DWORD = std::uint32_t;

struct locale_category
{
    char* locale;
    wchar_t* wlocale;
};

struct localeinfo_struct
{
    std::uint32_t reserved_00;
    UINT lc_codepage;
    std::uint32_t reserved_08[17];
    locale_category lc_category[6];
    std::uint32_t locale_name[6];
};

struct _LocaleUpdate
{
    localeinfo_struct* locinfo;
    struct cleanup_state
    {
        std::uint8_t reserved[0x70];
        DWORD flags;
    }* local_c;
    char local_8;

    _LocaleUpdate(localeinfo_struct* locale_info, _locale_t locale);
};

extern "C" int __cdecl __isleadbyte_l(
    unsigned int c,
    _LocaleUpdate* locale);

extern "C" int __stdcall MultiByteToWideChar(
    UINT code_page,
    DWORD flags,
    const char* multi_byte_string,
    int cb_multi_byte,
    wchar_t* wide_char_string,
    int cch_wide_char);

extern "C" int* __cdecl __errno();

int __cdecl __mbtowc_l(
    wchar_t* _DstCh,
    char* _SrcCh,
    std::size_t _SrcSizeInBytes,
    _locale_t _Locale)
{
    if ((_SrcCh != nullptr) && (_SrcSizeInBytes != 0))
    {
        if (*_SrcCh != '\0')
        {
            localeinfo_struct local_info;
            _LocaleUpdate local_14(&local_info, _Locale);

            if (local_14.locinfo->lc_category[0].wlocale != nullptr)
            {
                int result = __isleadbyte_l(
                    static_cast<unsigned int>(
                        static_cast<unsigned char>(*_SrcCh)),
                    &local_14);

                if (result == 0)
                {
                    result = MultiByteToWideChar(
                        local_14.locinfo->lc_codepage,
                        9,
                        _SrcCh,
                        1,
                        _DstCh,
                        static_cast<int>(_DstCh != nullptr));

                    if (result != 0)
                        goto conversion_succeeded;
                }
                else
                {
                    std::uint32_t required_bytes =
                        local_14.locinfo->locale_name[3];

                    if ((1 < static_cast<int>(required_bytes)) &&
                        (static_cast<int>(required_bytes) <=
                         static_cast<int>(_SrcSizeInBytes)) &&
                        (MultiByteToWideChar(
                             local_14.locinfo->lc_codepage,
                             9,
                             _SrcCh,
                             static_cast<int>(required_bytes),
                             _DstCh,
                             static_cast<int>(_DstCh != nullptr)) != 0))
                    {
                        required_bytes =
                            local_14.locinfo->locale_name[3];

                        if (local_14.local_8 == '\0')
                            return static_cast<int>(required_bytes);

                        local_14.local_c->flags =
                            local_14.local_c->flags & 0xfffffffd;

                        return static_cast<int>(required_bytes);
                    }
                    else if ((local_14.locinfo->locale_name[3] <=
                              _SrcSizeInBytes) &&
                             (_SrcCh[1] != '\0'))
                    {
                        required_bytes =
                            local_14.locinfo->locale_name[3];

                        if (local_14.local_8 == '\0')
                            return static_cast<int>(required_bytes);

                        local_14.local_c->flags =
                            local_14.local_c->flags & 0xfffffffd;

                        return static_cast<int>(required_bytes);
                    }
                }

                *__errno() = 0x2a;

                if (local_14.local_8 != '\0')
                {
                    local_14.local_c->flags =
                        local_14.local_c->flags & 0xfffffffd;
                }

                return -1;
            }

            if (_DstCh != nullptr)
            {
                *_DstCh = static_cast<wchar_t>(
                    static_cast<unsigned char>(*_SrcCh));
            }

        conversion_succeeded:
            if (local_14.local_8 != '\0')
            {
                local_14.local_c->flags =
                    local_14.local_c->flags & 0xfffffffd;
            }

            return 1;
        }

        if (_DstCh != nullptr)
            *_DstCh = L'\0';
    }

    return 0;
}