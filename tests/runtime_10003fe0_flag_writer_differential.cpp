#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>

using FlagWriter = void(__cdecl*)(int, int);

int wmain(int argc, wchar_t** argv)
{
    if (argc != 3)
    {
        fwprintf(stderr, L"usage: harness <original-asi> <diagnostic-dll>\n");
        return 2;
    }

    HMODULE original = LoadLibraryExW(argv[1], nullptr, DONT_RESOLVE_DLL_REFERENCES);
    if (original == nullptr)
    {
        fwprintf(stderr, L"original LoadLibraryEx failed: %lu\n", GetLastError());
        return 3;
    }
    HMODULE candidate = LoadLibraryExW(argv[2], nullptr, DONT_RESOLVE_DLL_REFERENCES);
    if (candidate == nullptr)
    {
        fwprintf(stderr, L"candidate LoadLibraryEx failed: %lu\n", GetLastError());
        return 4;
    }

    constexpr std::uintptr_t preferred_base = 0x10000000u;
    constexpr std::uintptr_t original_entry_va = 0x10003fe0u;
    constexpr std::uintptr_t candidate_entry_va = 0x10003bfeu;
    auto original_fn = reinterpret_cast<FlagWriter>(
        reinterpret_cast<std::uintptr_t>(original) +
        original_entry_va - preferred_base);
    auto candidate_fn = reinterpret_cast<FlagWriter>(
        reinterpret_cast<std::uintptr_t>(candidate) +
        candidate_entry_va - preferred_base);

    std::array<std::uint8_t, 64> original_memory{};
    std::array<std::uint8_t, 64> candidate_memory{};
    std::array<std::uint8_t, 64> expected_memory{};
    std::uint32_t state = 0xC001D00Du;
    std::uint32_t cases = 0;

    auto compare = [&](std::uint32_t offset, int value, std::uint32_t seed) -> bool {
        for (std::size_t i = 0; i < original_memory.size(); ++i)
        {
            const auto byte = static_cast<std::uint8_t>(
                (i * 53u + (i >> 2) + seed) & 0xFFu);
            original_memory[i] = byte;
            candidate_memory[i] = byte;
            expected_memory[i] = byte;
        }

        expected_memory[offset + 2] = value != 0 ? 4u : 0u;
        const int original_pointer = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(original_memory.data() + offset));
        const int candidate_pointer = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(candidate_memory.data() + offset));
        original_fn(original_pointer, value);
        candidate_fn(candidate_pointer, value);

        if (std::memcmp(original_memory.data(), expected_memory.data(),
                        original_memory.size()) != 0 ||
            std::memcmp(candidate_memory.data(), expected_memory.data(),
                        candidate_memory.size()) != 0)
        {
            std::fprintf(stderr,
                "FAIL offset=%u value=%08X seed=%08X expected=%02X original=%02X candidate=%02X\n",
                offset, static_cast<unsigned int>(value), seed,
                expected_memory[offset + 2], original_memory[offset + 2],
                candidate_memory[offset + 2]);
            return false;
        }
        ++cases;
        return true;
    };

    constexpr int edge_values[] = {
        0, 1, -1, 2, -2, 4, -4, 0x7FFFFFFF,
        static_cast<int>(0x80000000u), 0x55555555, static_cast<int>(0xAAAAAAAAu),
    };
    for (std::uint32_t offset = 0; offset < 62; ++offset)
    {
        for (int value : edge_values)
        {
            if (!compare(offset, value, 0x2468ACE0u))
            {
                return 5;
            }
        }
    }

    for (std::uint32_t i = 0; i < 100000u; ++i)
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        const std::uint32_t offset = state % 62u;
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        if (!compare(offset, static_cast<int>(state), state ^ i))
        {
            return 6;
        }
    }

    std::printf(
        "PASS: %u mapped original-vs-candidate 0x10003fe0 writes; "
        "all offsets and nonzero/zero integer inputs match independent byte oracle.\n",
        cases);
    FreeLibrary(candidate);
    FreeLibrary(original);
    return 0;
}
