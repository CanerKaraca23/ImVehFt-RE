#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <xmmintrin.h>

namespace {

constexpr std::uintptr_t kOriginalFunctionRva = 0x0001c60eu;
constexpr std::uintptr_t kCandidateFunctionRva = 0x00018921u;
constexpr std::uintptr_t kOriginalCallerRva = 0x0001c5f0u;
constexpr std::uintptr_t kCandidateCallerRva = 0x00018909u;
constexpr std::uint16_t kReductionExponentBase = 0x3030u;
constexpr std::uint16_t kReductionExponentSpan = 0x10c6u;

bool resolve_imports_without_entrypoint(HMODULE module)
{
    auto* base = reinterpret_cast<std::uint8_t*>(module);
    auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;
    auto* nt = reinterpret_cast<IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC) return false;

    const auto& directory = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (directory.VirtualAddress == 0 || directory.Size == 0) return true;
    auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + directory.VirtualAddress);
    for (; descriptor->Name != 0; ++descriptor) {
        auto* library = LoadLibraryA(reinterpret_cast<const char*>(base + descriptor->Name));
        if (library == nullptr) return false;
        auto* lookup = reinterpret_cast<IMAGE_THUNK_DATA32*>(
            base + (descriptor->OriginalFirstThunk != 0
                        ? descriptor->OriginalFirstThunk : descriptor->FirstThunk));
        auto* iat = reinterpret_cast<IMAGE_THUNK_DATA32*>(base + descriptor->FirstThunk);
        for (; lookup->u1.AddressOfData != 0; ++lookup, ++iat) {
            FARPROC address = nullptr;
            if (IMAGE_SNAP_BY_ORDINAL32(lookup->u1.Ordinal)) {
                address = GetProcAddress(
                    library, MAKEINTRESOURCEA(IMAGE_ORDINAL32(lookup->u1.Ordinal)));
            } else {
                auto* import = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                    base + lookup->u1.AddressOfData);
                address = GetProcAddress(library,
                    reinterpret_cast<const char*>(import->Name));
            }
            if (address == nullptr) return false;
            DWORD old_protection = 0;
            if (!VirtualProtect(iat, sizeof(*iat), PAGE_READWRITE, &old_protection))
                return false;
            iat->u1.Function = static_cast<DWORD>(
                reinterpret_cast<std::uintptr_t>(address));
            DWORD ignored_protection = 0;
            if (!VirtualProtect(iat, sizeof(*iat), old_protection, &ignored_protection))
                return false;
        }
    }
    return true;
}

struct Image final {
    HMODULE module = nullptr;
    bool imports_resolved = false;

    explicit Image(const wchar_t* path)
    {
        module = LoadLibraryExW(path, nullptr, DONT_RESOLVE_DLL_REFERENCES);
        if (module != nullptr) imports_resolved = resolve_imports_without_entrypoint(module);
    }

    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    ~Image()
    {
        if (module != nullptr) FreeLibrary(module);
    }

    std::uintptr_t address(std::uintptr_t rva) const
    {
        return reinterpret_cast<std::uintptr_t>(module) + rva;
    }
};

void invoke(std::uintptr_t entry, double input, std::uint32_t mxcsr,
            volatile std::uint8_t* output)
{
    // Give both images the same known floating-point environment. The target
    // uses SSE2 and returns through x87 ST(0).
    _mm_setcsr(mxcsr);
    __asm {
        mov eax, entry
        movsd xmm0, input
        xor ecx, ecx
        call eax
        mov edx, output
        fstp tbyte ptr [edx]
    }
}

void invoke_caller(std::uintptr_t caller, double input, std::uint32_t mxcsr,
                   std::uint16_t x87_control_word,
                   volatile std::uint8_t* output)
{
    _mm_setcsr(mxcsr);
    __asm {
        fninit
        fldcw x87_control_word
        fld input
        mov eax, caller
        xor ecx, ecx
        call eax
        mov edx, output
        fstp tbyte ptr [edx]
    }
}

int report_seh(EXCEPTION_POINTERS* exception)
{
    const auto* record = exception->ExceptionRecord;
    std::fwprintf(stderr, L"SEH code=%08lX eip=%08lX access=%llu target=%p\n",
                  record->ExceptionCode, exception->ContextRecord->Eip,
                  record->NumberParameters > 0
                      ? static_cast<unsigned long long>(record->ExceptionInformation[0]) : 0ull,
                  record->NumberParameters > 1
                      ? reinterpret_cast<void*>(record->ExceptionInformation[1]) : nullptr);
    std::fflush(stderr);
    return EXCEPTION_EXECUTE_HANDLER;
}

