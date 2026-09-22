#include <cstddef>
#include <cstdint>

using errno_t = int;
using UINT = std::uint32_t;
using DWORD = std::uint32_t;
using BOOL = std::int32_t;

extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" void* __cdecl _memset(void* _Dst, int _Val, std::size_t _Size);

struct _LocaleUpdate
{
    std::uint32_t local_14[2];
    std::int32_t local_c;
    char local_8;
};

using LocaleUpdateCtor = void(__thiscall*)(
    _LocaleUpdate* _This, _locale_t _Locale);

extern "C" int __stdcall
WideCharToMultiByte(
    UINT _CodePage,
    std::uint32_t _Flags,
    const wchar_t* _WideCharStr,
    int _WideCharCount,
    char* _MultiByteStr,
    int _MultiByteCount,
    const char* _DefaultChar,
    BOOL* _UsedDefaultChar);

extern "C" DWORD __stdcall GetLastError(void);

static __forceinline void set_errno_and_report(int value)
{
    int* error_slot = __errno();
    *error_slot = value;
    FUN_1001189f();
}

extern "C" errno_t __cdecl
__wctomb_s_l(
    int* _SizeConverted,
    char* _MbCh,
    std::size_t _SizeInBytes,
    wchar_t _WCh,
    _locale_t _Locale)
{
    char* lpMultiByteStr = _MbCh;
    std::size_t _Size = _SizeInBytes;
    int iVar1;
    int* piVar2;
    DWORD DVar3;

    _LocaleUpdate local_14{};

    if ((_MbCh == nullptr) && (_SizeInBytes != 0))
    {
        if (_SizeConverted != nullptr)
        {
            *_SizeConverted = 0;
        }

        iVar1 = 0;
    }
    else
    {
        if (_SizeConverted != nullptr)
        {
            *_SizeConverted = -1;
        }

        if (0x7fffffff < _SizeInBytes)
        {
            set_errno_and_report(0x16);
            return 0x16;
        }

        // Ghidra 0x1001a7d8: ECX=&local_14, pushed _Locale, CALL 0x10010b1a.
        reinterpret_cast<LocaleUpdateCtor>(0x10010b1a)(&local_14, _Locale);

        if (*reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uintptr_t*>(local_14.local_14[0]) + 0x14 / sizeof(std::uintptr_t)) == 0)
        {
            if (static_cast<std::uint16_t>(_WCh) < 0x100)
            {
                if (lpMultiByteStr != nullptr)
                {
                    if (_Size == 0)
                    {
                        set_errno_and_report(0x22);

                        if (local_14.local_8 == '\0')
                        {
                            return 0x22;
                        }

                        *reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(local_14.local_c) + 0x70) &=
                            0xfffffffd;

                        return 0x22;
                    }

                    *lpMultiByteStr = static_cast<char>(_WCh);
                }

                if (_SizeConverted != nullptr)
                {
                    *_SizeConverted = 1;
                }

                if (local_14.local_8 != '\0')
                {
                    *reinterpret_cast<std::uint32_t*>(
                        static_cast<std::uintptr_t>(local_14.local_c) + 0x70) &=
                        0xfffffffd;
                }

                iVar1 = 0;
            }
            else
            {
                if ((lpMultiByteStr != nullptr) && (_Size != 0))
                {
                    _memset(lpMultiByteStr, 0, _Size);
                }

                set_errno_and_report(0x22);

                if (local_14.local_8 == '\0')
                {
                    return 0x22;
                }

                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(local_14.local_c) + 0x70) &=
                    0xfffffffd;

                return 0x22;
            }
        }
        else
        {
            _MbCh = nullptr;

            iVar1 = WideCharToMultiByte(
                *reinterpret_cast<UINT*>(
                    static_cast<std::uintptr_t>(local_14.local_14[0]) + 4),
                0,
                &_WCh,
                1,
                lpMultiByteStr,
                static_cast<int>(_Size),
                nullptr,
                reinterpret_cast<BOOL*>(&_MbCh));

            if (iVar1 == 0)
            {
                DVar3 = GetLastError();

                if (DVar3 == 0x7a)
                {
                    if ((lpMultiByteStr != nullptr) && (_Size != 0))
                    {
                        _memset(lpMultiByteStr, 0, _Size);
                    }

                    set_errno_and_report(0x22);

                    if (local_14.local_8 == '\0')
                    {
                        return 0x22;
                    }

                    *reinterpret_cast<std::uint32_t*>(
                        static_cast<std::uintptr_t>(local_14.local_c) + 0x70) &=
                        0xfffffffd;

                    return 0x22;
                }
            }
            else if (_MbCh == nullptr)
            {
                if (_SizeConverted != nullptr)
                {
                    *_SizeConverted = iVar1;
                }

                if (local_14.local_8 != '\0')
                {
                    *reinterpret_cast<std::uint32_t*>(
                        static_cast<std::uintptr_t>(local_14.local_c) + 0x70) &=
                        0xfffffffd;
                }

                iVar1 = 0;
            }

            piVar2 = __errno();
            *piVar2 = 0x2a;

            piVar2 = __errno();
            iVar1 = *piVar2;

            if (local_14.local_8 != '\0')
            {
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(local_14.local_c) + 0x70) &=
                    0xfffffffd;
            }
        }
    }

    return iVar1;
}