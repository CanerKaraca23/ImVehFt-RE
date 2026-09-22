#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <cstddef>
#include <cstdint>
#include <cstdio>

extern "C" void __cdecl FUN_100014c0(const char* format, ...);
extern "C" FILE* __cdecl fopen(const char* filename, const char* mode);
extern "C" char* __cdecl fgets(char* buffer, int count, FILE* stream);
extern "C" int __cdecl FID_conflict__sscanf(
    const char* buffer,
    const char* format,
    ...);
extern "C" void* __cdecl FUN_10010230(std::size_t size);
extern "C" void* __stdcall FUN_10001430(char* param_1, int param_2);
extern "C" void* __stdcall FUN_100101c2(char* param_1);
extern "C" int __cdecl fclose(FILE* stream);

extern char* DAT_1003c25c;
extern int _DAT_1003c260;

extern "C" void __cdecl FUN_10001040(char* param_1)
{
    char local_180[256];
    std::uint8_t local_80[32];
    std::uint8_t local_60[4];
    std::uint8_t local_5c[4];
    std::uint8_t local_58[40];

    std::uint16_t local_30;
    std::uint8_t local_2e;
    std::uint8_t local_2d;
    int local_2c;
    int local_28;

    std::uint16_t local_24[2];
    std::uint16_t local_20[2];
    std::uint16_t local_1c[2];
    std::uint16_t local_18[2];

    FILE* local_14;
    std::uint16_t local_10[2];
    std::uint32_t local_c;
    std::uint32_t local_8;

    FUN_100014c0(
        "CarColors::ReadColorFile: processing %s",
        param_1);

    local_14 = fopen(param_1, "rt");

    do
    {
        do
        {
            fgets(local_180, 0x100, local_14);
        } while (local_180[0] == '#');
    } while (((local_180[0] == ';') ||
              (local_180[0] == '\0')) ||
             (local_180[0] == '\n'));

    FID_conflict__sscanf(
        local_180,
        "%s %d",
        local_80,
        local_10);

    FUN_100014c0("  vehicle %d", local_10[0]);

    local_30 = local_10[0];

    do
    {
        do
        {
            fgets(local_180, 0x100, local_14);
        } while (local_180[0] == '#');
    } while (((local_180[0] == ';') ||
              (local_180[0] == '\0')) ||
             (local_180[0] == '\n'));

    FID_conflict__sscanf(
        local_180,
        "%s %d",
        local_80,
        &local_8);

    FUN_100014c0("  num colors %d", local_8);

    local_2e = static_cast<std::uint8_t>(local_8);

    const std::uint64_t color_product =
        static_cast<std::uint64_t>(local_8) * 4;

    const std::uint32_t color_size =
        ((color_product >> 32) != 0)
            ? 0xffffffffu
            : static_cast<std::uint32_t>(color_product);

    local_2c = static_cast<int>(
        reinterpret_cast<std::uintptr_t>(
            FUN_10010230(static_cast<std::size_t>(color_size))));

    std::uint32_t color_index = 0;

    if (local_8 != 0)
    {
        auto* color_data = reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(local_2c)) + 2);

        do
        {
            do
            {
                do
                {
                    fgets(local_180, 0x100, local_14);
                } while (local_180[0] == '#');
            } while (((local_180[0] == ';') ||
                      (local_180[0] == '\0')) ||
                     (local_180[0] == '\n'));

            FID_conflict__sscanf(
                local_180,
                "%d %d %d",
                local_60,
                local_5c,
                local_58);

            const int color_0 =
                *reinterpret_cast<const int*>(local_60);
            const int color_1 =
                *reinterpret_cast<const int*>(local_5c);
            const int color_2 =
                *reinterpret_cast<const int*>(local_58);

            FUN_100014c0(
                "    color %d %d %d",
                color_0,
                color_1,
                color_2);

            color_data[-2] = static_cast<std::uint8_t>(color_0);
            color_data[-1] = static_cast<std::uint8_t>(color_1);
            color_data[0] = static_cast<std::uint8_t>(color_2);
            color_data[1] = 0xff;

            color_index = color_index + 1;
            color_data = color_data + 4;
            local_14 = local_14;
        } while (color_index < local_8);
    }

    do
    {
        do
        {
            fgets(local_180, 0x100, local_14);
        } while (local_180[0] == '#');
    } while (((local_180[0] == ';') ||
              (local_180[0] == '\0')) ||
             (local_180[0] == '\n'));

    FID_conflict__sscanf(
        local_180,
        "%s %d",
        local_80,
        &local_c);

    FUN_100014c0("  num variations %d", local_c);

    local_2d = static_cast<std::uint8_t>(local_c);

    const std::uint64_t variation_product =
        static_cast<std::uint64_t>(local_c) * 8;

    const std::uint32_t variation_size =
        ((variation_product >> 32) != 0)
            ? 0xffffffffu
            : static_cast<std::uint32_t>(variation_product);

    local_28 = static_cast<int>(
        reinterpret_cast<std::uintptr_t>(
            FUN_10010230(static_cast<std::size_t>(variation_size))));

    std::uint32_t variation_index = 0;

    if (local_c != 0)
    {
        auto* variation_data = reinterpret_cast<std::uint16_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(local_28)) + 4);

        do
        {
            do
            {
                do
                {
                    fgets(local_180, 0x100, local_14);
                } while (local_180[0] == '#');
            } while (((local_180[0] == ';') ||
                      (local_180[0] == '\0')) ||
                     (local_180[0] == '\n'));

            FID_conflict__sscanf(
                local_180,
                "%d %d %d %d",
                local_24,
                local_20,
                local_1c,
                local_18);

            FUN_100014c0(
                "    variation %d %d %d %d",
                local_24[0],
                local_20[0],
                local_1c[0],
                local_18[0]);

            variation_data[-2] = local_24[0];
            variation_data[-1] = local_20[0];
            variation_data[0] = local_1c[0];
            variation_data[1] = local_18[0];

            variation_index = variation_index + 1;
            variation_data = variation_data + 4;
        } while (variation_index < local_c);
    }

    char* list_node = DAT_1003c25c;

    void* new_node = FUN_10001430(
        DAT_1003c25c,
        *reinterpret_cast<int*>(DAT_1003c25c + 4));

    if (_DAT_1003c260 == 0x15555554)
    {
        new_node = reinterpret_cast<void*>(FUN_100101c2(const_cast<char*>("list<T> too long")));
    }

    _DAT_1003c260 = _DAT_1003c260 + 1;
    *reinterpret_cast<void**>(list_node + 4) = new_node;
    **reinterpret_cast<void***>(
        static_cast<std::uint8_t*>(new_node) + 4) = new_node;

    fclose(local_14);
}