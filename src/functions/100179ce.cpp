#include <cstddef>


extern "C" int __cdecl __mbtowc_l(
    wchar_t* _DstCh,
    char* _SrcCh,
    std::size_t _SrcSizeInBytes,
    _locale_t _Locale);

extern "C" int __cdecl _mbtowc(
    wchar_t* _DstCh,
    char* _SrcCh,
    std::size_t _SrcSizeInBytes)
{
    return __mbtowc_l(
        _DstCh,
        _SrcCh,
        _SrcSizeInBytes,
        static_cast<_locale_t>(nullptr));
}