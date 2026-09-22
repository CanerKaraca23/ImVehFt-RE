#include <cstddef>



extern "C" void* __cdecl __calloc_crt(std::size_t count, std::size_t size);
extern "C" void* __cdecl __recalloc_crt(
    void* memory,
    std::size_t count,
    std::size_t size);
extern "C" void* __cdecl FID_conflict__memcpy(
    void* destination,
    const void* source,
    std::size_t count);

extern "C" unsigned int __cdecl ___check_float_string(
    std::size_t param_1,
    void* param_2,
    unsigned int* param_3)
{
    std::size_t* unaff_ESI;
    void** unaff_EDI;
    __asm mov unaff_ESI, esi
    __asm mov unaff_EDI, edi
    const std::size_t count = *unaff_ESI;

    if (param_1 == count)
    {
        if (*unaff_EDI == param_2)
        {
            void* allocation = __calloc_crt(count, 2);
            *unaff_EDI = allocation;

            if (allocation == nullptr)
            {
                return 0;
            }

            *param_3 = 1;
            FID_conflict__memcpy(*unaff_EDI, param_2, *unaff_ESI);
        }
        else
        {
            void* allocation = __recalloc_crt(*unaff_EDI, count, 2);

            if (allocation == nullptr)
            {
                return 0;
            }

            *unaff_EDI = allocation;
        }

        *unaff_ESI = *unaff_ESI << 1;
    }

    return 1;
}