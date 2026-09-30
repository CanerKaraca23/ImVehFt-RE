#include <cstdint>
#include <cstdio>
#include <limits>

extern "C" std::int64_t __stdcall ivf_crt_alldiv_from_alldvrm(
    std::int64_t dividend, std::int64_t divisor);
extern "C" std::int64_t __stdcall ivf_crt_allrem_from_alldvrm(
    std::int64_t dividend, std::int64_t divisor);
extern "C" std::uint64_t __stdcall ivf_crt_aulldiv_from_aulldvrm(
    std::uint64_t dividend, std::uint64_t divisor);

static std::uint64_t next_value(std::uint64_t& state) {
    state ^= state << 13;
    state ^= state >> 7;
    state ^= state << 17;
    return state;
}

int main() {
    constexpr std::int64_t signed_values[] = {
        0, 1, -1, 2, -2, 9, -9, 10, -10,
        0x7fffffff, -0x7fffffff, 0x100000000LL, -0x100000000LL,
        (std::numeric_limits<std::int64_t>::max)(),
        (std::numeric_limits<std::int64_t>::min)()
    };
    std::uint64_t checks = 0;
    for (const auto dividend : signed_values) {
        for (const auto divisor : signed_values) {
            if (divisor == 0 ||
                (dividend == (std::numeric_limits<std::int64_t>::min)() && divisor == -1)) {
                continue;
            }
            if (ivf_crt_alldiv_from_alldvrm(dividend, divisor) != dividend / divisor ||
                ivf_crt_allrem_from_alldvrm(dividend, divisor) != dividend % divisor) {
                std::printf("signed mismatch: %lld / %lld\n",
                    static_cast<long long>(dividend), static_cast<long long>(divisor));
                return 1;
            }
            ++checks;
        }
    }

    std::uint64_t state = 0xA0761D6478BD642FULL;
    for (std::uint32_t index = 0; index < 100000; ++index) {
        const auto dividend = next_value(state);
        auto divisor = next_value(state);
        if (divisor == 0) divisor = 1;
        if (ivf_crt_aulldiv_from_aulldvrm(dividend, divisor) != dividend / divisor) {
            std::printf("unsigned mismatch at sample %u\n", index);
            return 2;
        }
        ++checks;
    }

    std::printf("PASS: %llu signed quotient/remainder and unsigned quotient cases\n",
        static_cast<unsigned long long>(checks));
    return 0;
}
