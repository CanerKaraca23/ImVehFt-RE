#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" errno_t __cdecl __cfltcvt_l(double* arg, char* buffer, size_t sizeInBytes, int format, int precision, int caps, _locale_t plocinfo);

errno_t __cdecl __cfltcvt(
    double* arg,
    char* buffer,
    size_t sizeInBytes,
    int format,
    int precision,
    int caps)
{
    errno_t result = __cfltcvt_l(
        arg,
        buffer,
        sizeInBytes,
        format,
        precision,
        caps,
        static_cast<_locale_t>(nullptr));

    return result;
}