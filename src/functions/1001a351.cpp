#include <cstdint>

extern "C" void __cdecl _free(void* _Memory);

extern "C" void* PTR_DAT_10029ea8;
extern "C" void* PTR_DAT_10029eac;
extern "C" void* PTR_DAT_10029eb0;
extern "C" void* PTR_DAT_10029ed8;
extern "C" void* PTR_DAT_10029edc;

extern "C" void __cdecl ___free_lconv_num(std::uint32_t* param_1)
{
    if (param_1 != nullptr)
    {
        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[0])) != PTR_DAT_10029ea8)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[0])));
        }

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[1])) != PTR_DAT_10029eac)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[1])));
        }

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[2])) != PTR_DAT_10029eb0)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[2])));
        }

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[0x0c])) != PTR_DAT_10029ed8)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[0x0c])));
        }

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[0x0d])) != PTR_DAT_10029edc)
        {
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(param_1[0x0d])));
        }
    }
}