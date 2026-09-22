#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <windows.h>

extern "C" wchar_t* __cdecl __GET_RTERRMSG(int param_1);
extern "C" int __cdecl __set_error_mode(int mode);
extern "C" errno_t __cdecl _wcscpy_s(
    wchar_t* destination,
    std::size_t size,
    const wchar_t* source);
extern "C" errno_t __cdecl _wcsncpy_s(
    wchar_t* destination,
    std::size_t size,
    const wchar_t* source,
    std::size_t count);
extern "C" errno_t __cdecl _wcscat_s(
    wchar_t* destination,
    std::size_t size,
    const wchar_t* source);
extern "C" std::size_t __cdecl _wcslen(const wchar_t* string);
extern "C" std::size_t __cdecl _strlen(const char* string);
extern "C" int __cdecl ___crtMessageBoxW(
    const wchar_t* text,
    const wchar_t* caption,
    unsigned int type);
extern "C" [[noreturn]] void __cdecl __invoke_watson(
    wchar_t* expression,
    wchar_t* function,
    wchar_t* file,
    unsigned int line,
    std::uintptr_t reserved);
extern "C" void __fastcall __security_check_cookie(std::uintptr_t cookie);

extern "C" unsigned int DAT_10029490;
extern "C" int DAT_10039a00;
extern "C" wchar_t DAT_10039b54[];
extern "C" wchar_t DAT_10039b98[];
extern "C" wchar_t DAT_10039bca[];
extern "C" unsigned short _DAT_10039dd2;

extern "C" void __cdecl __NMSG_WRITE(int param_1)
{
    wchar_t* pwVar1;
    int iVar2;
    errno_t eVar3;
    DWORD DVar4;
    std::size_t sVar5;
    HANDLE hFile;
    unsigned int uVar6;
    wchar_t** lpNumberOfBytesWritten;
    LPOVERLAPPED lpOverlapped;
    wchar_t* local_200;
    char local_1fc[500];
    std::uintptr_t local_8 =
        static_cast<std::uintptr_t>(DAT_10029490) ^
        reinterpret_cast<std::uintptr_t>(&local_8);

    pwVar1 = __GET_RTERRMSG(param_1);

    if (pwVar1 != nullptr)
    {
        local_200 = pwVar1;
        iVar2 = __set_error_mode(3);

        if ((iVar2 == 1) ||
            ((iVar2 = __set_error_mode(3), iVar2 == 0) &&
             (DAT_10039a00 == 1)))
        {
            hFile = GetStdHandle(0xfffffff4);

            if ((hFile != nullptr) && (hFile != INVALID_HANDLE_VALUE))
            {
                uVar6 = 0;

                do
                {
                    local_1fc[uVar6] = static_cast<char>(pwVar1[uVar6]);

                    if (pwVar1[uVar6] == L'\0')
                    {
                        break;
                    }

                    uVar6 = uVar6 + 1;
                } while (uVar6 < 500);

                lpOverlapped = nullptr;
                lpNumberOfBytesWritten = &local_200;
                local_1fc[499] = 0;
                sVar5 = _strlen(local_1fc);

                WriteFile(
                    hFile,
                    local_1fc,
                    static_cast<DWORD>(sVar5),
                    reinterpret_cast<LPDWORD>(lpNumberOfBytesWritten),
                    lpOverlapped);
            }
        }
        else if (param_1 != 0xfc)
        {
            eVar3 = _wcscpy_s(
                DAT_10039b98,
                0x314,
                L"Runtime Error!\n\nProgram: ");

            if (eVar3 == 0)
            {
                _DAT_10039dd2 = 0;

                DVar4 = GetModuleFileNameW(
                    nullptr,
                    DAT_10039bca,
                    0x104);

                if ((DVar4 != 0) ||
                    ((eVar3 = _wcscpy_s(
                          DAT_10039bca,
                          0x2fb,
                          L"<program name unknown>"),
                      eVar3 == 0)))
                {
                    sVar5 = _wcslen(DAT_10039bca);

                    if (0x3c < sVar5 + 1)
                    {
                        sVar5 = _wcslen(DAT_10039bca);

                        eVar3 = _wcsncpy_s(
                            reinterpret_cast<wchar_t*>(
                                reinterpret_cast<std::uint8_t*>(DAT_10039b54) +
                                sVar5 * 2),
                            0x2fb -
                                ((static_cast<int>(sVar5 * 2 + -0x76)) >> 1),
                            L"...",
                            3);

                        if (eVar3 != 0)
                        {
                            goto LAB_1001719b;
                        }
                    }

                    eVar3 = _wcscat_s(
                        DAT_10039b98,
                        0x314,
                        L"\n\n");

                    if ((eVar3 == 0) &&
                        ((eVar3 = _wcscat_s(
                              DAT_10039b98,
                              0x314,
                              local_200),
                          eVar3 == 0)))
                    {
                        ___crtMessageBoxW(
                            DAT_10039b98,
                            L"Microsoft Visual C++ Runtime Library",
                            0x12010);
                        __security_check_cookie(
                            local_8 ^
                            reinterpret_cast<std::uintptr_t>(&local_8));
                        return;
                    }
                }
            }

        LAB_1001719b:
            __invoke_watson(nullptr, nullptr, nullptr, 0, 0);
        }
    }

    __security_check_cookie(
        local_8 ^ reinterpret_cast<std::uintptr_t>(&local_8));
}