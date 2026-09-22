#include <cstddef>
#include <cstdint>
#include <exception>

struct EHRegistrationNode;
struct EHExceptionRecord;
struct _CONTEXT;
struct _s_ESTypeList;
struct _s_CatchableType;
struct _s_HandlerType;
struct _s_TryBlockMapEntry;

// x86 MSVC 2010 EH metadata layouts cross-checked against Ghidra operands
// and the adjacent 1001d48a / 1001b8c6 candidate declarations.
struct _s_FuncInfo
{
    std::uint32_t magicNumber_and_bbtFlags;  // +0x00
    std::int32_t maxState;                   // +0x04
    void* pUnwindMap;                        // +0x08
    std::uint32_t nTryBlocks;                // +0x0c
    _s_TryBlockMapEntry* pTryBlockMap;       // +0x10
    std::uint32_t nIPMapEntries;             // +0x14
    void* pIPtoStateMap;                     // +0x18
    _s_ESTypeList* pESTypeList;              // +0x1c
};
static_assert(offsetof(_s_FuncInfo, maxState) == 0x04);
static_assert(offsetof(_s_FuncInfo, nTryBlocks) == 0x0c);
static_assert(offsetof(_s_FuncInfo, pTryBlockMap) == 0x10);
static_assert(sizeof(_s_FuncInfo) == 0x20);

struct TypeDescriptor { void* pVFTable; void* spare; };
struct _s_HandlerType
{
    std::uint32_t adjectives;
    TypeDescriptor* pType;
    std::int32_t dispCatchObj;
    void* addressOfHandler;
};
struct _s_ESTypeList { std::uint32_t nCount; _s_HandlerType* pTypeArray; };
static_assert(sizeof(_s_ESTypeList) == 0x08);
static_assert(offsetof(_s_ESTypeList, pTypeArray) == 0x04);
struct _s_TryBlockMapEntry
{
    std::int32_t tryLow;
    std::int32_t tryHigh;
    std::int32_t catchHigh;
    std::int32_t nCatches;
    _s_HandlerType* pHandlerArray;
};
static_assert(sizeof(_s_HandlerType) == 0x10);
static_assert(sizeof(_s_TryBlockMapEntry) == 0x14);

// Ghidra reads __getptd()+0x88 and +0x8c for these CRT state fields.
struct _ptiddata
{
    std::uint8_t reserved_00_87[0x88];
    EHExceptionRecord* _curexception;
    _CONTEXT* _curcontext;
    std::uint32_t reserved_90;
    void* _curexcspec;
};
static_assert(offsetof(_ptiddata, _curexception) == 0x88);
static_assert(offsetof(_ptiddata, _curcontext) == 0x8c);
static_assert(offsetof(_ptiddata, _curexcspec) == 0x94);

// Recovered from x86 Ghidra memory operands in FindHandler.
struct EHExceptionRecord
{
    std::uint32_t magicNumber_and_bbtFlags; // +0x00
    std::uint32_t exceptionFlags;           // +0x04
    void* nestedRecord;                     // +0x08
    void* exceptionAddress;                 // +0x0c
    std::uint32_t pTryBlockMap;              // +0x10
    std::uint32_t nIPMapEntries;             // +0x14
    std::uint32_t unknown18;                 // +0x18
    _s_ESTypeList* pESTypeList;             // +0x1c
};
static_assert(offsetof(EHExceptionRecord, pTryBlockMap) == 0x10);
static_assert(offsetof(EHExceptionRecord, nIPMapEntries) == 0x14);
static_assert(offsetof(EHExceptionRecord, unknown18) == 0x18);
static_assert(offsetof(EHExceptionRecord, pESTypeList) == 0x1c);
static_assert(sizeof(EHExceptionRecord) == 0x20);

struct _tiddata { std::uint8_t reserved_00_7f[0x80]; void* _translator; };
extern "C" _ptiddata* __cdecl __getptd(void);
extern "C" void __cdecl _inconsistency(void);
extern "C" int __cdecl _ValidateRead(void*, std::uint32_t);
extern "C" int __cdecl IsInExceptionSpec(EHExceptionRecord*, _s_ESTypeList*);
extern "C" int __cdecl FUN_10010792(void*, void*);
extern "C" void __cdecl ___DestructExceptionObject(int*);
extern "C" void __cdecl FUN_100102c3();
static __declspec(naked) void __cdecl CallExceptionCtorAbi(std::exception*, char**)
{
    __asm {
        push ebp
        mov ebp, esp
        mov ecx, dword ptr [ebp + 08h]
        push dword ptr [ebp + 0ch]
        call FUN_100102c3
        add esp, 4
        mov esp, ebp
        pop ebp
        ret
    }
}
extern "C" __declspec(noreturn) void __stdcall __CxxThrowException_8(void*, void*);
extern "C" _s_TryBlockMapEntry* __cdecl _GetRangeOfTrysToCheck(
    _s_FuncInfo*, int, int, std::uint32_t*, std::uint32_t*);
