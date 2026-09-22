#include <cstddef>
#include <cstdint>
#include <cwchar>

extern "C" std::uint32_t DAT_1003d550;
extern "C" char* DAT_100399f4;
extern "C" char** DAT_10039a1c;
extern "C" std::uint32_t _DAT_1003d544;

extern "C" void __stdcall ___initmbctable(void);
extern "C" std::size_t __cdecl _strlen(const char* string);
extern "C" void* __cdecl __calloc_crt(std::size_t count, std::size_t size);
extern "C" int __cdecl strcpy_s(char* destination, std::size_t size,
                                 const char* source);
extern "C" void __cdecl _free(void* block);
extern "C" [[noreturn]] void __cdecl __invoke_watson(
    wchar_t* expression,
    wchar_t* functionName,
    wchar_t* fileName,
    unsigned int lineNumber,
    std::uintptr_t reserved);

extern "C" std::uint32_t __stdcall FUN_100168fe(void)
{
    char** puVar1;
    std::size_t sVar2;
    char* _Dst;
    int eVar3;
    char* pcVar4;
    int iVar5;

    if (DAT_1003d550 == 0)
    {
        ___initmbctable();
    }

    iVar5 = 0;
    pcVar4 = DAT_100399f4;

    if (DAT_100399f4 != nullptr)
    {
        for (; *pcVar4 != '\0'; pcVar4 = pcVar4 + sVar2 + 1)
        {
            if (*pcVar4 != '=')
            {
                iVar5 = iVar5 + 1;
            }

            sVar2 = _strlen(pcVar4);
        }

        puVar1 = static_cast<char**>(
            __calloc_crt(static_cast<std::size_t>(iVar5 + 1), 4));

        pcVar4 = DAT_100399f4;
        DAT_10039a1c = puVar1;

        if (puVar1 != nullptr)
        {
            do
            {
                if (*pcVar4 == '\0')
                {
                    _free(DAT_100399f4);
                    DAT_100399f4 = nullptr;
                    *puVar1 = nullptr;
                    _DAT_1003d544 = 1;
                    return 0;
                }

                sVar2 = _strlen(pcVar4);
                sVar2 = sVar2 + 1;

                if (*pcVar4 != '=')
                {
                    _Dst = static_cast<char*>(__calloc_crt(sVar2, 1));
                    *puVar1 = _Dst;

                    if (_Dst == nullptr)
                    {
                        _free(DAT_10039a1c);
                        DAT_10039a1c = nullptr;
                        return 0xffffffffu;
                    }

                    eVar3 = strcpy_s(_Dst, sVar2, pcVar4);

                    if (eVar3 != 0)
                    {
                        __invoke_watson(nullptr, nullptr, nullptr, 0, 0);
                    }

                    puVar1 = puVar1 + 1;
                }

                pcVar4 = pcVar4 + sVar2;
            } while (true);
        }
    }

    return 0xffffffffu;
}