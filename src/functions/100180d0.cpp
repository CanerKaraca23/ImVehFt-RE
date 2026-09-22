#include <Windows.h>

extern "C" PIMAGE_SECTION_HEADER __cdecl __FindPESection(
    PBYTE pImageBase,
    DWORD_PTR rva)
{
    const int iVar1 = *reinterpret_cast<int*>(pImageBase + 0x3C);
    unsigned int uVar3 = 0;

    auto* p_Var2 = reinterpret_cast<PIMAGE_SECTION_HEADER>(
        pImageBase +
        *reinterpret_cast<unsigned short*>(pImageBase + iVar1 + 0x14) +
        0x18 +
        iVar1);

    if (*reinterpret_cast<unsigned short*>(pImageBase + iVar1 + 0x06) != 0)
    {
        do
        {
            if ((p_Var2->VirtualAddress <= rva) &&
                (rva < p_Var2->Misc.PhysicalAddress + p_Var2->VirtualAddress))
            {
                return p_Var2;
            }

            uVar3 = uVar3 + 1;
            p_Var2 = p_Var2 + 1;
        }
        while (uVar3 < *reinterpret_cast<unsigned short*>(
                            pImageBase + iVar1 + 0x06));
    }

    return nullptr;
}