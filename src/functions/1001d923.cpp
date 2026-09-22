#include <cstdint>

#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
struct EHExceptionRecord;
struct EHRegistrationNode;
struct _CONTEXT;
struct ESTypeList;
struct _s_FuncInfo {
    std::uint32_t magicNumber_and_bbtFlags;
    std::int32_t maxState;
    std::uint32_t pUnwindMap;
    std::uint32_t nTryBlocks;
    std::uint32_t pTryBlockMap;
    std::uint32_t nIPMapEntries;
    std::uint32_t pIPtoStateMap;
    ESTypeList* pESTypeList;
    std::uint32_t EHFlags;
};
static_assert(offsetof(_s_FuncInfo, nTryBlocks) == 0x0c);
static_assert(offsetof(_s_FuncInfo, pESTypeList) == 0x1c);
static_assert(offsetof(_s_FuncInfo, EHFlags) == 0x20);
extern "C" void __cdecl FindHandler(
    EHExceptionRecord*, EHRegistrationNode*, _CONTEXT*, void*, _s_FuncInfo*,
    std::uint8_t, int, EHRegistrationNode*);
extern "C" void __cdecl ___FrameUnwindToState(int, void*, int, int);

extern "C" void* __cdecl __getptd(void);

std::uint32_t __cdecl ___InternalCxxFrameHandler(
    EHExceptionRecord* param_1,
    EHRegistrationNode* param_2,
    _CONTEXT* param_3,
    void* param_4,
    _s_FuncInfo* param_5,
    int param_6,
    EHRegistrationNode* param_7,
    unsigned char param_8)
{
    auto* p_Var1 = reinterpret_cast<std::uint8_t*>(__getptd());

    if (((*reinterpret_cast<int*>(
              p_Var1 + 0x20c) != 0) ||
         (*reinterpret_cast<int*>(
              reinterpret_cast<std::uint8_t*>(param_1) + 0x00) ==
          -0x1f928c9d)) ||
        (*reinterpret_cast<int*>(
             reinterpret_cast<std::uint8_t*>(param_1) + 0x00) ==
         -0x7fffffda) ||
        (((param_5->magicNumber_and_bbtFlags & 0x1fffffff) < 0x19930522) ||
         ((param_5->EHFlags & 1) == 0)))
    {
        if ((*reinterpret_cast<std::uint8_t*>(
                 reinterpret_cast<std::uint8_t*>(param_1) + 0x04) &
             0x66) == 0)
        {
            if ((param_5->nTryBlocks != 0) ||
                ((0x19930520 <
                      (param_5->magicNumber_and_bbtFlags & 0x1fffffff)) &&
                 (param_5->pESTypeList != nullptr)))
            {
                if ((*reinterpret_cast<int*>(
                         reinterpret_cast<std::uint8_t*>(param_1) + 0x00) ==
                     -0x1f928c9d) &&
                    (2 < *reinterpret_cast<std::uint32_t*>(
                              reinterpret_cast<std::uint8_t*>(param_1) +
                              0x10)) &&
                    (0x19930522 <
                     *reinterpret_cast<std::uint32_t*>(
                         reinterpret_cast<std::uint8_t*>(param_1) + 0x14)) &&
                    (*reinterpret_cast<void (**)(EHExceptionRecord*,
                                                  EHRegistrationNode*,
                                                  _CONTEXT*,
                                                  void*,
                                                  _s_FuncInfo*,
                                                  int,
                                                  EHRegistrationNode*,
                                                  unsigned char)>(
                         static_cast<std::uintptr_t>(
                             *reinterpret_cast<std::uint32_t*>(
                                 reinterpret_cast<std::uint8_t*>(param_1) +
                                 0x1c)) +
                         8) != nullptr))
                {
                    using Handler = std::uint32_t(__cdecl*)(
                        EHExceptionRecord*,
                        EHRegistrationNode*,
                        _CONTEXT*,
                        void*,
                        _s_FuncInfo*,
                        int,
                        EHRegistrationNode*,
                        unsigned char);

                    const auto handler =
                        *reinterpret_cast<Handler*>(
                            static_cast<std::uintptr_t>(
                                *reinterpret_cast<std::uint32_t*>(
                                    reinterpret_cast<std::uint8_t*>(param_1) +
                                    0x1c)) +
                            8);

                    return handler(
                        param_1,
                        param_2,
                        param_3,
                        param_4,
                        param_5,
                        param_6,
                        param_7,
                        param_8);
                }

                FindHandler(
                    param_1,
                    param_2,
                    param_3,
                    param_4,
                    param_5,
                    param_8,
                    param_6,
                    param_7);
            }
        }
        else if ((param_5->maxState != 0) && (param_6 == 0))
        {
            ___FrameUnwindToState(
                static_cast<int>(
                    reinterpret_cast<std::uintptr_t>(param_2)),
                param_4,
                static_cast<int>(
                    reinterpret_cast<std::uintptr_t>(param_5)),
                -1);
        }
    }

    return 1;
}