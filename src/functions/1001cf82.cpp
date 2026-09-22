#include <cstdint>

int __cdecl ___AdjustPointer(int param_1, int* param_2)
{
    int adjusted_pointer = *param_2 + param_1;

    if (param_2[1] >= 0)
    {
        adjusted_pointer =
            adjusted_pointer +
            *reinterpret_cast<int*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<int*>(
                        static_cast<std::uintptr_t>(param_2[1] + param_1)) +
                    param_2[2])) +
            param_2[1];
    }

    return adjusted_pointer;
}