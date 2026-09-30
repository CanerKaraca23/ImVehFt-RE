#include <cstdint>

extern "C" void __cdecl gs_consume_buffer(unsigned char* buffer);

extern "C" __declspec(noinline) void __cdecl gs_guarded_probe()
{
    volatile unsigned char localBuffer[64] = {};
    localBuffer[0] = 0x5a;
    gs_consume_buffer(const_cast<unsigned char*>(localBuffer));
}
