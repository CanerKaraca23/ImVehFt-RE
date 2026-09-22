#include <windows.h>
#include <cstdint>
#include <cstring>

extern std::uint16_t DAT_100243dc;

extern int __cdecl strncmp(
    char* str1,
    char* str2,
    std::uint32_t max_count);

extern "C" std::int32_t __cdecl FUN_10001b90(
    LPCSTR param_1,
    void* param_2);

using Callback = void (__cdecl*)(LPCSTR);

extern "C" std::int32_t __cdecl FUN_10001b90(
    LPCSTR param_1,
    void* param_2)
{
    char local_460[320];
    CHAR local_320[264];
    char local_218[264];
    CHAR local_110[268];
    char* local_464;

    std::memset(local_460, 0, 0x140);

    DWORD result = GetFullPathNameA(
        param_1,
        0x104,
        local_110,
        &local_464);

    if (result == 0)
        return 0;

    char* source = local_464;
    char* destination = local_218;

    do
    {
        char value = *source;
        *destination = value;
        ++source;
        ++destination;
    } while (destination[-1] != '\0');

    std::memcpy(local_464, "*.*", 4);

    *reinterpret_cast<std::uint32_t*>(local_460) = 0x10;

    HANDLE find_handle = FindFirstFileA(
        local_110,
        reinterpret_cast<LPWIN32_FIND_DATAA>(local_460));

    if (find_handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (strncmp(local_460 + 0x2c, const_cast<char*>("."), 1) != 0 &&
                strncmp(local_460 + 0x2c, const_cast<char*>(".."), 2) != 0 &&
                ((*reinterpret_cast<std::uint32_t*>(local_460) & 0x10) != 0))
            {
                result = GetFullPathNameA(
                    param_1,
                    0x104,
                    local_320,
                    &local_464);

                if (result == 0)
                    return 0;

                source = local_460 + 0x2c;
                destination = local_464;

                do
                {
                    char value = *source;
                    *destination = value;
                    ++source;
                    ++destination;
                } while (destination[-1] != '\0');

                auto* word_pointer =
                    reinterpret_cast<std::uint16_t*>(local_460 + 0x13f);

                char* next;
                do
                {
                    next = reinterpret_cast<char*>(word_pointer) + 1;
                    word_pointer =
                        reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(word_pointer) + 1);
                } while (*next != '\0');

                *word_pointer = DAT_100243dc;

                source = local_218;
                do
                {
                    ++source;
                } while (source[-1] != '\0');

                std::uint32_t length =
                    static_cast<std::uint32_t>(source - local_218);

                destination = local_460 + 0x13f;

                do
                {
                    next = destination + 1;
                    destination = destination + 1;
                } while (*next != '\0');

                source = local_218;

                for (std::uint32_t count = length >> 2;
                     count != 0;
                     --count)
                {
                    *reinterpret_cast<std::uint32_t*>(destination) =
                        *reinterpret_cast<const std::uint32_t*>(source);

                    source += 4;
                    destination += 4;
                }

                for (std::uint32_t count = length & 3;
                     count != 0;
                     --count)
                {
                    *destination = *source;
                    ++source;
                    ++destination;
                }

                FUN_10001b90(local_320, param_2);
            }

        } while (FindNextFileA(
            find_handle,
            reinterpret_cast<LPWIN32_FIND_DATAA>(local_460)) != 0);
    }

    FindClose(find_handle);

    find_handle = FindFirstFileA(
        param_1,
        reinterpret_cast<LPWIN32_FIND_DATAA>(local_460));

    if (find_handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ((*reinterpret_cast<std::uint32_t*>(local_460) & 0x10) == 0)
            {
                result = GetFullPathNameA(
                    param_1,
                    0x104,
                    local_218,
                    &local_464);

                if (result == 0)
                    return 0;

                source = local_460 + 0x2c;
                destination = local_464;

                do
                {
                    char value = *source;
                    *destination = value;
                    ++source;
                    ++destination;
                } while (destination[-1] != '\0');

                reinterpret_cast<Callback>(param_2)(local_218);
            }

        } while (FindNextFileA(
            find_handle,
            reinterpret_cast<LPWIN32_FIND_DATAA>(local_460)) != 0);

        FindClose(find_handle);
    }

    return 1;
}