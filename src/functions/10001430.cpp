#include <cstddef>
#include <cstdint>

extern "C" void* __cdecl FUN_10010893(std::size_t size);

struct ExceptionAbi
{
    void construct(const void* source);
};

extern "C" [[noreturn]] void __stdcall __CxxThrowException_8(
    void* exception_object,
    const void* throw_info);

extern void** std_bad_alloc_vftable;
extern std::uint8_t DAT_10028608;

extern "C" void* __stdcall FUN_10001430(
    char* param_1,
    std::uint32_t param_2)
{
    std::uint32_t* context;
    __asm mov context, esi

    auto* puVar1 =
        static_cast<std::uint32_t*>(FUN_10010893(0x14));

    if (puVar1 != nullptr)
    {
        puVar1[0] = reinterpret_cast<std::uint32_t>(param_1);
        puVar1[1] = param_2;

        if (puVar1 + 2 != nullptr)
        {
            puVar1[2] = context[0];
            puVar1[3] = context[1];
            puVar1[4] = context[2];
        }

        return puVar1;
    }

    void* local_10[3];
    param_1 = nullptr;

    reinterpret_cast<ExceptionAbi*>(local_10)->construct(&param_1);
    local_10[0] = std_bad_alloc_vftable;

    __CxxThrowException_8(local_10, &DAT_10028608);
}