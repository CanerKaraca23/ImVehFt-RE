#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#include <cstddef>
#include <cstdio>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <cstddef>
#include <cstdio>

extern char DAT_1003a6c5;
extern char DAT_1003a8c8;

extern "C" int __stdcall MessageBoxA(
    void* hWnd,
    const char* lpText,
    const char* lpCaption,
    unsigned int uType);

extern "C" int __cdecl strcpy_s(
    char* destination,
    std::size_t size,
    const char* source);

extern "C" int __cdecl strcat_s(
    char* destination,
    std::size_t size,
    const char* source);

extern "C" FILE* __cdecl fopen(
    const char* filename,
    const char* mode);

extern "C" FILE* __stdcall FUN_10001520(void)
{
    FILE* pFVar1;
    char local_204[512];

    if (DAT_1003a6c5 == '\0')
    {
        MessageBoxA(
            nullptr,
            "CFile::m_bInitialised - FALSE",
            "CFile::Open",
            0);

        return nullptr;
    }

    strcpy_s(local_204, 0x200, &DAT_1003a8c8);
    strcat_s(local_204, 0x200, "ImVehFt.log");

    pFVar1 = fopen(local_204, "w");
    return pFVar1;
}