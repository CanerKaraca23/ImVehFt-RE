#include <Windows.h>
#include <cstdint>
#include <cstddef>

extern "C" void* __cdecl __calloc_crt(std::size_t, std::size_t);
extern "C" std::uint32_t DAT_1003c418;
extern "C" void* DAT_1003c420[64];

int __cdecl __ioinit(void)
{
    void* block;
    DWORD file_type;
    BOOL initialized;
    HANDLE handle;
    UINT count;
    UINT initialized_count;
    std::uint32_t* block_slot;
    std::uint32_t index;
    std::uint8_t* flags;
    std::uint8_t* handles;
    STARTUPINFOW startup_info;

    GetStartupInfoW(&startup_info);

    block = __calloc_crt(0x20, 0x40);
    if (block == nullptr)
        return -1;

    DAT_1003c418 = 0x20;
    DAT_1003c420[0] = block;

    if (reinterpret_cast<std::uintptr_t>(block) <
        reinterpret_cast<std::uintptr_t>(block) + 0x800U)
    {
        std::uintptr_t cursor =
            reinterpret_cast<std::uintptr_t>(block) + 5U;
        const std::uintptr_t limit =
            reinterpret_cast<std::uintptr_t>(block) + 0x800U;

        do
        {
            auto* entry = reinterpret_cast<std::uint8_t*>(cursor - 5U);

            *reinterpret_cast<std::uint32_t*>(entry + 0x00) = 0xFFFFFFFFU;
            *reinterpret_cast<std::uint16_t*>(entry + 0x04) = 0x0A00;
            *reinterpret_cast<std::uint32_t*>(entry + 0x08) = 0;
            *reinterpret_cast<std::uint16_t*>(entry + 0x24) = 0x0A00;
            *reinterpret_cast<std::uint8_t*>(entry + 0x26) = 10;
            *reinterpret_cast<std::uint32_t*>(entry + 0x38) = 0;
            *reinterpret_cast<std::uint8_t*>(entry + 0x34) = 0;

            cursor += 0x40U;
        }
        while ((cursor - 0x40U) + 0x3BU < limit);
    }

    if ((startup_info.cbReserved2 != 0) &&
        (startup_info.lpReserved2 != nullptr))
    {
        count = *reinterpret_cast<UINT*>(startup_info.lpReserved2);
        flags = startup_info.lpReserved2 + 4;
        handles = flags + count;

        if (0x7FF < static_cast<int>(count))
            count = 0x800;

        initialized_count = count;

        if (static_cast<int>(DAT_1003c418) < static_cast<int>(count))
        {
            block_slot = reinterpret_cast<std::uint32_t*>(&DAT_1003c420[1]);

            do
            {
                block = __calloc_crt(0x20, 0x40);
                initialized_count = DAT_1003c418;

                if (block == nullptr)
                    break;

                DAT_1003c418 += 0x20;
                *block_slot = static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(block));

                if (reinterpret_cast<std::uintptr_t>(block) <
                    reinterpret_cast<std::uintptr_t>(block) + 0x800U)
                {
                    std::uintptr_t cursor =
                        reinterpret_cast<std::uintptr_t>(block) + 5U;
                    const std::uintptr_t limit =
                        reinterpret_cast<std::uintptr_t>(block) + 0x800U;

                    do
                    {
                        auto* entry =
                            reinterpret_cast<std::uint8_t*>(cursor - 5U);

                        *reinterpret_cast<std::uint32_t*>(entry + 0x00) =
                            0xFFFFFFFFU;
                        *reinterpret_cast<std::uint32_t*>(entry + 0x08) = 0;
                        *reinterpret_cast<std::uint8_t*>(entry + 0x24) =
                            *reinterpret_cast<std::uint8_t*>(entry + 0x24) &
                            0x80;
                        *reinterpret_cast<std::uint32_t*>(entry + 0x38) = 0;
                        *reinterpret_cast<std::uint16_t*>(entry + 0x04) =
                            0x0A00;
                        *reinterpret_cast<std::uint16_t*>(entry + 0x25) =
                            0x0A0A;
                        *reinterpret_cast<std::uint8_t*>(entry + 0x34) = 0;

                        cursor += 0x40U;
                    }
                    while ((cursor - 0x40U) + 0x3BU < limit);
                }

                ++block_slot;
                initialized_count = count;
            }
            while (static_cast<int>(DAT_1003c418) < static_cast<int>(count));
        }

        index = 0;

        if (0 < static_cast<int>(initialized_count))
        {
            do
            {
                handle = *reinterpret_cast<HANDLE*>(handles);

                if ((handle != INVALID_HANDLE_VALUE) &&
                    (handle != reinterpret_cast<HANDLE>(-2)) &&
                    ((*flags & 1) != 0) &&
                    (((*flags & 8) != 0) ||
                     ((file_type = GetFileType(handle)), file_type != 0)))
                {
                    auto* entry = reinterpret_cast<std::uint8_t*>(
                        DAT_1003c420[index >> 5]) +
                        ((index & 0x1FU) * 0x40U);

                    *reinterpret_cast<HANDLE*>(entry + 0x00) = handle;
                    *reinterpret_cast<std::uint8_t*>(entry + 0x04) = *flags;

                    initialized = InitializeCriticalSectionAndSpinCount(
                        reinterpret_cast<LPCRITICAL_SECTION>(entry + 0x0C),
                        4000);

                    if (initialized == 0)
                        return -1;

                    *reinterpret_cast<std::uint32_t*>(entry + 0x08) += 1;
                }

                handles += 4;
                ++index;
                ++flags;
            }
            while (static_cast<int>(index) <
                   static_cast<int>(initialized_count));
        }
    }

    index = 0;

    do
    {
        auto* entry = reinterpret_cast<std::uint8_t*>(
            DAT_1003c420[0]) + index * 0x40U;
        auto* entry_handle = reinterpret_cast<HANDLE*>(entry + 0x00);
        auto* entry_flags = reinterpret_cast<std::uint8_t*>(entry + 0x04);

        if ((*entry_handle == INVALID_HANDLE_VALUE) ||
            (*entry_handle == reinterpret_cast<HANDLE>(-2)))
        {
            *entry_flags = 0x81;

            if (index == 0)
                file_type = 0xFFFFFFF6U;
            else
                file_type = 0xFFFFFFF5U - (index != 1);

            handle = GetStdHandle(file_type);

            if ((handle == INVALID_HANDLE_VALUE) ||
                (handle == nullptr) ||
                ((file_type = GetFileType(handle)), file_type == 0))
            {
                *entry_flags = *entry_flags | 0x40;
                *entry_handle = reinterpret_cast<HANDLE>(-2);
            }
            else
            {
                *entry_handle = handle;

                if ((file_type & 0xFF) == 2)
                    *entry_flags = *entry_flags | 0x40;
                else if ((file_type & 0xFF) == 3)
                    *entry_flags = *entry_flags | 8;

                initialized = InitializeCriticalSectionAndSpinCount(
                    reinterpret_cast<LPCRITICAL_SECTION>(entry + 0x0C),
                    4000);

                if (initialized == 0)
                    return -1;

                *reinterpret_cast<std::uint32_t*>(entry + 0x08) += 1;
            }
        }
        else
        {
            *entry_flags = *entry_flags | 0x80;
        }

        ++index;
    }
    while (static_cast<int>(index) < 3);

    SetHandleCount(DAT_1003c418);
    return 0;
}