bool invoke_caller_guarded(std::uintptr_t caller, double input, std::uint32_t mxcsr,
                           std::uint16_t x87_control_word,
                           volatile std::uint8_t* output)
{
    __try {
        invoke_caller(caller, input, mxcsr, x87_control_word, output);
        return true;
    }
    __except (report_seh(GetExceptionInformation())) {
        return false;
    }
}

std::uint32_t next_random(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

double make_reduction_input(std::uint16_t exponent_word, std::uint64_t mantissa,
                            bool negative)
{
    const std::uint64_t sign = negative ? (std::uint64_t{1} << 63) : 0;
    const std::uint64_t bits = sign |
        (static_cast<std::uint64_t>(exponent_word & 0x7fffu) << 48) |
        (mantissa & 0x0000ffffffffffffull);
    double value = 0.0;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

bool compare(std::uintptr_t original, std::uintptr_t candidate, double input,
             std::uint32_t mxcsr, std::uint32_t case_number)
{
    std::array<std::uint8_t, 10> original_result{};
    std::array<std::uint8_t, 10> candidate_result{};
    std::uint64_t input_bits = 0;
    std::memcpy(&input_bits, &input, sizeof(input_bits));
    const auto exponent_word = static_cast<std::uint16_t>((input_bits >> 48) & 0x7fffu);
    const auto reduction_word = static_cast<std::uint16_t>(exponent_word - kReductionExponentBase);
    const bool exception_tail = reduction_word > 0x10c5u &&
                                static_cast<std::int16_t>(reduction_word) > 0x10c5;
    if (exception_tail) {
        std::fwprintf(stderr, L"unexpected exception-tail input in direct-call comparison: %016llX\n",
                      static_cast<unsigned long long>(input_bits));
        return false;
    }
    invoke(original, input, mxcsr, original_result.data());
    invoke(candidate, input, mxcsr, candidate_result.data());
    invoke(original, input, mxcsr, original_result.data());
    invoke(candidate, input, mxcsr, candidate_result.data());
    if (original_result == candidate_result) return true;

    std::fwprintf(stderr,
                  L"MISMATCH case=%u input=%016llX original={",
                  case_number, static_cast<unsigned long long>(input_bits));
    for (const auto byte : original_result) std::fwprintf(stderr, L"%02X", byte);
    std::fwprintf(stderr, L"} candidate={");
    for (const auto byte : candidate_result) std::fwprintf(stderr, L"%02X", byte);
    std::fwprintf(stderr, L"}\n");
    return false;
}

} // namespace

int wmain(int argc, wchar_t** argv)
{
    if (argc != 3) {
        std::fwprintf(stderr, L"usage: %ls <original.asi> <candidate-diagnostic.dll>\n", argv[0]);
        return 2;
    }

    Image original(argv[1]);
    Image candidate(argv[2]);
    if (original.module == nullptr || candidate.module == nullptr ||
        !original.imports_resolved || !candidate.imports_resolved) {
        std::fwprintf(stderr, L"LoadLibraryEx(DONT_RESOLVE_DLL_REFERENCES) failed: %lu\n",
                      GetLastError());
        return 3;
    }
    if (original.module == candidate.module) {
        std::fwprintf(stderr, L"unexpected image bases: original=%p candidate=%p\n",
                      original.module, candidate.module);
        return 4;
    }

    struct DataPair { const wchar_t* name; std::uintptr_t original_rva; std::uintptr_t candidate_rva; };
    constexpr std::array<DataPair, 18> data_pairs{{
        {L"DAT_10025010", 0x25010u, 0x35e50u}, {L"DAT_10025018", 0x25018u, 0x35e58u},
        {L"DAT_10025020", 0x25020u, 0x35e60u}, {L"DAT_10025028", 0x25028u, 0x35e68u},
        {L"_DAT_10025810", 0x25810u, 0x36650u}, {L"_DAT_10025820", 0x25820u, 0x36660u},
        {L"_DAT_10025830", 0x25830u, 0x36670u}, {L"_DAT_10025840", 0x25840u, 0x36680u},
        {L"DAT_10025850", 0x25850u, 0x36690u}, {L"DAT_10025858", 0x25858u, 0x36698u},
        {L"_DAT_10025860", 0x25860u, 0x366a0u}, {L"DAT_10025870", 0x25870u, 0x366b0u},
        {L"_DAT_10025878", 0x25878u, 0x366b8u}, {L"_UNK_10025818", 0x25818u, 0x3d658u},
        {L"_UNK_10025828", 0x25828u, 0x3d668u}, {L"_UNK_10025838", 0x25838u, 0x3d678u},
        {L"_UNK_10025848", 0x25848u, 0x3d688u}, {L"_UNK_10025868", 0x25868u, 0x3d6a8u},
    }};
    for (const auto& pair : data_pairs) {
        std::uint64_t original_bits = 0;
        std::uint64_t candidate_bits = 0;
        std::memcpy(&original_bits, reinterpret_cast<const void*>(original.address(pair.original_rva)),
                    sizeof(original_bits));
        std::memcpy(&candidate_bits, reinterpret_cast<const void*>(candidate.address(pair.candidate_rva)),
                    sizeof(candidate_bits));
        if (original_bits != candidate_bits) {
            std::fwprintf(stderr, L"DATA MISMATCH %ls original=%016llX candidate=%016llX\n",
                          pair.name, static_cast<unsigned long long>(original_bits),
                          static_cast<unsigned long long>(candidate_bits));
            return 7;
        }
        if (pair.original_rva < 0x25030u) {
            std::wprintf(L"DATA %ls = %016llX\n", pair.name,
                         static_cast<unsigned long long>(original_bits));
        }
    }
    const auto* original_table = reinterpret_cast<const void*>(original.address(0x25010u));
    const auto* candidate_table = reinterpret_cast<const void*>(candidate.address(0x35e50u));
    if (std::memcmp(original_table, candidate_table, 0x800u) != 0) {
        const auto* old_bytes = static_cast<const std::uint8_t*>(original_table);
        const auto* new_bytes = static_cast<const std::uint8_t*>(candidate_table);
        for (std::size_t offset = 0; offset < 0x800u; ++offset) {
            if (old_bytes[offset] != new_bytes[offset]) {
                std::fwprintf(stderr, L"TABLE MISMATCH offset=%03zX original=%02X candidate=%02X\n",
                              offset, old_bytes[offset], new_bytes[offset]);
                break;
            }
        }
        return 8;
    }

    const auto original_function = original.address(kOriginalFunctionRva);
    const auto candidate_function = candidate.address(kCandidateFunctionRva);
    const auto original_caller = original.address(kOriginalCallerRva);
    const auto candidate_caller = candidate.address(kCandidateCallerRva);
    std::uint32_t case_number = 0;

    constexpr std::array<std::uint16_t, 15> exponent_words{
        0x0000u, 0x0001u, 0x000fu, 0x0010u, 0x1000u, 0x302fu,
        0x3030u, 0x3031u, 0x3100u, 0x3500u, 0x3fc0u, 0x3fd0u,
        0x4000u, 0x40f4u, 0x40f5u,
    };
    constexpr std::array<std::uint64_t, 4> mantissas{
        0ull, 1ull, 0x00007fffffffffffull, 0x0000ffffffffffffull,
    };
    constexpr std::array<std::uint32_t, 4> rounding_modes{
        0x1f80u, // nearest
        0x3f80u, // down
        0x5f80u, // up
        0x7f80u, // toward zero
    };
    for (const auto mxcsr : rounding_modes) {
        for (const auto exponent_word : exponent_words) {
            for (const auto mantissa : mantissas) {
                for (const bool negative : {false, true}) {
                    if (!compare(original_function, candidate_function,
                                 make_reduction_input(exponent_word, mantissa, negative),
                                 mxcsr, case_number++)) return 5;
                }
            }
        }

        constexpr std::uint32_t kRandomCases = 50000;
        std::uint32_t state = 0x1c60e029u;
        for (std::uint32_t index = 0; index < kRandomCases; ++index) {
            const auto exponent_word = static_cast<std::uint16_t>(
                kReductionExponentBase + next_random(state) % kReductionExponentSpan);
            const auto mantissa =
                (static_cast<std::uint64_t>(next_random(state)) << 16) |
                (next_random(state) & 0xffffu);
            const bool negative = (next_random(state) & 1u) != 0;
            if (!compare(original_function, candidate_function,
                         make_reduction_input(exponent_word, mantissa, negative),
                         mxcsr, case_number++)) return 6;
        }
    }

    constexpr std::array<std::uint16_t, 3> tail_exponents{0x40f6u, 0x40f7u, 0x4100u};
    constexpr std::array<std::uint16_t, 4> x87_control_words{
        0x037fu, // default extended precision, nearest
        0x027fu, // original helper's saved-word comparison case
        0x0b7fu, // round upward
        0x0f7fu, // truncate toward zero
    };
    std::uint32_t tail_cases = 0;
    for (const auto x87_control_word : x87_control_words) {
        for (const auto mxcsr : rounding_modes) {
            for (const auto exponent_word : tail_exponents) {
                for (const auto mantissa : mantissas) {
                    for (const bool negative : {false, true}) {
                    std::array<std::uint8_t, 10> original_tail{};
                    std::array<std::uint8_t, 10> candidate_tail{};
                    const double tail_input = make_reduction_input(
                        exponent_word, mantissa, negative);
                    if (!invoke_caller_guarded(original_caller, tail_input, mxcsr,
                                               x87_control_word,
                                               original_tail.data()) ||
                        !invoke_caller_guarded(candidate_caller, tail_input, mxcsr,
                                               x87_control_word,
                                               candidate_tail.data())) return 9;
                    if (original_tail != candidate_tail) {
                        std::uint64_t input_bits = 0;
                        std::memcpy(&input_bits, &tail_input, sizeof(input_bits));
                        std::fwprintf(stderr,
                                      L"TAIL MISMATCH input=%016llX original={",
                                      static_cast<unsigned long long>(input_bits));
                        for (const auto byte : original_tail)
                            std::fwprintf(stderr, L"%02X", byte);
                        std::fwprintf(stderr, L"} candidate={");
                        for (const auto byte : candidate_tail)
                            std::fwprintf(stderr, L"%02X", byte);
                        std::fwprintf(stderr, L"}\n");
                        return 10;
                    }
                    ++tail_cases;
                    }
                }
            }
        }
    }

    constexpr std::uint32_t kTailRandomCasesPerMode = 1000;
    for (const auto x87_control_word : x87_control_words) {
        for (const auto mxcsr : rounding_modes) {
            std::uint32_t state = 0x7a11c60eu;
            for (std::uint32_t index = 0; index < kTailRandomCasesPerMode; ++index) {
            const auto exponent_word = static_cast<std::uint16_t>(
                0x40f6u + next_random(state) % 11u);
            const auto mantissa =
                (static_cast<std::uint64_t>(next_random(state)) << 16) |
                (next_random(state) & 0xffffu);
            const bool negative = (next_random(state) & 1u) != 0;
            std::array<std::uint8_t, 10> original_tail{};
            std::array<std::uint8_t, 10> candidate_tail{};
            const double tail_input = make_reduction_input(
                exponent_word, mantissa, negative);
            if (!invoke_caller_guarded(original_caller, tail_input, mxcsr,
                                       x87_control_word,
                                       original_tail.data()) ||
                !invoke_caller_guarded(candidate_caller, tail_input, mxcsr,
                                       x87_control_word,
                                       candidate_tail.data())) return 11;
            if (original_tail != candidate_tail) {
                std::uint64_t input_bits = 0;
                std::memcpy(&input_bits, &tail_input, sizeof(input_bits));
                std::fwprintf(stderr,
                              L"RANDOM TAIL MISMATCH input=%016llX original={",
                              static_cast<unsigned long long>(input_bits));
                for (const auto byte : original_tail)
                    std::fwprintf(stderr, L"%02X", byte);
                std::fwprintf(stderr, L"} candidate={");
                for (const auto byte : candidate_tail)
                    std::fwprintf(stderr, L"%02X", byte);
                std::fwprintf(stderr, L"}\n");
                return 12;
            }
            ++tail_cases;
            }
        }
    }

    std::wprintf(L"PASS: %u bit-exact normal-path results and %u bit-exact exception-tail results across all four MXCSR rounding modes through the original caller. Original base=%p candidate base=%p.\n",
                 case_number, tail_cases, original.module, candidate.module);
    return 0;
}
