#include <cstdint>

extern "C" void __cdecl FUN_10010756(void*);
extern "C" void __stdcall FUN_1001074b(void*);

extern "C" void __cdecl FUN_10008dd0(std::uint32_t param_1, int param_2)
{
    struct Context
    {
        std::uint8_t reserved_00[0x28];
        void* member_28;
        std::uint8_t reserved_2c[4];
        void* member_30;
    };

    (void)param_1;

    auto* context = reinterpret_cast<Context*>(
        static_cast<std::uintptr_t>(
            static_cast<std::uint32_t>(param_2)));

    FUN_10010756(context->member_28);

    if (context->member_30 != nullptr)
    {
        FUN_1001074b(context->member_30);
    }
}