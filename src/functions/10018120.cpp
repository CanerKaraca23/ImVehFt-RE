#include "imvehft_image_aliases.hpp"
#include <Windows.h>
#include "gta_sa_address_access.hpp"

extern "C" BOOL __cdecl __ValidateImageBase(PBYTE pImageBase);
extern "C" PIMAGE_SECTION_HEADER __cdecl __FindPESection(
    PBYTE pImageBase,
    DWORD_PTR rva);
extern "C" void __cdecl __except_handler4();

extern "C" BOOL __cdecl __IsNonwritableInCurrentImage(PBYTE pTarget)
{
    void* pcStack_10 = reinterpret_cast<void*>(&__except_handler4);
    void* local_14 = IMVEHFT_READ_EXCEPTION_LIST();
    unsigned int local_c =
        *reinterpret_cast<unsigned int*>(IVF_IMAGE_ADDRESS_10029490) ^ IVF_IMAGE_ADDRESS_100284C0;

    IMVEHFT_WRITE_EXCEPTION_LIST(&local_14);

    unsigned int local_8 = 0;

    (void)pcStack_10;
    (void)local_c;
    (void)local_8;

    PBYTE imageBase = reinterpret_cast<PBYTE>(0x10000000u);
    BOOL result = __ValidateImageBase(imageBase);

    if (result != 0)
    {
        PIMAGE_SECTION_HEADER section =
            __FindPESection(
                imageBase,
                reinterpret_cast<DWORD_PTR>(pTarget) - 0x10000000u);

        if (section != nullptr)
        {
            IMVEHFT_WRITE_EXCEPTION_LIST(local_14);
            return static_cast<BOOL>(
                ~(section->Characteristics >> 0x1f) & 1u);
        }
    }

    IMVEHFT_WRITE_EXCEPTION_LIST(local_14);
    return 0;
}
