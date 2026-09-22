#include <cstdint>

struct pthreadlocinfo;
struct pthreadmbcinfo;

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
    pthreadlocinfo* locinfo;        // offset 0x00
    pthreadmbcinfo* mbcinfo;        // offset 0x04
    _ptiddata* ptd;                 // offset 0x08
    std::uint8_t updated;           // offset 0x0C
    _LocaleUpdate(localeinfo_struct* locale);
};

extern pthreadlocinfo* PTR_DAT_10029c08;
extern pthreadmbcinfo* PTR_DAT_100298c8;
extern std::uint32_t DAT_100299c0;

extern _ptiddata* __cdecl __getptd();
extern pthreadlocinfo* __cdecl ___updatetlocinfo();
extern pthreadmbcinfo* __cdecl ___updatetmbcinfo();

_LocaleUpdate::_LocaleUpdate(localeinfo_struct* param_1)
{
    this->updated = 0;

    if (param_1 == nullptr)
    {
        _ptiddata* thread_data = __getptd();

        this->ptd = thread_data;
        this->locinfo = thread_data->ptlocinfo;
        this->mbcinfo = thread_data->ptmbcinfo;

        if ((this->locinfo != PTR_DAT_10029c08) &&
            ((thread_data->_ownlocale & DAT_100299c0) == 0))
        {
            this->locinfo = ___updatetlocinfo();
        }

        if ((this->mbcinfo != PTR_DAT_100298c8) &&
            ((thread_data->_ownlocale & DAT_100299c0) == 0))
        {
            this->mbcinfo = ___updatetmbcinfo();
        }

        if ((thread_data->_ownlocale & 2U) == 0)
        {
            thread_data->_ownlocale = thread_data->_ownlocale | 2U;
            this->updated = 1;
        }
    }
    else
    {
        this->locinfo = param_1->locinfo;
        this->mbcinfo = param_1->mbcinfo;
    }

}