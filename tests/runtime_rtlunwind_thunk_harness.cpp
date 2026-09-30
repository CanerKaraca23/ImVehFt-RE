#include <cstddef>
#include <cstdint>

using RtlUnwindFunction = void(__stdcall*)(void*, void*, void*, void*);

extern "C" void __stdcall ImVehFt_Recovered_RtlUnwind(
    void* target_frame,
    void* target_ip,
    void* exception_record,
    void* return_value);

namespace
{
std::uint32_t call_count = 0;
void* captured_arguments[4]{};

void __stdcall test_rtlunwind_target(
    void* target_frame,
    void* target_ip,
    void* exception_record,
    void* return_value)
{
    ++call_count;
    captured_arguments[0] = target_frame;
    captured_arguments[1] = target_ip;
    captured_arguments[2] = exception_record;
    captured_arguments[3] = return_value;
}
}

// The candidate naked thunk dereferences this cell, just like the original
// image's IAT slot. The test points it at a harmless stdcall recorder.
extern "C" RtlUnwindFunction _imp__RtlUnwind = test_rtlunwind_target;

int main()
{
    for (std::uintptr_t iteration = 1; iteration <= 32; ++iteration)
    {
        void* expected[4] = {
            reinterpret_cast<void*>(0x1000U + iteration),
            reinterpret_cast<void*>(0x2000U + iteration),
            reinterpret_cast<void*>(0x3000U + iteration),
            reinterpret_cast<void*>(0x4000U + iteration),
        };

        ImVehFt_Recovered_RtlUnwind(expected[0], expected[1], expected[2], expected[3]);

        if (call_count != iteration)
        {
            return 1;
        }
        for (std::size_t index = 0; index < 4; ++index)
        {
            if (captured_arguments[index] != expected[index])
            {
                return 2;
            }
        }
    }

    return 0;
}
