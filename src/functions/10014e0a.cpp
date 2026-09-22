#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#include <cstddef>
#include <cstdint>
extern "C" void __stdcall FUN_10014f24(void);
extern "C" void __stdcall FUN_10014f30(void);

#include <cstddef>
#include <cstdint>

extern "C" void __cdecl __SEH_prolog4(std::uint32_t, int);
extern "C" void __stdcall __SEH_epilog4(void);

void __stdcall __freefls_4(void* param_1)
{
    __SEH_prolog4(0x100283f8u, 0x08);

    using LONG = long;

    struct __freefls_data
    {
        unsigned char reserved_00[0x24];
        void* slot_24;
        unsigned char reserved_28[0x04];
        void* slot_2c;
        unsigned char reserved_30[0x04];
        void* slot_34;
        unsigned char reserved_38[0x04];
        void* slot_3c;
        void* slot_40;
        void* slot_44;
        void* slot_48;
        unsigned char reserved_4c[0x10];
        void* slot_5c;
        unsigned char reserved_60[0x08];
        LONG* slot_68;
        LONG* slot_6c;
    };
    static_assert(sizeof(LONG) == 4);
    static_assert(offsetof(__freefls_data, slot_24) == 0x24);
    static_assert(offsetof(__freefls_data, slot_2c) == 0x2c);
    static_assert(offsetof(__freefls_data, slot_34) == 0x34);
    static_assert(offsetof(__freefls_data, slot_3c) == 0x3c);
    static_assert(offsetof(__freefls_data, slot_40) == 0x40);
    static_assert(offsetof(__freefls_data, slot_44) == 0x44);
    static_assert(offsetof(__freefls_data, slot_48) == 0x48);
    static_assert(offsetof(__freefls_data, slot_5c) == 0x5c);
    static_assert(offsetof(__freefls_data, slot_68) == 0x68);
    static_assert(offsetof(__freefls_data, slot_6c) == 0x6c);

    extern void __cdecl _free(void*);
    extern void __cdecl __lock(int);
    extern LONG __stdcall InterlockedDecrement(LONG*);
    extern LONG* __cdecl ___removelocaleref(LONG*);
    extern void __cdecl ___freetlocinfo(void*);

    extern unsigned char DAT_10022770;
    extern LONG DAT_100294a0;
    extern LONG* PTR_DAT_10029c08;
    extern LONG DAT_10029b30;

    if (param_1 != nullptr)
    {
        __freefls_data* data = static_cast<__freefls_data*>(param_1);

        if (data->slot_24 != nullptr)
            _free(data->slot_24);
        if (data->slot_2c != nullptr)
            _free(data->slot_2c);
        if (data->slot_34 != nullptr)
            _free(data->slot_34);
        if (data->slot_3c != nullptr)
            _free(data->slot_3c);
        if (data->slot_40 != nullptr)
            _free(data->slot_40);
        if (data->slot_44 != nullptr)
            _free(data->slot_44);
        if (data->slot_48 != nullptr)
            _free(data->slot_48);
        if (data->slot_5c != &DAT_10022770)
            _free(data->slot_5c);

        __lock(0xd);

        LONG* pLVar1 = data->slot_68;
        if (pLVar1 != nullptr)
        {
            LONG LVar2 = InterlockedDecrement(pLVar1);
            if ((LVar2 == 0) && (pLVar1 != &DAT_100294a0))
                _free(pLVar1);
        }

        FUN_10014f24();

        __lock(0xc);

        pLVar1 = data->slot_6c;
        if (pLVar1 != nullptr)
        {
            ___removelocaleref(pLVar1);
            if ((pLVar1 != PTR_DAT_10029c08) &&
                (pLVar1 != &DAT_10029b30) &&
                (*pLVar1 == 0))
            {
                ___freetlocinfo(pLVar1);
            }
        }

        FUN_10014f30();
        _free(param_1);
    }
    __SEH_epilog4();
}