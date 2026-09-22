#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct EHExceptionRecord; struct EHRegistrationNode; struct _CONTEXT; struct _s_CatchableType; struct _s_FuncInfo;
struct TypeDescriptor { void* pVFTable; void* spare; };
struct _s_HandlerType { unsigned int adjectives; TypeDescriptor* pType; int dispCatchObj; void* addressOfHandler; };
struct _s_TryBlockMapEntry { int tryLow; int tryHigh; int catchHigh; int nCatches; _s_HandlerType* pHandlerArray; };
struct _s_FuncInfo { unsigned int magicNumber; int maxState; void* pUnwindMap; unsigned int nTryBlocks; _s_TryBlockMapEntry* pTryBlockMap; };
struct _tiddata { std::uint8_t _pad_0000_0080[0x80]; void* _translator; };
static_assert(offsetof(_s_FuncInfo, nTryBlocks) == 0x0c);
static_assert(offsetof(_s_FuncInfo, pTryBlockMap) == 0x10);
static_assert(sizeof(_s_TryBlockMapEntry) == 0x14);
static_assert(offsetof(_s_HandlerType, addressOfHandler) == 0x0c);
static_assert(offsetof(_tiddata, _translator) == 0x80);
extern "C" _tiddata* __cdecl __getptd(void);
extern "C" void* __stdcall FUN_10014c40(void);
extern "C" void __cdecl _inconsistency(void);
extern "C" int __cdecl _CallSETranslator(EHExceptionRecord*, EHRegistrationNode*, _CONTEXT*, void*, _s_FuncInfo*, int, EHRegistrationNode*);
extern "C" _s_TryBlockMapEntry* __cdecl _GetRangeOfTrysToCheck(_s_FuncInfo*, int, int, unsigned int*, unsigned int*);
extern "C" void __cdecl CatchIt(void);
void __cdecl FindHandlerForForeignException(
    EHExceptionRecord* param_1,
    EHRegistrationNode* param_2,
    _CONTEXT* param_3,
    void* param_4,
    _s_FuncInfo* param_5,
    int param_6,
    int param_7,
    EHRegistrationNode* param_8)
{
    if (*reinterpret_cast<int*>(param_1) != -0x7ffffffd)
    {
        _tiddata* p_Var2 = __getptd();

        if (p_Var2->_translator != nullptr)
        {
            p_Var2 = __getptd();
            void* pvVar3 = FUN_10014c40();

            if ((p_Var2->_translator != pvVar3) &&
                (*reinterpret_cast<int*>(param_1) != -0x1fbcb0b3) &&
                (*reinterpret_cast<int*>(param_1) != -0x1fbcbcae) &&
                (_CallSETranslator(
                     param_1,
                     param_2,
                     param_3,
                     param_4,
                     param_5,
                     param_7,
                     param_8) != 0))
            {
                return;
            }
        }

        if (param_5->nTryBlocks == 0)
        {
            _inconsistency();
        }

        std::uint32_t local_8;
        std::uint32_t in_stack_fffffff0;

        _s_TryBlockMapEntry* p_Var5 =
            _GetRangeOfTrysToCheck(
                param_5,
                param_7,
                param_6,
                &local_8,
                &in_stack_fffffff0);

        if (local_8 < in_stack_fffffff0)
        {
            std::uint8_t* current =
                reinterpret_cast<std::uint8_t*>(p_Var5);

            do
            {
                _s_TryBlockMapEntry* entry =
                    reinterpret_cast<_s_TryBlockMapEntry*>(current);

                if ((entry->tryLow <= param_6) &&
                    (param_6 <= entry->tryHigh))
                {
                    _s_HandlerType* handler =
                        &entry->pHandlerArray[entry->nCatches - 1];

                    TypeDescriptor* pTVar1 = handler->pType;

                    if (((pTVar1 == nullptr) ||
                         (*reinterpret_cast<const unsigned char*>(
                              &pTVar1[1].pVFTable) == 0)) &&
                        ((handler->adjectives & 0x40U) == 0))
                    {
                        _s_HandlerType* handler_reg = handler;
                    EHRegistrationNode* node_reg = param_2;
                    _s_TryBlockMapEntry* try_reg = entry;
                    __asm {
                        mov ebx, handler_reg
                        mov esi, node_reg
                        mov edi, try_reg
                        push param_8
                        push param_7
                        push 0
                        push param_5
                        push param_4
                        push param_3
                        push param_1
                        call CatchIt
                        add esp, 1Ch
                    }
                    }
                }

                local_8 = local_8 + 1;
                current = current + 20;
            }
            while (local_8 < in_stack_fffffff0);
        }
    }
}