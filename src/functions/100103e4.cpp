#include <cstdarg>
#include <cstdint>

extern void* __input_l;

extern "C" std::uint32_t __cdecl vscan_fn(
    void* param_1,
    int param_2,
    std::uint32_t param_3,
    std::uint32_t param_4
);

int __cdecl FID_conflict__sscanf(
    char* _Src,
    char* _Format,
    ...
)
{
    (void)_Src;

    va_list arg_list;
    va_start(arg_list, _Format);

    const int result = static_cast<int>(
        vscan_fn(
            __input_l,
            static_cast<int>(
                reinterpret_cast<std::uintptr_t>(_Format)
            ),
            0,
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(arg_list)
            )
        )
    );

    va_end(arg_list);
    return result;
}