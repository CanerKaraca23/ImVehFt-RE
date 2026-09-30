#include "imvehft_image_aliases.hpp"
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

struct EH4ScopeTableHeader
{
    // Ghidra's 10012e90 assembly decodes these four offsets before walking
    // the three-DWORD scope records that start at +0x10.
    std::uint32_t gs_cookie_offset;
    std::uint32_t gs_cookie_xor_offset;
    std::uint32_t eh_cookie_offset;
    std::uint32_t eh_cookie_xor_offset;
};

static_assert(offsetof(EH4ExceptionFrame, saved_exception_state) == 0x00);
static_assert(offsetof(EH4ExceptionFrame, scope_cookie) == 0x0c);
static_assert(offsetof(EH4ExceptionFrame, try_level) == 0x10);
static_assert(offsetof(EH4ExceptionFrame, unwind_target) == 0x14);
static_assert(sizeof(EH4ScopeTableHeader) == 0x10);

extern "C" std::uint32_t DAT_10029490;

extern "C" void __fastcall __security_check_cookie(std::uintptr_t);
extern "C" int __fastcall _EH4_CallFilterFunc(void*, void*);
extern "C" BOOL __cdecl __IsNonwritableInCurrentImage(PBYTE);
extern "C" void __fastcall _EH4_GlobalUnwind2(
    PVOID,
    PEXCEPTION_RECORD);
extern "C" void __fastcall _EH4_LocalUnwind(
    int,
    std::uint32_t,
    int,
    std::uint32_t*);
extern "C" void __fastcall _EH4_TransferToHandler(void*, void*);

#define IVF_CHECK_EH4_FRAME_COOKIES(scope_table_address, frame_address) do { \
    const auto* const _scope_table = reinterpret_cast<const EH4ScopeTableHeader*>(scope_table_address); \
    const std::uintptr_t _frame = static_cast<std::uintptr_t>(frame_address); \
    if (_scope_table->gs_cookie_offset != 0xfffffffeu) { \
        /* Mirrors Ghidra: (frame + GS_XOR_offset) ^ *(frame + GS_offset). */ \
        const auto _gs_cookie = *reinterpret_cast<const std::uint32_t*>( \
            _frame + _scope_table->gs_cookie_offset); \
        const auto _gs_cookie_xor = static_cast<std::uint32_t>( \
            _frame + _scope_table->gs_cookie_xor_offset); \
        __security_check_cookie(_gs_cookie ^ _gs_cookie_xor); \
    } \
    /* EH cookie is always checked, even when the GS-cookie offset is -2. */ \
    const auto _eh_cookie = *reinterpret_cast<const std::uint32_t*>( \
        _frame + _scope_table->eh_cookie_offset); \
    const auto _eh_cookie_xor = static_cast<std::uint32_t>( \
        _frame + _scope_table->eh_cookie_xor_offset); \
    __security_check_cookie(_eh_cookie ^ _eh_cookie_xor); \
} while (0)

extern "C" std::uint32_t __cdecl __except_handler4(
    PEXCEPTION_RECORD param_1,
    PVOID param_2,
    std::uint32_t param_3)
{
    auto* frame = reinterpret_cast<EH4ExceptionFrame*>(
        reinterpret_cast<std::uintptr_t>(param_2) - 0x04u);

    const std::uint32_t encoded_cookie =
        frame->scope_cookie ^ DAT_10029490;

    const auto eh_frame_address =
        reinterpret_cast<std::uintptr_t>(param_2) + 0x10u;
    IVF_CHECK_EH4_FRAME_COOKIES(encoded_cookie, eh_frame_address);

    EH4LocalState local_state{};
    std::uint8_t local_cookie = 0;
    std::uint32_t return_value = 1;
    PVOID matched_scope_level = param_2;
    BOOL run_post_transfer_unwind =
        (param_1->ExceptionFlags & 0x66u) != 0;

    if (!run_post_transfer_unwind)
    {
        frame->saved_exception_state = &local_state;

        PVOID next_scope_level = frame->try_level;

        local_state.exception_record = param_1;
        local_state.exception_context = param_3;

        std::uint32_t* scope_record = nullptr;
        BOOL stop_search = 0;
        BOOL transfer_to_handler = 0;

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
                    stop_search = 1;
                    break;
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

            if (stop_search)
                break;

            const int filter_result = _EH4_CallFilterFunc(
                filter,
                reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(param_2) + 0x10u));

            local_cookie = 1;

            if (filter_result < 0)
            {
                return_value = 0;
                break;
            }

            if (filter_result >= 1)
            {
                transfer_to_handler = 1;
                break;
            }
        }

        if (transfer_to_handler)
        {
            auto* const destructor_slot =
                reinterpret_cast<void (**)(PEXCEPTION_RECORD, int)>(
                    IVF_IMAGE_ADDRESS_100261E0);
            if ((param_1->ExceptionCode == 0xe06d7363u) &&
                (*destructor_slot != nullptr) &&
                (__IsNonwritableInCurrentImage(
                     reinterpret_cast<PBYTE>(destructor_slot)) != 0))
            {
                (*destructor_slot)(
                    param_1,
                    1);
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
            IVF_CHECK_EH4_FRAME_COOKIES(encoded_cookie, eh_frame_address);

            _EH4_TransferToHandler(
                reinterpret_cast<void*>(
                    static_cast<std::uintptr_t>(
                        scope_record[2])),
                reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(param_2) + 0x10u));
            run_post_transfer_unwind = 1;
        }
    }

    if (run_post_transfer_unwind &&
        frame->try_level !=
            reinterpret_cast<PVOID>(
                static_cast<std::uintptr_t>(0xfffffffeu)))
    {
        _EH4_LocalUnwind(
            static_cast<int>(reinterpret_cast<std::uintptr_t>(param_2)),
            0xfffffffeu,
            static_cast<int>(
                reinterpret_cast<std::uintptr_t>(param_2) + 0x10u),
            &DAT_10029490);
    }

    if (local_cookie != 0)
        IVF_CHECK_EH4_FRAME_COOKIES(encoded_cookie, eh_frame_address);

    return return_value;
}

#undef IVF_CHECK_EH4_FRAME_COOKIES
