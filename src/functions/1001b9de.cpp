#include <cstdint>
#include "gta_sa_address_access.hpp"

struct EHRegistrationNode;
struct _s_FuncInfo;

extern "C" std::uint32_t DAT_10029490;

extern "C" void __cdecl CatchGuardHandler();

extern "C" void* __stdcall __CallSettingFrame_12(
    void* param_1,
    EHRegistrationNode* param_2,
    unsigned long param_3);

extern "C" void* __cdecl _CallCatchBlock2(
    EHRegistrationNode* param_1,
    _s_FuncInfo* param_2,
    void* param_3,
    int param_4,
    unsigned long param_5)
{
    void* result;
    void* local_1c;
    void (*local_18)();
    std::uint32_t local_14;
    _s_FuncInfo* local_10;
    EHRegistrationNode* local_c;
    int local_8;

    local_14 = DAT_10029490 ^
               static_cast<std::uint32_t>(
                   reinterpret_cast<std::uintptr_t>(&local_1c));
    local_10 = param_2;
    local_8 = param_4 + 1;
    local_18 = CatchGuardHandler;
    local_c = param_1;

    local_1c = IMVEHFT_READ_EXCEPTION_LIST();
    IMVEHFT_WRITE_EXCEPTION_LIST(&local_1c);

    result = __CallSettingFrame_12(param_3, param_1, param_5);

    IMVEHFT_WRITE_EXCEPTION_LIST(local_1c);
    return result;
}
