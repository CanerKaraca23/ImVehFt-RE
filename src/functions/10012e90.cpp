#include <cstddef>
#include <cstdint>

using PVOID = void*;
using PBYTE = std::uint8_t*;
using BOOL = int;

struct EXCEPTION_RECORD
{
    std::uint32_t ExceptionCode;
    std::uint32_t ExceptionFlags;
};

using PEXCEPTION_RECORD = EXCEPTION_RECORD*;

struct EH4LocalState
{
    PEXCEPTION_RECORD exception_record;
    std::uint32_t exception_context;
};

struct EH4ExceptionFrame
{
    EH4LocalState* saved_exception_state; // param_2 - 0x04
    std::uint32_t reserved_00;            // param_2 + 0x00
    std::uint32_t reserved_04;            // param_2 + 0x04
    std::uint32_t scope_cookie;           // param_2 + 0x08
    PVOID try_level;                      // param_2 + 0x0c
    std::uint32_t unwind_target;          // param_2 + 0x10
};

static_assert(offsetof(EH4ExceptionFrame, saved_exception_state) == 0x00);
static_assert(offsetof(EH4ExceptionFrame, scope_cookie) == 0x0c);
static_assert(offsetof(EH4ExceptionFrame, try_level) == 0x10);
static_assert(offsetof(EH4ExceptionFrame, unwind_target) == 0x14);

extern "C" std::uint32_t DAT_10029490;

extern "C" void (*PTR____DestructExceptionObject)(
    PEXCEPTION_RECORD,
    int,
    std::uint32_t);

extern "C" void __fastcall __security_check_cookie(std::uintptr_t);
extern "C" int __fastcall _EH4_CallFilterFunc(void*);
extern "C" BOOL __cdecl __IsNonwritableInCurrentImage(PBYTE);
extern "C" void __fastcall _EH4_GlobalUnwind2(
    PVOID,
    PEXCEPTION_RECORD);
extern "C" void __fastcall _EH4_LocalUnwind(
    int,
    std::uint32_t,
    int,
    std::uint32_t*);
extern "C" void __fastcall _EH4_TransferToHandler(void*);

extern "C" std::uint32_t __cdecl __except_handler4(
    PEXCEPTION_RECORD param_1,
    PVOID param_2,
    std::uint32_t param_3)
{
    auto* frame = reinterpret_cast<EH4ExceptionFrame*>(
        reinterpret_cast<std::uintptr_t>(param_2) - 0x04u);

    const std::uint32_t encoded_cookie =
        frame->scope_cookie ^ DAT_10029490;

    EH4LocalState local_state{};
    std::uint8_t local_cookie = 0;
    std::uint32_t return_value = 1;
    const std::uint32_t handler_address = 0x10012ed9u;

    PVOID matched_scope_level = param_2;

    if ((param_1->ExceptionFlags & 0x66u) == 0)
    {
        frame->saved_exception_state = &local_state;

        PVOID next_scope_level = frame->try_level;

        local_state.exception_record = param_1;
        local_state.exception_context = param_3;

        std::uint32_t* scope_record = nullptr;

        for (;;)
        {
            void* filter = nullptr;

            do
            {
                matched_scope_level = next_scope_level;

                if (matched_scope_level ==
                    reinterpret_cast<PVOID>(
                        static_cast<std::uintptr_t>(0xfffffffeu)))
                {
                    __security_check_cookie(encoded_cookie);
                    return return_value;
                }

                const auto scope_level =
                    static_cast<std::int32_t>(
                        reinterpret_cast<std::intptr_t>(
                            matched_scope_level));

                scope_record =
                    reinterpret_cast<std::uint32_t*>(
                        static_cast<std::uintptr_t>(encoded_cookie) +
                        static_cast<std::intptr_t>(
                            (scope_level * 3 + 4) * 4));

                filter = reinterpret_cast<void*>(
                    static_cast<std::uintptr_t>(scope_record[1]));

                next_scope_level = reinterpret_cast<PVOID>(
                    static_cast<std::uintptr_t>(scope_record[0]));
            }
            while (filter == nullptr);

            const int filter_result =
                _EH4_CallFilterFunc(filter);

            local_cookie = 1;

            if (filter_result < 0)
            {
                __security_check_cookie(encoded_cookie);
                return 0;
            }

            if (filter_result >= 1)
                break;
        }

        if ((param_1->ExceptionCode == 0xe06d7363u) &&
            (PTR____DestructExceptionObject != nullptr) &&
            (__IsNonwritableInCurrentImage(
                 reinterpret_cast<PBYTE>(
                     &PTR____DestructExceptionObject)) != 0))
        {
            PTR____DestructExceptionObject(
                param_1,
                1,
                handler_address);
        }

        _EH4_GlobalUnwind2(param_2, param_1);

        if (frame->try_level != matched_scope_level)
        {
            _EH4_LocalUnwind(
                static_cast<int>(
                    reinterpret_cast<std::uintptr_t>(param_2)),
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(
                        matched_scope_level)),
                static_cast<int>(
                    reinterpret_cast<std::uintptr_t>(param_2) + 0x10u),
                &DAT_10029490);
        }

        frame->try_level = next_scope_level;

        _EH4_TransferToHandler(
            reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    scope_record[2])));
    }

    if (*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uintptr_t>(
                matched_scope_level) + 0x0cu) != -2)
    {
        _EH4_LocalUnwind(
            static_cast<int>(
                reinterpret_cast<std::uintptr_t>(
                    matched_scope_level)),
            0xfffffffeu,
            static_cast<int>(
                reinterpret_cast<std::uintptr_t>(param_2) + 0x10u),
            &DAT_10029490);
    }

    __security_check_cookie(encoded_cookie);
    return return_value;
}