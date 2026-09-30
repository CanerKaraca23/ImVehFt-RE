#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" void __cdecl __initterm_e(std::uint32_t*, std::uint32_t*);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kOriginalEntry = 0x10012be1;
constexpr std::size_t kMaxTable = 32;
constexpr std::size_t kCallbackCount = 8;

struct Invocation
{
    std::int32_t esp_after_call;
    std::int32_t esp_after_caller_cleanup;
};

struct Capture
{
    std::array<std::uint32_t, kMaxTable> calls{};
    std::uint32_t call_count = 0;
    Invocation invocation{};
};

struct Mutation
{
    bool enabled = false;
    std::uint32_t mutator_id = 0;
    std::size_t slot = 0;
    std::uint32_t replacement = 0;
};

volatile std::uint32_t g_esp_before = 0;
std::array<int, kCallbackCount> g_returns{};
std::array<std::uint32_t, kMaxTable> g_call_log{};
std::uint32_t g_call_count = 0;
std::uint32_t* g_active_table = nullptr;
std::size_t g_active_table_size = 0;
Mutation g_mutation{};

void Record(std::uint32_t id)
{
    if (g_call_count < g_call_log.size())
        g_call_log[g_call_count++] = id;
    if (g_mutation.enabled && id == g_mutation.mutator_id &&
        g_mutation.slot < g_active_table_size)
        g_active_table[g_mutation.slot] = g_mutation.replacement;
}

template <std::uint32_t Id>
__declspec(noinline) int __cdecl Callback()
{
    Record(Id);
    return g_returns[Id];
}

using CallbackFunction = int(__cdecl*)();
constexpr std::array<CallbackFunction, kCallbackCount> kCallbacks = {
    &Callback<0>, &Callback<1>, &Callback<2>, &Callback<3>,
    &Callback<4>, &Callback<5>, &Callback<6>, &Callback<7>};

std::array<std::uint32_t, kCallbackCount> CallbackAddresses()
{
    std::array<std::uint32_t, kCallbackCount> result{};
    for (std::size_t i = 0; i < result.size(); ++i)
        result[i] = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(kCallbacks[i]));
    return result;
}

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, std::uint32_t*, std::uint32_t*, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ecx], edx
        add esp, 8
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov dword ptr [ecx + 4], edx
        pop ebp
        ret
    }
}

std::uint8_t* MapReference(char const* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    DWORD const size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(size);
    DWORD read = 0;
    BOOL const ok = ReadFile(file, bytes.data(), size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size)
        return nullptr;

    auto const* dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0 ||
        static_cast<std::size_t>(dos->e_lfanew) + sizeof(IMAGE_NT_HEADERS32) > bytes.size())
        return nullptr;
    auto const* nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase)
        return nullptr;

    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kImageBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kImageBase)))
        return nullptr;
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);

    auto const* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (!section->SizeOfRawData)
            continue;
        if (section->PointerToRawData > bytes.size() ||
            section->SizeOfRawData > bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData >
                nt->OptionalHeader.SizeOfImage - section->VirtualAddress)
        {
            VirtualFree(image, 0, MEM_RELEASE);
            return nullptr;
        }
        std::memcpy(image + section->VirtualAddress,
                    bytes.data() + section->PointerToRawData,
                    section->SizeOfRawData);
    }
    return image;
}

Capture Run(std::uint32_t function, std::vector<std::uint32_t>& table,
            std::array<int, kCallbackCount> const& returns,
            Mutation const& mutation)
{
    g_returns = returns;
    g_call_log = {};
    g_call_count = 0;
    g_active_table = table.data();
    g_active_table_size = table.size();
    g_mutation = mutation;

    Capture capture{};
    std::uint32_t* const first = table.data();
    std::uint32_t* const last = table.data() + table.size();
    InvokeRaw(function, first, last, &capture.invocation);
    capture.call_count = g_call_count;
    for (std::uint32_t i = 0; i < capture.call_count; ++i)
        capture.calls[i] = g_call_log[i];
    return capture;
}

std::uint32_t CallbackId(std::uint32_t value,
                         std::array<std::uint32_t, kCallbackCount> const& addresses)
{
    for (std::uint32_t i = 0; i < addresses.size(); ++i)
        if (addresses[i] == value)
            return i;
    return 0xffffffffu;
}

std::vector<std::uint32_t> Expected(std::vector<std::uint32_t>& table,
                                    std::array<int, kCallbackCount> const& returns,
                                    Mutation const& mutation,
                                    std::array<std::uint32_t, kCallbackCount> const& addresses)
{
    std::vector<std::uint32_t> calls;
    for (std::size_t index = 0; index < table.size(); ++index)
    {
        std::uint32_t const entry = table[index];
        if (!entry)
            continue;
        std::uint32_t const id = CallbackId(entry, addresses);
        if (id == 0xffffffffu)
            return {0xfffffffeu};
        calls.push_back(id);
        if (mutation.enabled && id == mutation.mutator_id &&
            mutation.slot < table.size())
            table[mutation.slot] = mutation.replacement;
        if (returns[id] != 0)
            break;
    }
    return calls;
}

