#include <cstdint>

struct _ptiddata;
using signal_handler = void(__cdecl*)(...);

extern "C" std::uint32_t DAT_1003a31c;
extern "C" std::uint32_t DAT_1003a320;
extern "C" std::uint32_t DAT_1003a324;
extern "C" std::uint32_t DAT_1003a328;
extern "C" std::int32_t DAT_10022800;
extern "C" std::int32_t DAT_10022804;
extern "C" void __cdecl __SEH_prolog4(...);
extern "C" void __cdecl __SEH_epilog4(...);

extern "C" _ptiddata* __cdecl __getptd_noexit();
extern "C" std::uint32_t __cdecl siglookup(std::uint32_t);
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void* __stdcall DecodePointer(void*);
extern "C" [[noreturn]] void __cdecl __exit(int);
extern "C" void __cdecl __lock(int);
extern "C" std::uint32_t __stdcall FUN_10014c40();
extern "C" void __stdcall FUN_1001803c();

struct _ptiddata
{
    void* _pxcptacttab;
    void* _tpxcptinfoptrs;
    int   _tfpecode;
};

extern "C" int __cdecl _raise(int _SigNum)
{
    bool bVar1;
    std::uint32_t uVar2;
    int* piVar3;
    void* Ptr;
    signal_handler pcVar4;
    std::uint32_t uVar5;
    std::uint32_t* puVar6;
    _ptiddata* p_Var7;
    // Ghidra shows these are saved and restored only on the matching signal paths.
    int local_34 = 0;
    void* local_30 = nullptr;
    int local_28;
    int result;

    __SEH_prolog4();
    bVar1 = false;
    Ptr = nullptr;
    p_Var7 = nullptr;
    result = 0;

    if (_SigNum < 0x0c)
    {
        if (_SigNum != 0x0b)
        {
            if (_SigNum == 2)
            {
                puVar6 = &DAT_1003a31c;
                Ptr = reinterpret_cast<void*>(
                    static_cast<std::uintptr_t>(DAT_1003a31c));
                goto LAB_10017f7f;
            }

            if (_SigNum != 4)
            {
                if (_SigNum == 6)
                    goto LAB_10017f5d;

                if (_SigNum != 8)
                    goto LAB_10017f4b;
            }
        }

        p_Var7 = __getptd_noexit();
        if (p_Var7 == nullptr)
        {
            result = -1;
            goto finish;
        }

        uVar2 = siglookup(
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(p_Var7->_pxcptacttab)));

        puVar6 = reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(uVar2) + 8);

        pcVar4 = reinterpret_cast<signal_handler*>(
            static_cast<std::uintptr_t>(*puVar6))[0];
    }
    else
    {
        if (_SigNum == 0x0f)
        {
            puVar6 = &DAT_1003a328;
            Ptr = reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(DAT_1003a328));
        }
        else if (_SigNum == 0x15)
        {
            puVar6 = &DAT_1003a320;
            Ptr = reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(DAT_1003a320));
        }
        else
        {
            if (_SigNum != 0x16)
            {
LAB_10017f4b:
                piVar3 = __errno();
                *piVar3 = 0x16;
                FUN_1001189f();
                result = -1;
                goto finish;
            }

LAB_10017f5d:
            puVar6 = &DAT_1003a324;
            Ptr = reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(DAT_1003a324));
        }

LAB_10017f7f:
        bVar1 = true;
        pcVar4 = reinterpret_cast<signal_handler*>(DecodePointer(Ptr))[0];
    }

    if (pcVar4 == reinterpret_cast<signal_handler>(
                     static_cast<std::uintptr_t>(1)))
    {
        result = 0;
        goto finish;
    }

    if (pcVar4 == nullptr)
        __exit(3);

    if (bVar1)
        __lock(0);

    if ((_SigNum == 8) || (_SigNum == 0x0b) || (_SigNum == 4))
    {
        local_30 = p_Var7->_tpxcptinfoptrs;
        p_Var7->_tpxcptinfoptrs = nullptr;

        if (_SigNum == 8)
        {
            local_34 = p_Var7->_tfpecode;
            p_Var7->_tfpecode = 0x8c;
            goto LAB_10017fe3;
        }
    }
    else
    {
LAB_10017fe3:
        if (_SigNum == 8)
        {
            for (local_28 = DAT_10022800;
                 local_28 < DAT_10022804 + DAT_10022800;
                 ++local_28)
            {
                *reinterpret_cast<std::uint32_t*>(
                    local_28 * 0x0c + 8 +
                    static_cast<std::uintptr_t>(
                        reinterpret_cast<std::uintptr_t>(
                            p_Var7->_pxcptacttab))) = 0;
            }

            goto LAB_1001801b;
        }
    }

    uVar5 = FUN_10014c40();
    *puVar6 = uVar5;

LAB_1001801b:
    FUN_1001803c();

    if (_SigNum == 8)
        pcVar4(8, p_Var7->_tfpecode);
    else
    {
        pcVar4(_SigNum);

        if ((_SigNum != 0x0b) && (_SigNum != 4))
        {
            result = 0;
            goto finish;
        }
    }

    p_Var7->_tpxcptinfoptrs = local_30;

    if (_SigNum == 8)
        p_Var7->_tfpecode = local_34;

finish:
    __SEH_epilog4();
    return result;
}