extern "C" int __cdecl ___TypeMatch(std::uint8_t*, std::uint8_t*, std::uint32_t*);
extern "C" void __stdcall _UnwindNestedFrames(EHRegistrationNode*, EHExceptionRecord*);
extern "C" void __cdecl ___FrameUnwindToState(int, void*, int, int);
extern "C" void __stdcall FUN_1001d026(void);
extern "C" void __cdecl FindHandlerForForeignException(
    EHExceptionRecord*, EHRegistrationNode*, _CONTEXT*, void*, _s_FuncInfo*,
    int, int, EHRegistrationNode*);

extern "C" __declspec(noreturn) void __cdecl terminate(void) noexcept;
extern EHExceptionRecord s_bad_exception_100261f0;

// Ghidra confirms seven stack arguments and register arguments in EDI/ESI/EBX.
// ECX is forwarded but not consumed by CatchIt's x86 body.
extern "C" void __cdecl CatchIt();
static __declspec(naked) void __cdecl CallCatchItRegisterAbi(
    EHExceptionRecord*, EHRegistrationNode*, _CONTEXT*, void*, _s_FuncInfo*,
    _s_HandlerType*, _s_CatchableType*, _s_TryBlockMapEntry*,
    EHRegistrationNode*, _s_HandlerType*)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        mov edi, dword ptr [ebp + 24h]
        mov esi, dword ptr [ebp + 28h]
        mov ebx, dword ptr [ebp + 2ch]
        mov ecx, dword ptr [ebp + 30h]
        push dword ptr [ebp + 20h]
        push dword ptr [ebp + 1ch]
        push dword ptr [ebp + 18h]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0ch]
        push dword ptr [ebp + 08h]
        call CatchIt
        add esp, 1ch
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}



