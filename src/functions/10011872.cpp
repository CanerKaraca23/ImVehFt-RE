#include <cstdint>

extern std::uint32_t DAT_10039a04;

extern "C" void* __stdcall DecodePointer(void* pointer);

extern "C" [[noreturn]] void __cdecl __invoke_watson(
    wchar_t* param_1,
    wchar_t* param_2,
    wchar_t* param_3,
    std::uint32_t param_4,
    std::uintptr_t param_5);

extern "C" void __stdcall FUN_10011872(
    wchar_t* param_1,
    wchar_t* param_2,
    wchar_t* param_3,
    std::uint32_t param_4,
    std::uintptr_t param_5)
{
    using UnrecoveredJumpTable = void (*)();

    const auto unrecovered_jumptable =
        reinterpret_cast<UnrecoveredJumpTable>(
            DecodePointer(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(DAT_10039a04))));

    if (unrecovered_jumptable != nullptr)
    {
        unrecovered_jumptable();
        return;
    }

    __invoke_watson(param_1, param_2, param_3, param_4, param_5);
}