#include <cstddef>
#include <cstdint>

using PVOID = void*;

extern "C" PVOID __cdecl DecodePointer(PVOID pointer);
extern "C" PVOID __cdecl EncodePointer(PVOID pointer);
extern "C" std::size_t __cdecl __msize(PVOID memory);
extern "C" PVOID __cdecl __realloc_crt(PVOID memory, std::size_t size);

extern PVOID DAT_1003d548;
extern PVOID DAT_1003d54c;

PVOID __cdecl __onexit_nolock(PVOID param_1)
{
    auto* memory =
        static_cast<std::uint32_t*>(DecodePointer(DAT_1003d54c));
    auto* current =
        static_cast<std::uint32_t*>(DecodePointer(DAT_1003d548));

    int offset;
    if (current < memory ||
        (offset = static_cast<int>(
             reinterpret_cast<std::uintptr_t>(current) -
             reinterpret_cast<std::uintptr_t>(memory)),
         offset + 4U < 4))
    {
        return nullptr;
    }

    const std::size_t current_size = __msize(memory);

    if (current_size < offset + 4U)
    {
        std::size_t growth = 0x800;
        if (current_size < 0x800)
        {
            growth = current_size;
        }

        PVOID resized;
        if (growth + current_size < current_size ||
            (resized = __realloc_crt(memory, growth + current_size),
             resized == nullptr))
        {
            if (current_size + 0x10 < current_size)
            {
                return nullptr;
            }

            resized = __realloc_crt(memory, current_size + 0x10);
            if (resized == nullptr)
            {
                return nullptr;
            }
        }

        current = reinterpret_cast<std::uint32_t*>(
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(resized)) +
            (offset >> 2) * 4);

        DAT_1003d54c = EncodePointer(resized);
    }

    const PVOID encoded_param = EncodePointer(param_1);
    *current = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(encoded_param));

    DAT_1003d548 = EncodePointer(current + 1);
    return param_1;
}