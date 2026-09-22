#include <cstdint>

extern "C" int __cdecl _isdigit(unsigned int value);

extern "C" unsigned int __cdecl __hextodec(std::uint8_t param_1)
{
    const int is_digit = _isdigit(static_cast<unsigned int>(param_1));
    unsigned int value =
        static_cast<unsigned int>(static_cast<char>(param_1));

    if (is_digit == 0)
    {
        value = (value & 0xffffffdfu) - 7u;
    }

    return value;
}