void __cdecl FindHandler(
    EHExceptionRecord* param_1,
    EHRegistrationNode* param_2,
    _CONTEXT* param_3,
    void* param_4,
    _s_FuncInfo* param_5,
    std::uint8_t param_6,
    int param_7,
    EHRegistrationNode* param_8)
{
    std::uint8_t handlerFound = 0;
    _s_FuncInfo* pVar11 = param_5;
    EHExceptionRecord* pVar12 = param_1;

    int currentState;

    if (param_5->maxState < 0x81)
    {
        currentState = static_cast<int>(
            static_cast<std::int8_t>(
                reinterpret_cast<std::uint8_t*>(param_2)[8]));
    }
    else
    {
        currentState = *reinterpret_cast<int*>(
            reinterpret_cast<std::uint8_t*>(param_2) + 8);
    }

    if (currentState < -1 || param_5->maxState <= currentState)
    {
        _inconsistency();
    }

    if (param_1->magicNumber_and_bbtFlags == 0xe06d7363)
    {
        if (param_1->pTryBlockMap == 3 &&
            (param_1->nIPMapEntries == 0x19930520 ||
             param_1->nIPMapEntries == 0x19930521 ||
             param_1->nIPMapEntries == 0x19930522) &&
            param_1->unknown18 == 0)
        {
            _ptiddata* ptd = __getptd();

            if (ptd->_curexception == nullptr)
            {
                return;
            }

            ptd = __getptd();
            pVar12 = static_cast<EHExceptionRecord*>(ptd->_curexception);
            param_1 = pVar12;

            ptd = __getptd();
            param_3 = ptd->_curcontext;

            if (_ValidateRead(pVar12, 1) == 0)
            {
                _inconsistency();
            }

            if (pVar12->magicNumber_and_bbtFlags == 0xe06d7363 &&
                pVar12->pTryBlockMap == 3 &&
                (pVar12->nIPMapEntries == 0x19930520 ||
                 pVar12->nIPMapEntries == 0x19930521 ||
                 pVar12->nIPMapEntries == 0x19930522) &&
                pVar12->pESTypeList == nullptr)
            {
                _inconsistency();
            }

            ptd = __getptd();

            if (ptd->_curexcspec != nullptr)
            {
                ptd = __getptd();
                int* exceptionSpec =
                    static_cast<int*>(ptd->_curexcspec);

                ptd = __getptd();
                ptd->_curexcspec = nullptr;

                if (IsInExceptionSpec(
                        param_1,
                        reinterpret_cast<_s_ESTypeList*>(exceptionSpec)) == 0)
                {
                    int index = 0;

                    if (0 < *exceptionSpec)
                    {
                        do
                        {
                            type_info* type =
                                *reinterpret_cast<type_info**>(
                                    reinterpret_cast<std::uint8_t*>(
                                        static_cast<std::uintptr_t>(
                                            exceptionSpec[1])) +
                                    4 + index * 0x10);

                            if (FUN_10010792(
                                    type,
                                    &s_bad_exception_100261f0))
                            {
                                ___DestructExceptionObject(
                                    reinterpret_cast<int*>(param_1));

                                alignas(std::exception)
                                    std::uint8_t exceptionStorage[
                                        sizeof(std::exception)];

                                std::exception* exceptionObject =
                                    reinterpret_cast<std::exception*>(
                                        exceptionStorage);

                                param_1 =
                                    reinterpret_cast<EHExceptionRecord*>(
                                        &s_bad_exception_100261f0);

                                CallExceptionCtorAbi(
                                    exceptionObject,
                                    reinterpret_cast<char**>(&param_1));

                                __CxxThrowException_8(
                                    exceptionObject,
                                    reinterpret_cast<void*>(
                                        0x1002874c));
                            }

                            ++index;
                        }
                        while (index < *exceptionSpec);
                    }

                    terminate();
                }
            }
        }

        pVar11 = param_5;

        if (pVar12->magicNumber_and_bbtFlags == 0xe06d7363 &&
            pVar12->pTryBlockMap == 3 &&
            (pVar12->nIPMapEntries == 0x19930520 ||
             pVar12->nIPMapEntries == 0x19930521 ||
             pVar12->nIPMapEntries == 0x19930522))
        {
            if (param_5->nTryBlocks != 0)
            {
                std::uint32_t firstTry;
                std::uint32_t lastTry;

                _s_TryBlockMapEntry* tryBlock =
                    _GetRangeOfTrysToCheck(
                        param_5,
                        param_7,
                        currentState,
                        &firstTry,
                        &lastTry);

                if (firstTry < lastTry)
                {
                    _s_TryBlockMapEntry* tryEntry = tryBlock;

                    do
                    {
                        if (tryEntry->tryLow <= currentState &&
                            currentState <= tryEntry->tryHigh)
                        {
                            _s_HandlerType* handler =
                                tryEntry->pHandlerArray;

                            for (int handlerCount = tryEntry->nCatches;
                                 0 < handlerCount;
                                 --handlerCount)
                            {
                                _s_HandlerType* typeEntry =
                                    pVar12->pESTypeList[1].pTypeArray;

                                for (std::uint32_t typeCount =
                                         typeEntry->adjectives;
                                     0 < static_cast<int>(typeCount);
                                     --typeCount)
                                {
                                    typeEntry =
                                        reinterpret_cast<_s_HandlerType*>(
                                            &typeEntry->pType);

                                    _s_FuncInfo* matchedType =
                                        reinterpret_cast<_s_FuncInfo*>(
                                            typeEntry->pType);

                                    if (___TypeMatch(
                                            reinterpret_cast<std::uint8_t*>(
                                                handler),
                                            reinterpret_cast<std::uint8_t*>(
                                                matchedType),
                                            reinterpret_cast<std::uint32_t*>(
                                                pVar12->pESTypeList)) != 0)
                                    {
                                        handlerFound = 1;

                                        CallCatchItRegisterAbi(
                                            pVar12,
                                            reinterpret_cast<
                                                EHRegistrationNode*>(
                                                param_3),
                                            reinterpret_cast<_CONTEXT*>(param_4),
                                            param_5,
                                            matchedType,
                                            reinterpret_cast<
                                                _s_HandlerType*>(
                                                static_cast<std::uintptr_t>(
                                                    param_7)),
                                            reinterpret_cast<
                                                _s_CatchableType*>(
                                                reinterpret_cast<std::uintptr_t>(param_8)),
                                            tryEntry,
                                            param_2,
                                            handler);

                                        pVar12 = param_1;
                                        goto TryBlockComplete;
                                    }
                                }

                                handler += 1;
                            }
                        }

                    TryBlockComplete:
                        ++firstTry;
                        tryEntry += 1;
                    }
                    while (firstTry < lastTry);
                }
            }

            if (param_6 != 0)
            {
                ___DestructExceptionObject(
                    reinterpret_cast<int*>(pVar12));
            }

            pVar11 = param_5;

            if (handlerFound != 0 ||
                ((pVar11->magicNumber_and_bbtFlags & 0x1fffffffU) <
                 0x19930521) ||
                pVar11->pESTypeList == nullptr ||
                IsInExceptionSpec(
                    pVar12,
                    reinterpret_cast<_s_ESTypeList*>(pVar11->pESTypeList)) != 0)
            {
                goto ExceptionSpecChecked;
            }

            __getptd();
            __getptd();

            _ptiddata* ptd = __getptd();
            ptd->_curexception = pVar12;

            ptd = __getptd();
            ptd->_curcontext = param_3;

            EHRegistrationNode* unwindNode = param_8;

            if (unwindNode == nullptr)
            {
                unwindNode = param_2;
            }

            _UnwindNestedFrames(unwindNode, pVar12);

            pVar12 = reinterpret_cast<EHExceptionRecord*>(param_5);

            ___FrameUnwindToState(
                static_cast<std::int32_t>(
                    reinterpret_cast<std::uintptr_t>(param_2)),
                param_4,
                static_cast<std::int32_t>(
                    reinterpret_cast<std::uintptr_t>(param_5)),
                -1);

            FUN_1001d026();
            pVar11 = param_5;
        }
    }

    if (pVar11->nTryBlocks != 0)
    {
        if (param_6 != 0)
        {
            terminate();
        }

        FindHandlerForForeignException(
            pVar12,
            param_2,
            param_3,
            param_4,
            pVar11,
            currentState,
            param_7,
            param_8);
    }

ExceptionSpecChecked:
    if (__getptd()->_curexcspec != nullptr)
    {
        _inconsistency();
    }
}