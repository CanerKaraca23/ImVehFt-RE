#include <cstdint>
#include <cstdlib>
#include <windows.h>

extern std::uint32_t _DAT_1003c3fc;
extern HANDLE DAT_1003c3e8;
extern int* DAT_1003c3ec;

extern "C" void __stdcall thunk_FUN_10009580();
extern "C" __declspec(noreturn) void __stdcall FUN_100095f0();
extern "C" void __stdcall FUN_100094d0();
extern "C" int* __stdcall FUN_10009360();
extern "C" int* __stdcall FUN_1000c420();

LPVOID __stdcall FUN_1000a350()
{
    int* mapped_data;
    HANDLE mapping_handle;

    if ((_DAT_1003c3fc & 1u) == 0)
    {
        _DAT_1003c3fc = _DAT_1003c3fc | 1u;
        DAT_1003c3e8 = static_cast<HANDLE>(0);
        DAT_1003c3ec = nullptr;
        std::atexit(reinterpret_cast<void (__cdecl*)()>(thunk_FUN_10009580));
    }

    if (DAT_1003c3ec == nullptr)
    {
        if (DAT_1003c3e8 == nullptr)
            goto open_mapping;

    map_view:
        if ((DAT_1003c3ec != nullptr) ||
            ((DAT_1003c3ec = static_cast<int*>(
                  MapViewOfFile(DAT_1003c3e8, 0xF001Fu, 0, 0, 0))),
             DAT_1003c3ec != nullptr))
        {
            mapped_data = DAT_1003c3ec;
            mapping_handle = DAT_1003c3e8;

            if ((DAT_1003c3e8 != nullptr) && (*DAT_1003c3ec == 0))
            {
                FUN_100095f0();
            }

            goto validate_mapping;
        }
    }
    else
    {
        mapped_data = DAT_1003c3ec;
        mapping_handle = DAT_1003c3e8;

        if (DAT_1003c3e8 != nullptr)
            goto mapping_ready;

    open_mapping:
        DAT_1003c3e8 = OpenFileMappingA(
            0xF001Fu,
            FALSE,
            "GTA_PLUGIN_SDK");

        mapped_data = DAT_1003c3ec;
        mapping_handle = DAT_1003c3e8;

        if (DAT_1003c3e8 != nullptr)
            goto map_view;
    }

validate_mapping:
    // Ghidra reloads both globals after the error/repair call path here.
    mapped_data = DAT_1003c3ec;
    mapping_handle = DAT_1003c3e8;
    if ((mapped_data != nullptr) && (mapping_handle != nullptr))
        goto mapping_ready;

    FUN_100094d0();
    mapped_data = DAT_1003c3ec;
    mapping_handle = DAT_1003c3e8;

mapping_ready:
    if ((mapped_data == nullptr) || (mapping_handle == nullptr))
        FUN_100095f0();

    LPVOID object = HeapAlloc(
        reinterpret_cast<HANDLE>(mapped_data[1]),
        0,
        0x6C);

    char* source = const_cast<char*>("DK22Pac");
    char character;

    do
    {
        character = *source;
        source[static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(object)) - 0x100243F0] = character;
        source = source + 1;
    } while (character != '\0');

    source = const_cast<char*>("ImVehFt.asi");

    do
    {
        character = *source;
        source[static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(object)) - 0x100243B0] = character;
        source = source + 1;
    } while (character != '\0');

    source = const_cast<char*>("ImVehFt");

    do
    {
        character = *source;
        source[static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(object)) - 0x10024408] = character;
        source = source + 1;
    } while (character != '\0');

    source = const_cast<char*>("2.0.2");

    do
    {
        character = *source;
        source[static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(object)) - 0x100243A8] = character;
        source = source + 1;
    } while (character != '\0');

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uint8_t*>(object) + 0x5C) = 1;

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uint8_t*>(object) + 0x60) = 0;

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uint8_t*>(object) + 0x58) = 0x20208;

    int* list = FUN_10009360();

    if (list[1] == 0)
    {
        list[1] = static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(list));
        *list = static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(list));
    }

    int* node = FUN_1000c420();

    if (node == nullptr)
    {
        node = nullptr;
    }
    else
    {
        node[2] = static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(object));

        if (node[1] == 0)
        {
            node[1] = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(node));
            *node = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(node));

            const int list_head = *list;
            auto* previous = *reinterpret_cast<std::uint32_t**>(
                static_cast<std::uintptr_t>(list_head) + 4);

            *previous = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(node));

            node[1] = static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(previous));
            *node = list_head;

            *reinterpret_cast<int**>(
                static_cast<std::uintptr_t>(list_head) + 4) = node;

            return object;
        }
    }

    const int list_head = *list;
    auto* previous = *reinterpret_cast<std::uint32_t**>(
        static_cast<std::uintptr_t>(list_head) + 4);

    *previous = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(node));

    node[1] = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(previous));
    *node = list_head;

    *reinterpret_cast<int**>(
        static_cast<std::uintptr_t>(list_head) + 4) = node;

    return object;
}