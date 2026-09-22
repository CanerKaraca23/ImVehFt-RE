#include <cstddef>
#include <cstdint>

extern "C" std::size_t __cdecl _strlen(const char*);
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

std::uint32_t __cdecl vscan_fn(
    void* param_1,
    int param_2,
    std::uint32_t param_3,
    std::uint32_t param_4
)
{
    char* unaff_ESI;
    __asm mov unaff_ESI, esi
    std::uint32_t local_stack[7]{};
    std::uint32_t& local_20 = local_stack[0];
    std::uint32_t& local_18 = local_stack[2];

    if (unaff_ESI != nullptr && param_2 != 0)
    {
        const std::size_t sVar2 = _strlen(unaff_ESI);

        local_18 = 0x49;
        local_20 = 0x7FFFFFFF;

        if (sVar2 < 0x80000000ULL)
        {
            local_20 = static_cast<std::uint32_t>(sVar2);
        }

        using Callback = std::uint32_t(__cdecl*)(
            void*,
            int,
            std::uint32_t,
            std::uint32_t
        );

        return reinterpret_cast<Callback>(param_1)(
            reinterpret_cast<std::uint8_t*>(&local_20) - 4,
            param_2,
            param_3,
            param_4
        );
    }

    *(__errno()) = 0x16;
    FUN_1001189f();
    return 0xFFFFFFFFU;
}