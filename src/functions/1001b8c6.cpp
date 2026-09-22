#include <cstddef>
struct _s_TryBlockMapEntry { int tryLow; int tryHigh; int catchHigh; int nCatches; void* pHandlerArray; };
struct _s_FuncInfo { unsigned int magicNumber; int maxState; void* pUnwindMap; unsigned int nTryBlocks; _s_TryBlockMapEntry* pTryBlockMap; };
static_assert(sizeof(_s_TryBlockMapEntry) == 0x14);
static_assert(offsetof(_s_TryBlockMapEntry, tryHigh) == 0x04);
static_assert(offsetof(_s_TryBlockMapEntry, catchHigh) == 0x08);
static_assert(offsetof(_s_FuncInfo, nTryBlocks) == 0x0c);
static_assert(offsetof(_s_FuncInfo, pTryBlockMap) == 0x10);
extern "C" void __cdecl _inconsistency(void);
_s_TryBlockMapEntry* __cdecl
_GetRangeOfTrysToCheck(
    _s_FuncInfo* param_1,
    int param_2,
    int param_3,
    unsigned int* param_4,
    unsigned int* param_5)
{
    _s_TryBlockMapEntry* pTVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;
    unsigned int uVar5;
    pTVar1 = param_1->pTryBlockMap;
    uVar5 = param_1->nTryBlocks;
    uVar2 = uVar5;
    uVar3 = uVar5;
    while (uVar4 = uVar2, -1 < param_2) {
        if (uVar5 == 0xffffffffu) _inconsistency();
        uVar5 = uVar5 - 1;
        if (((pTVar1[uVar5].tryHigh < param_3) && (param_3 <= pTVar1[uVar5].catchHigh)) || (uVar2 = uVar4, uVar5 == 0xffffffffu)) {
            param_2 = param_2 + -1;
            uVar2 = uVar5;
            uVar3 = uVar4;
        }
    }
    uVar5 = uVar5 + 1;
    *param_4 = uVar5;
    *param_5 = uVar3;
    if ((param_1->nTryBlocks < uVar3) || (uVar3 < uVar5)) _inconsistency();
    return pTVar1 + uVar5;
}