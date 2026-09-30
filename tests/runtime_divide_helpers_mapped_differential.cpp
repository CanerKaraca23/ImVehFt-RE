#include <Windows.h>

#include <cstdint>
#include <cstdio>

struct Invocation
{
    std::uint32_t quotient_low;
    std::uint32_t quotient_high;
    std::uint32_t remainder_low;
    std::uint32_t remainder_high;
    std::uint32_t stack_before;
    std::uint32_t stack_after;
    std::uint32_t ebx_before;
    std::uint32_t esi_before;
    std::uint32_t esi_after;
    std::uint32_t edi_before;
    std::uint32_t edi_after;
    std::uint32_t ebp_before;
    std::uint32_t ebp_after;
};

using DivideEntry = void(__stdcall*)();

static HMODULE LoadMappedImage(const wchar_t* path)
{
    return LoadLibraryExW(path, nullptr, DONT_RESOLVE_DLL_REFERENCES);
}

static Invocation Invoke(
    DivideEntry entry,
    std::uint32_t dividend_low,
    std::uint32_t dividend_high,
    std::uint32_t divisor_low,
    std::uint32_t divisor_high)
{
    Invocation result{};
    std::uint32_t entry_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(entry));
    __asm {
        mov result.stack_before, esp
        mov result.esi_before, esi
        mov result.edi_before, edi
        mov result.ebp_before, ebp
        mov result.ebx_before, ebx
        mov eax, entry_address
        push divisor_high
        push divisor_low
        push dividend_high
        push dividend_low
        call eax
        mov result.quotient_low, eax
        mov result.quotient_high, edx
        mov result.remainder_high, ebx
        mov result.remainder_low, ecx
        mov result.stack_after, esp
        mov result.esi_after, esi
        mov result.edi_after, edi
        mov result.ebp_after, ebp
        mov ebx, result.ebx_before
        mov esi, result.esi_before
        mov edi, result.edi_before
    }
    return result;
}

static bool SameInvocation(const Invocation& a, const Invocation& b)
{
    return a.quotient_low == b.quotient_low &&
        a.quotient_high == b.quotient_high &&
        a.remainder_low == b.remainder_low &&
        a.remainder_high == b.remainder_high &&
        a.stack_after == a.stack_before &&
        b.stack_after == b.stack_before &&
        a.esi_after == a.esi_before && b.esi_after == b.esi_before &&
        a.edi_after == a.edi_before && b.edi_after == b.edi_before &&
        a.ebp_after == a.ebp_before && b.ebp_after == b.ebp_before;
}

static bool NonzeroDivisor(std::uint32_t low, std::uint32_t high)
{
    return low != 0 || high != 0;
}

int wmain(int argc, wchar_t** argv)
{
    if (argc != 3)
    {
        fwprintf(stderr, L"usage: harness <original-asi> <diagnostic-dll>\n");
        return 2;
    }

    HMODULE original = LoadMappedImage(argv[1]);
    if (original == nullptr)
    {
        fwprintf(stderr, L"original LoadLibraryEx failed: %lu\n", GetLastError());
        return 3;
    }
    HMODULE candidate = LoadMappedImage(argv[2]);
    if (candidate == nullptr)
    {
        fwprintf(stderr, L"candidate LoadLibraryEx failed: %lu\n", GetLastError());
        return 4;
    }

    constexpr std::uintptr_t preferred_base = 0x10000000u;
    const auto entry = [](HMODULE image, std::uintptr_t va) {
        return reinterpret_cast<DivideEntry>(
            reinterpret_cast<std::uintptr_t>(image) + va - preferred_base);
    };

    DivideEntry original_unsigned = entry(original, 0x1001a900u);
    DivideEntry candidate_unsigned = entry(candidate, 0x100172a5u);
    DivideEntry original_signed = entry(original, 0x1001dda0u);
    DivideEntry candidate_signed = entry(candidate, 0x10019b4du);

    std::uint64_t tested = 0;
    auto compare = [&](std::uint32_t al, std::uint32_t ah,
                       std::uint32_t dl, std::uint32_t dh) -> bool {
        if (!NonzeroDivisor(dl, dh))
        {
            dl = 1;
        }
        const Invocation ou = Invoke(original_unsigned, al, ah, dl, dh);
        const Invocation cu = Invoke(candidate_unsigned, al, ah, dl, dh);
        if (!SameInvocation(ou, cu))
        {
            std::fprintf(stderr, "unsigned mismatch at test %llu\n",
                static_cast<unsigned long long>(tested));
            return false;
        }
        const Invocation os = Invoke(original_signed, al, ah, dl, dh);
        const Invocation cs = Invoke(candidate_signed, al, ah, dl, dh);
        if (!SameInvocation(os, cs))
        {
            std::fprintf(stderr, "signed mismatch at test %llu\n",
                static_cast<unsigned long long>(tested));
            return false;
        }
        ++tested;
        return true;
    };

    const std::uint64_t edge_values[] = {
        0, 1, 2, 3, 0x7FFFFFFFULL, 0x80000000ULL,
        0xFFFFFFFFULL, 0x100000000ULL, 0x7FFFFFFFFFFFFFFFULL,
        0x8000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL,
        0x00000001FFFFFFFFULL, 0xFFFFFFFF00000001ULL,
    };
    for (std::uint64_t dividend : edge_values)
    {
        for (std::uint64_t divisor : edge_values)
        {
            if (!compare(static_cast<std::uint32_t>(dividend),
                         static_cast<std::uint32_t>(dividend >> 32),
                         static_cast<std::uint32_t>(divisor),
                         static_cast<std::uint32_t>(divisor >> 32)))
            {
                return 5;
            }
        }
    }

    std::uint32_t state = 0xA341316Cu;
    constexpr std::uint32_t random_count = 250000u;
    for (std::uint32_t i = 0; i < random_count; ++i)
    {
        auto next = [&state]() {
            state ^= state << 13;
            state ^= state >> 17;
            state ^= state << 5;
            return state;
        };
        const std::uint32_t al = next();
        const std::uint32_t ah = next();
        const std::uint32_t dl = next();
        const std::uint32_t dh = next();
        if (!compare(al, ah, dl, dh))
        {
            return 6;
        }
    }

    std::printf(
        "PASS: %llu original-vs-candidate input pairs; unsigned and signed "
        "quotient/remainder outputs, stdcall stack cleanup and preserved ESI/EDI/EBP match. "
        "Images loaded without initialization.\n",
        static_cast<unsigned long long>(tested));
    FreeLibrary(candidate);
    FreeLibrary(original);
    return 0;
}
