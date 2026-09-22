#include <cstddef>
#include <cstdint>

extern std::uint32_t DAT_10039a4c;

extern "C" void* __stdcall DecodePointer(void* Ptr);

extern "C" int __cdecl __callnewh(std::size_t _Size)
{
    using NewHandler = int(__cdecl*)(std::size_t);

    auto handler = reinterpret_cast<NewHandler>(
        DecodePointer(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(DAT_10039a4c))));

    if (handler != nullptr) {
        int result = handler(_Size);
        if (result != 0) {
            return 1;
        }
    }

    return 0;
}