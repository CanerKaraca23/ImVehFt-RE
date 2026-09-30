#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <vector>

using TolowerFunction = int(__cdecl*)(int);

static HMODULE LoadImageWithoutInitialization(const wchar_t* path)
{
    return LoadLibraryExW(path, nullptr, DONT_RESOLVE_DLL_REFERENCES);
}

int wmain(int argc, wchar_t** argv)
{
    if (argc != 3)
    {
        std::fwprintf(stderr, L"usage: harness <original-asi> <diagnostic-dll>\n");
        return 2;
    }

    HMODULE original = LoadImageWithoutInitialization(argv[1]);
    if (original == nullptr)
    {
        std::fwprintf(stderr, L"original LoadLibraryEx failed: %lu\n", GetLastError());
        return 3;
    }

    HMODULE candidate = LoadImageWithoutInitialization(argv[2]);
    if (candidate == nullptr)
    {
        std::fwprintf(stderr, L"candidate LoadLibraryEx failed: %lu\n", GetLastError());
        return 4;
    }

    constexpr std::uintptr_t preferred_base = 0x10000000u;
    constexpr std::uintptr_t original_entry = 0x10015237u;
    constexpr std::uintptr_t candidate_entry = 0x1001d9b6u;
    constexpr std::uintptr_t original_locale_flag = 0x10039a84u;
    constexpr std::uintptr_t candidate_locale_flag = 0x10091ab8u;

    auto original_fn = reinterpret_cast<TolowerFunction>(
        reinterpret_cast<std::uintptr_t>(original) +
        (original_entry - preferred_base));
    auto candidate_fn = reinterpret_cast<TolowerFunction>(
        reinterpret_cast<std::uintptr_t>(candidate) +
        (candidate_entry - preferred_base));

    *reinterpret_cast<volatile std::uint32_t*>(
        reinterpret_cast<std::uintptr_t>(original) +
        (original_locale_flag - preferred_base)) = 0;
    *reinterpret_cast<volatile std::uint32_t*>(
        reinterpret_cast<std::uintptr_t>(candidate) +
        (candidate_locale_flag - preferred_base)) = 0;

    std::vector<std::uint32_t> inputs = {
        0u, 1u, 0x40u, 0x41u, 0x42u, 0x5Au, 0x5Bu, 0x7Fu, 0x80u,
        0xFFu, 0x100u, 0x7FFFFFFFu, 0x80000000u, 0xFFFFFF80u,
        0xFFFFFFFFu,
    };
    for (std::uint32_t value = 0x41u; value <= 0x5Au; ++value)
    {
        inputs.push_back(value);
    }

    std::uint32_t state = 0x6D2B79F5u;
    constexpr std::uint32_t random_count = 500000u;
    for (std::uint32_t i = 0; i < random_count; ++i)
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        inputs.push_back(state);
    }

    for (std::uint32_t i = 0; i < inputs.size(); ++i)
    {
        const int input = static_cast<int>(inputs[i]);
        const int expected = original_fn(input);
        const int actual = candidate_fn(input);
        if (actual != expected)
        {
            std::fprintf(
                stderr,
                "FAIL index=%u input=%08X original=%08X candidate=%08X\n",
                i,
                inputs[i],
                static_cast<unsigned int>(expected),
                static_cast<unsigned int>(actual));
            return 5;
        }
    }

    std::printf(
        "PASS: %zu bit-exact _tolower inputs through original and private-linked candidate; "
        "locale flag fixed to zero; images loaded without initialization.\n",
        inputs.size());
    FreeLibrary(candidate);
    FreeLibrary(original);
    return 0;
}
