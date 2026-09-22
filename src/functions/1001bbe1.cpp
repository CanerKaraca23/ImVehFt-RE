#include <cmath>

int __cdecl __positive(double* arg)
{
    double dVar1 = *arg;

    if (!std::isnan(dVar1) &&
        (0.0 < dVar1 != (dVar1 == 0.0)))
    {
        return 1;
    }

    return 0;
}