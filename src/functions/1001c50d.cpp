#include <cstddef>
#include <cstdint>

extern "C" errno_t __cdecl __cftoe_l(
    std::uint32_t* arg,
    char* buffer,
    std::size_t sizeInBytes,
    int precision,
    int caps,
    _locale_t plocinfo);

extern "C" errno_t __cdecl __cftof_l(
    std::uint32_t* arg,
    char* buffer,
    std::size_t sizeInBytes,
    int precision,
    _locale_t plocinfo);

extern "C" int __cdecl __cftoa_l(
    double* arg,
    char* buffer,
    std::size_t sizeInBytes,
    std::size_t precision,
    int caps,
    _locale_t plocinfo);

extern "C" errno_t __cdecl __cftog_l(
    std::uint32_t* arg,
    char* buffer,
    std::size_t sizeInBytes,
    std::size_t precision,
    int caps,
    _locale_t plocinfo);

errno_t __cdecl __cfltcvt_l(
    double* arg,
    char* buffer,
    std::size_t sizeInBytes,
    int format,
    int precision,
    int caps,
    _locale_t plocinfo)
{
    errno_t result;

    if ((format == 0x65) || (format == 0x45))
    {
        result = __cftoe_l(
            reinterpret_cast<std::uint32_t*>(arg),
            buffer,
            sizeInBytes,
            precision,
            caps,
            plocinfo);
    }
    else if (format == 0x66)
    {
        result = __cftof_l(
            reinterpret_cast<std::uint32_t*>(arg),
            buffer,
            sizeInBytes,
            precision,
            plocinfo);
        return result;
    }
    else if ((format == 0x61) || (format == 0x41))
    {
        const int extraout_EAX = __cftoa_l(
            arg,
            buffer,
            sizeInBytes,
            precision,
            caps,
            plocinfo);

        result = static_cast<errno_t>(extraout_EAX);
    }
    else
    {
        result = __cftog_l(
            reinterpret_cast<std::uint32_t*>(arg),
            buffer,
            sizeInBytes,
            precision,
            caps,
            plocinfo);
    }

    return result;
}