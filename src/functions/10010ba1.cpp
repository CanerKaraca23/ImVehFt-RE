#include <cstddef>
#include <cstdint>
#include <new>

struct pthreadmbcinfo;
struct pthreadlocinfo
{
    std::uint8_t _reserved_00[0x14];
    struct LocaleCategory0
    {
        wchar_t* wlocale;
    } lc_category[1];
};

struct localeinfo_struct
{
    pthreadlocinfo* locinfo;
    pthreadmbcinfo* mbcinfo;
};

struct _ptiddata
{
    std::uint8_t _reserved_00[0x68];
    pthreadmbcinfo* ptmbcinfo;
    pthreadlocinfo* ptlocinfo;
    std::uint32_t _ownlocale;
};

struct _LocaleUpdate
{
    pthreadlocinfo* locinfo;
    pthreadmbcinfo* mbcinfo;
    _ptiddata* ptd;
    std::uint8_t updated;
    _LocaleUpdate(localeinfo_struct* locale);
};

extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" int __cdecl ___ascii_strnicmp(char*, char*, std::size_t);
extern "C" int __cdecl __tolower_l(int, _LocaleUpdate*);

int __cdecl _strnicmp_l(
    char* _Str1,
    char* _Str2,
    std::size_t _MaxCount,
    _locale_t _Locale)
{
    int* piVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    alignas(_LocaleUpdate) std::uint8_t local_storage[sizeof(_LocaleUpdate)];
    _LocaleUpdate* local_14 = reinterpret_cast<_LocaleUpdate*>(local_storage);

    if (_MaxCount == 0)
    {
        iVar2 = 0;
    }
    else
    {
        ::new (static_cast<void*>(local_14)) _LocaleUpdate(reinterpret_cast<localeinfo_struct*>(_Locale));

        if ((_Str1 == nullptr) || (_Str2 == nullptr))
        {
            piVar1 = __errno();
            *piVar1 = 0x16;
            FUN_1001189f();

            if (local_14->updated != 0)
            {
                local_14->ptd->_ownlocale &= ~2U;
            }

            iVar2 = 0x7fffffff;
        }
        else if (_MaxCount < 0x80000000U)
        {
            if (local_14->locinfo->lc_category[0].wlocale == nullptr)
            {
                iVar2 = ___ascii_strnicmp(_Str1, _Str2, _MaxCount);
            }
            else
            {
                iVar4 = static_cast<int>(
                    reinterpret_cast<std::uintptr_t>(_Str1)) -
                    static_cast<int>(
                        reinterpret_cast<std::uintptr_t>(_Str2));

                do
                {
                    iVar2 = __tolower_l(
                        static_cast<unsigned int>(
                            static_cast<unsigned char>(_Str2[iVar4])),
                        local_14);

                    iVar3 = __tolower_l(
                        static_cast<unsigned int>(
                            static_cast<unsigned char>(*_Str2)),
                        local_14);

                    _Str2 = _Str2 + 1;
                    _MaxCount = _MaxCount - 1;

                    if ((_MaxCount == 0) || (iVar2 == 0))
                    {
                        break;
                    }
                }
                while (iVar2 == iVar3);

                iVar2 = iVar2 - iVar3;
            }

            if (local_14->updated != 0)
            {
                local_14->ptd->_ownlocale &= ~2U;
            }
        }
        else
        {
            piVar1 = __errno();
            *piVar1 = 0x16;
            FUN_1001189f();

            if (local_14->updated != 0)
            {
                local_14->ptd->_ownlocale &= ~2U;
            }

            iVar2 = 0x7fffffff;
        }
    }

    return iVar2;
}