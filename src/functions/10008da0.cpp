#include <cstddef>
#include <cstdint>

extern "C" std::uint32_t __cdecl FUN_10010893(std::size_t size);

extern "C" void __cdecl FUN_10008da0(
    std::uint32_t param_1,
    std::uint32_t* param_2
)
{
    param_2[0] = param_1;
    param_2[10] = FUN_10010893(0x518);
    *reinterpret_cast<std::uint8_t*>(param_2 + 0x0B) = 0;
    param_2[0x0C] = 0;
}