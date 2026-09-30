#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>

using Initializer = void(__cdecl*)(int);

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
    constexpr std::uintptr_t original_entry_va = 0x10001ad0u;
    constexpr std::uintptr_t candidate_entry_va = 0x10001948u;
    constexpr std::uintptr_t original_global_va = 0x1003aaccu;
    constexpr std::uintptr_t candidate_global_va = 0x10092b00u;

    auto original_fn = reinterpret_cast<Initializer>(
        reinterpret_cast<std::uintptr_t>(original) +
        original_entry_va - preferred_base);
    auto candidate_fn = reinterpret_cast<Initializer>(
        reinterpret_cast<std::uintptr_t>(candidate) +
        candidate_entry_va - preferred_base);

    std::array<std::uint8_t, 4096> original_memory{};
    std::array<std::uint8_t, 4096> candidate_memory{};
    std::array<std::uint8_t, 4096> expected_memory{};
    auto* original_base = original_memory.data() + 1024;
    auto* candidate_base = candidate_memory.data() + 1024;
    *reinterpret_cast<volatile std::uint32_t*>(
        reinterpret_cast<std::uintptr_t>(original) +
        original_global_va - preferred_base) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(original_base));
    *reinterpret_cast<volatile std::uint32_t*>(
        reinterpret_cast<std::uintptr_t>(candidate) +
        candidate_global_va - preferred_base) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(candidate_base));

    std::uint32_t state = 0xB5297A4Du;
    std::uint32_t cases = 0;
    auto compare_offset = [&](int offset, std::uint32_t seed) -> bool {
        for (std::size_t i = 0; i < original_memory.size(); ++i)
        {
            const std::uint8_t value = static_cast<std::uint8_t>(
                (i * 37u + (i >> 3) + seed) & 0xFFu);
            original_memory[i] = value;
            candidate_memory[i] = value;
            expected_memory[i] = value;
        }

        const auto write_at = static_cast<std::size_t>(1024 + offset);
        expected_memory[write_at] = 1;
        std::memset(expected_memory.data() + write_at + 1, 0, 15);

        original_fn(offset);
        candidate_fn(offset);
        if (std::memcmp(original_memory.data(), expected_memory.data(),
                        original_memory.size()) != 0 ||
            std::memcmp(candidate_memory.data(), expected_memory.data(),
                        candidate_memory.size()) != 0)
        {
            std::fprintf(stderr, "FAIL offset=%d seed=%08X\n", offset, seed);
            return false;
        }
        ++cases;
        return true;
    };

    for (int offset = -512; offset <= 512; ++offset)
    {
        if (!compare_offset(offset, 0x13579BDFu))
        {
            return 5;
        }
    }

    for (std::uint32_t i = 0; i < 50000u; ++i)
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        const int offset = static_cast<int>(state % 2049u) - 1024;
        if (!compare_offset(offset, state))
        {
            return 6;
        }
    }

    std::printf(
        "PASS: %u mapped original-vs-candidate memory-effect cases for "
        "0x10001ad0 over aligned/unaligned offsets; DLLs loaded without initialization.\n",
        cases);
    FreeLibrary(candidate);
    FreeLibrary(original);
    return 0;
}
