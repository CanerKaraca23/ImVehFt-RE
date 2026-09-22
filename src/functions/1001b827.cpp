#include <cstdint>

struct EHExceptionRecord
{
    std::uint8_t reserved_00[4];
    std::uint32_t field_04;
};

struct EHRegistrationNode;
struct _s_FuncInfo;

struct TranslatorGuardRN
{
    std::uint8_t reserved_00[0x0C];
    _s_FuncInfo* field_0C;
    EHRegistrationNode* field_10;
    int field_14;
    EHRegistrationNode* field_18;
    std::uint8_t reserved_1C[8];
    int field_24;
};

enum _EXCEPTION_DISPOSITION : int;

extern "C" void __cdecl ___InternalCxxFrameHandler(
    EHExceptionRecord*, EHRegistrationNode*, void*, void*,
    _s_FuncInfo*, int, EHRegistrationNode*, unsigned char);

extern "C" void __stdcall _UnwindNestedFrames(
    EHRegistrationNode*, EHExceptionRecord*);

extern "C" int __cdecl _CallSETranslator(
    EHExceptionRecord*, EHRegistrationNode*, void*, void*,
    _s_FuncInfo*, int, EHRegistrationNode*);

using TranslatorCallback = _EXCEPTION_DISPOSITION(__cdecl*)();

_EXCEPTION_DISPOSITION __cdecl TranslatorGuardHandler(
    EHExceptionRecord* param_1,
    TranslatorGuardRN* param_2,
    void* param_3,
    void* param_4)
{
    (void)param_4;

    if ((param_1->field_04 & 0x66u) != 0)
    {
        param_2->field_24 = 1;

        // __security_check_cookie is compiler-injected at the function epilogue.
        return static_cast<_EXCEPTION_DISPOSITION>(1);
    }

    ___InternalCxxFrameHandler(
        param_1,
        param_2->field_10,
        param_3,
        nullptr,
        param_2->field_0C,
        param_2->field_14,
        param_2->field_18,
        1);

    if (param_2->field_24 == 0)
    {
        _UnwindNestedFrames(
            reinterpret_cast<EHRegistrationNode*>(param_2),
            param_1);
    }

    TranslatorCallback local_8;

    _CallSETranslator(
        reinterpret_cast<EHExceptionRecord*>(0x123),
        reinterpret_cast<EHRegistrationNode*>(&local_8),
        nullptr,
        nullptr,
        nullptr,
        0,
        nullptr);

    // __security_check_cookie is compiler-injected at the function epilogue.
    return local_8();
}