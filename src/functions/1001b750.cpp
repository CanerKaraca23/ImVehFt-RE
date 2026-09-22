#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using undefined4 = std::uint32_t;
using uint = std::uint32_t;
using undefined = unsigned char;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined8 = std::uint64_t;
#pragma warning(disable:4733)
struct EHExceptionRecord { std::uint32_t ExceptionCode; };
struct EHRegistrationNode;
struct _s_FuncInfo;
typedef void (__cdecl code)(std::uint32_t, void*);
struct _ptiddata
{
    std::uint8_t reserved_00[0x80];
    code* _translator;
};
static_assert(offsetof(_ptiddata, _translator) == 0x80);
extern "C" _ptiddata* __cdecl __getptd(void);
extern std::uint32_t DAT_10029490;

int __cdecl _CallSETranslator(
    EHExceptionRecord* param_1,
    EHRegistrationNode* param_2,
    void* param_3,
    void* ,
    _s_FuncInfo* param_5,
    int param_6,
    EHRegistrationNode* param_7)
{
    int local_3c;
    EHExceptionRecord* local_38;
    void* local_34;
    code* local_30;
    undefined4* local_2c;
    code* local_28;
    uint local_24;
    _s_FuncInfo* local_20;
    EHRegistrationNode* local_1c;
    int local_18;
    EHRegistrationNode* local_14;
    int local_8;


    if (param_1 == reinterpret_cast<EHExceptionRecord*>(0x123))
    {
        *reinterpret_cast<undefined4*>(param_2) = 0x1001B7FB;
        local_3c = 1;
    }
    else
    {
        local_28 = reinterpret_cast<code*>(0x1001B827u);
        local_24 = DAT_10029490 ^
                   static_cast<uint>(
                       reinterpret_cast<uintptr_t>(&local_2c));
        local_20 = param_5;
        local_1c = param_2;
        local_18 = param_6;
        local_14 = param_7;
        local_8 = 0;

        __asm {
            mov eax, fs:[0]
            mov local_2c, eax
        }
        __asm {
            lea eax, local_2c
            mov fs:[0], eax
        }

        local_38 = param_1;
        local_34 = param_3;

        _ptiddata* p_Var1 = __getptd();
        local_30 = p_Var1->_translator;

        (*local_30)(
            *reinterpret_cast<undefined4*>(param_1),
            &local_38);

        local_3c = 0;

        if (local_8 != 0)
        {
            __asm {
                mov eax, fs:[0]
                mov edx, local_2c
                mov dword ptr [edx], eax
            }
        }

        __asm {
            mov eax, local_2c
            mov fs:[0], eax
        }
    }

    return local_3c;
}