bool CheckCase(std::uint32_t candidate_address,
               std::array<std::uint32_t, kCallbackCount> const& addresses,
               std::vector<std::uint32_t> initial,
               std::array<int, kCallbackCount> const& returns,
               Mutation const& mutation)
{
    std::vector<std::uint32_t> original_table = initial;
    std::vector<std::uint32_t> candidate_table = initial;
    std::vector<std::uint32_t> expected_table = initial;
    std::vector<std::uint32_t> const expected_calls =
        Expected(expected_table, returns, mutation, addresses);
    if (expected_calls.size() == 1 && expected_calls[0] == 0xfffffffeu)
        return false;

    Capture const original = Run(kOriginalEntry, original_table, returns, mutation);
    Capture const candidate = Run(candidate_address, candidate_table, returns, mutation);
    if (original.call_count != expected_calls.size() ||
        candidate.call_count != expected_calls.size() ||
        original_table != expected_table || candidate_table != expected_table ||
        original.invocation.esp_after_call != -8 ||
        candidate.invocation.esp_after_call != -8 ||
        original.invocation.esp_after_caller_cleanup != 0 ||
        candidate.invocation.esp_after_caller_cleanup != 0)
        return false;

    for (std::size_t i = 0; i < expected_calls.size(); ++i)
        if (original.calls[i] != expected_calls[i] ||
            candidate.calls[i] != expected_calls[i])
            return false;
    return true;
}

std::uint32_t NextRandom(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}
} // namespace

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "Run this harness as PE32/x86.");
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <ImVehFt.asi>\n");
        return 2;
    }
    auto* const reference = MapReference(argv[1]);
    if (!reference)
    {
        std::fprintf(stderr, "Could not map original ImVehFt PE at its preferred base.\n");
        return 3;
    }

    auto const addresses = CallbackAddresses();
    auto const candidate_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&__initterm_e));
    std::uint64_t cases = 0;
    auto run = [&](std::vector<std::uint32_t> table,
                   std::array<int, kCallbackCount> returns,
                   Mutation mutation = {}) {
        ++cases;
        return CheckCase(candidate_address, addresses, std::move(table),
                         returns, mutation);
    };

    std::array<int, kCallbackCount> returns{};
    if (!run({}, returns) || !run({0, 0, 0, 0}, returns))
    {
        VirtualFree(reference, 0, MEM_RELEASE);
        return 4;
    }

    std::vector<std::uint32_t> all_success(addresses.begin(), addresses.end());
    if (!run(all_success, returns))
    {
        VirtualFree(reference, 0, MEM_RELEASE);
        return 5;
    }
    returns[0] = 1;
    returns[3] = -1;
    returns[6] = 0x1234;
    if (!run({addresses[0], addresses[1], addresses[2]}, returns) ||
        !run({0, 0, addresses[3], addresses[4], addresses[5]}, returns) ||
        !run({addresses[1], addresses[2], addresses[3], addresses[4]}, returns))
    {
        VirtualFree(reference, 0, MEM_RELEASE);
        return 6;
    }

    returns = {};
    Mutation mutation{true, 0, 2, addresses[5]};
    if (!run({addresses[0], addresses[1], 0, addresses[3]}, returns, mutation))
    {
        VirtualFree(reference, 0, MEM_RELEASE);
        return 7;
    }

    std::uint32_t random = 0xa341316cu;
    constexpr std::uint32_t kRandomCases = 100000;
    for (std::uint32_t test = 0; test < kRandomCases; ++test)
    {
        std::uint32_t const length = NextRandom(random) % (kMaxTable + 1);
        std::vector<std::uint32_t> table(length);
        for (std::uint32_t i = 0; i < length; ++i)
        {
            std::uint32_t const choice = NextRandom(random) % 10;
            table[i] = choice < 3 ? 0 : addresses[NextRandom(random) % addresses.size()];
        }
        std::array<int, kCallbackCount> random_returns{};
        for (int& result : random_returns)
        {
            std::uint32_t const choice = NextRandom(random) % 5;
            result = choice < 3 ? 0 : (choice == 3 ? -1 : static_cast<int>(NextRandom(random) | 1u));
        }
        Mutation random_mutation{};
        if ((NextRandom(random) & 7u) == 0 && length > 0)
        {
            random_mutation.enabled = true;
            random_mutation.mutator_id = NextRandom(random) % addresses.size();
            random_mutation.slot = NextRandom(random) % length;
            random_mutation.replacement = addresses[NextRandom(random) % addresses.size()];
        }
        if (!run(std::move(table), random_returns, random_mutation))
        {
            std::fprintf(stderr, "Differential mismatch at randomized case %u.\n", test);
            VirtualFree(reference, 0, MEM_RELEASE);
            return 8;
        }
    }

    VirtualFree(reference, 0, MEM_RELEASE);
    std::printf("PASS: %llu original/candidate/oracle callback-table cases; %u deterministic randomized tables, with order, early-stop, null-entry, mutation, and cdecl stack behavior matched.\n",
                static_cast<unsigned long long>(cases), kRandomCases);
    std::puts("LIMIT: callback functions were controlled test stubs; real CRT initialization and GTA startup were not exercised.");
    return 0;
}
