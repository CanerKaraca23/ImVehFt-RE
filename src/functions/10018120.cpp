#include <Windows.h>

extern "C" PVOID ExceptionList;
extern "C" BOOL __cdecl __ValidateImageBase(PBYTE pImageBase);
extern "C" PIMAGE_SECTION_HEADER __cdecl __FindPESection(
    PBYTE pImageBase,
    DWORD_PTR rva);
extern "C" void __cdecl __except_handler4();

extern "C" BOOL __cdecl __IsNonwritableInCurrentImage(PBYTE pTarget)
{
    void* pcStack_10 = reinterpret_cast<void*>(&__except_handler4);
    void* local_14 = ExceptionList;
    unsigned int local_c =
        *reinterpret_cast<unsigned int*>(0x10029490) ^ 0x100284c0u;

    ExceptionList = &local_14;

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
            ExceptionList = local_14;
            return static_cast<BOOL>(
                ~(section->Characteristics >> 0x1f) & 1u);
        }
    }

    ExceptionList = local_14;
    return 0;
}