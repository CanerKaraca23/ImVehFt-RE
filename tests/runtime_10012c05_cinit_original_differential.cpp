#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" int __cdecl __cinit(int);
extern "C" void __stdcall FUN_10016cec();

using FpmathFunction = void(__cdecl*)(int);
using RuntimeFunction = void(__stdcall*)(int, int, int);
extern "C" FpmathFunction PTR___fpmath_10025004;
extern "C" std::uint32_t DAT_100221b8[];
extern "C" std::uint32_t DAT_100221d0[];
extern "C" std::uint32_t DAT_10022154[];
extern "C" std::uint32_t DAT_100221b4[];
extern "C" RuntimeFunction DAT_1003d554;

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kOriginalEntry = 0x10012c05;
constexpr std::uint32_t kOriginalFpmathSlot = 0x10025004;
constexpr std::uint32_t kOriginalRuntimeSlot = 0x1003d554;
constexpr std::size_t kPreinitCount = 6;
constexpr std::size_t kRuntimeInitCount = 24;
constexpr std::size_t kMaxTrace = 128;

struct Event
{
    std::uint32_t kind;
    std::uint32_t value;
};

struct Invocation
{
    std::int32_t esp_after_call;
    std::int32_t esp_after_caller_cleanup;
    std::int32_t result;
};

struct Scenario
{
    int parameter = 0;
    bool fpmath_present = false;
    bool fpmath_nonwritable = false;
    bool runtime_callback_present = false;
    bool runtime_callback_nonwritable = false;
    std::array<int, kPreinitCount> preinit_ids{};
    std::array<int, kRuntimeInitCount> runtime_ids{};
    std::array<int, kPreinitCount> preinit_results{};
};

struct Capture
{
    std::array<Event, kMaxTrace> events{};
    std::uint32_t event_count = 0;
    Invocation invocation{};
};

volatile std::uint32_t g_esp_before = 0;
std::array<std::uint32_t, 8> g_callback_addresses{};
Scenario g_scenario{};
std::array<Event, kMaxTrace> g_events{};
std::uint32_t g_event_count = 0;

void Log(std::uint32_t kind, std::uint32_t value = 0)
{
    if (g_event_count < g_events.size())
        g_events[g_event_count++] = {kind, value};
}

template <std::uint32_t Id>
__declspec(noinline) int __cdecl PreinitCallback()
{
    Log(0x100u + Id);
    return g_scenario.preinit_results[Id];
}

template <std::uint32_t Id>
__declspec(noinline) void __cdecl RuntimeInitializer()
{
    Log(0x200u + Id);
}

using PreinitFunction = int(__cdecl*)();
using InitializerFunction = void(__cdecl*)();
constexpr std::array<PreinitFunction, kPreinitCount> kPreinitCallbacks = {
    &PreinitCallback<0>, &PreinitCallback<1>, &PreinitCallback<2>,
    &PreinitCallback<3>, &PreinitCallback<4>, &PreinitCallback<5>};
constexpr std::array<InitializerFunction, 8> kRuntimeCallbacks = {
    &RuntimeInitializer<0>, &RuntimeInitializer<1>,
    &RuntimeInitializer<2>, &RuntimeInitializer<3>,
    &RuntimeInitializer<4>, &RuntimeInitializer<5>,
    &RuntimeInitializer<6>, &RuntimeInitializer<7>};

std::uint32_t AddressOf(PreinitFunction function)
{
    return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(function));
}

std::uint32_t AddressOf(InitializerFunction function)
{
    return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(function));
}

void __cdecl FpmathCallback(int parameter)
{
    Log(0x10, static_cast<std::uint32_t>(parameter));
}

void __stdcall RuntimeCallback(int first, int second, int third)
{
    Log(0x30, (static_cast<std::uint32_t>(first) << 16) |
                  (static_cast<std::uint32_t>(second) << 8) |
                  static_cast<std::uint32_t>(third));
}

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, int, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov ecx, dword ptr [ebp + 10h]
        mov dword ptr [ecx + 8], eax
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov dword ptr [ecx], edx
        add esp, 4
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov dword ptr [ecx + 4], edx
        pop ebp
        ret
    }
}

int ReportException(EXCEPTION_POINTERS const* info)
{
    std::fprintf(stderr,
                 "SEH exception=0x%08lx address=%p EIP=0x%08lx ESP=0x%08lx EBP=0x%08lx events=%lu\n",
                 info->ExceptionRecord->ExceptionCode,
                 info->ExceptionRecord->ExceptionAddress,
                 info->ContextRecord->Eip, info->ContextRecord->Esp,
                 info->ContextRecord->Ebp, g_event_count);
    auto const* const stack = reinterpret_cast<std::uint32_t const*>(
        info->ContextRecord->Esp);
    std::fprintf(stderr, "stack=%08lx,%08lx,%08lx,%08lx trace:",
                 stack[0], stack[1], stack[2], stack[3]);
    for (std::uint32_t i = 0; i < g_event_count && i < 40; ++i)
        std::fprintf(stderr, " %lx:%lx", g_events[i].kind, g_events[i].value);
    std::fputc('\n', stderr);
    return EXCEPTION_EXECUTE_HANDLER;
}

bool TryInvoke(std::uint32_t function, int parameter, Invocation* invocation)
{
    __try
    {
        InvokeRaw(function, parameter, invocation);
        return true;
    }
    __except (ReportException(GetExceptionInformation()))
    {
        return false;
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

bool RedirectCall(std::uint8_t* image, std::uint32_t call_va,
                  std::uint32_t expected_target, std::uintptr_t replacement)
{
    auto* const call = image + (call_va - kImageBase);
    if (call[0] != 0xe8)
        return false;
    std::int32_t old_relative = 0;
    std::memcpy(&old_relative, call + 1, sizeof(old_relative));
    if (static_cast<std::int64_t>(call_va) + 5 + old_relative != expected_target)
        return false;
    auto const new_relative = static_cast<std::int32_t>(
        replacement - reinterpret_cast<std::uintptr_t>(call + 5));
    std::memcpy(call + 1, &new_relative, sizeof(new_relative));
    return true;
}

extern "C" int __cdecl CinitNonwritableStub(std::uint8_t* address)
{
    std::uintptr_t const value = reinterpret_cast<std::uintptr_t>(address);
    if (value == kOriginalFpmathSlot || value ==
        reinterpret_cast<std::uintptr_t>(&PTR___fpmath_10025004))
    {
        Log(0x01);
        return g_scenario.fpmath_nonwritable ? 1 : 0;
    }
    if (value == kOriginalRuntimeSlot || value ==
        reinterpret_cast<std::uintptr_t>(&DAT_1003d554))
    {
        Log(0x02);
        return g_scenario.runtime_callback_nonwritable ? 1 : 0;
    }
    Log(0xff, static_cast<std::uint32_t>(value));
    return 0;
}

extern "C" void __stdcall CinitInitpStub()
{
    Log(0x20);
}

extern "C" int __cdecl CinitAtexitStub(void(__cdecl* function)())
{
    std::uintptr_t const value = reinterpret_cast<std::uintptr_t>(function);
    bool const expected = value == 0x10016cecu || value ==
        reinterpret_cast<std::uintptr_t>(&FUN_10016cec);
    Log(0x21, expected ? 1u : 0u);
    return 0;
}

extern "C" void __stdcall FUN_10016cec()
{
    Log(0x22);
}

void StoreOriginalTables(std::uint8_t* image, Scenario const& scenario)
{
    auto* preinit = reinterpret_cast<std::uint32_t*>(image + 0x221b8);
    auto* runtime = reinterpret_cast<std::uint32_t*>(image + 0x22154);
    for (std::size_t i = 0; i < kPreinitCount; ++i)
        preinit[i] = scenario.preinit_ids[i] < 0 ? 0u :
            AddressOf(kPreinitCallbacks[static_cast<std::size_t>(scenario.preinit_ids[i])]);
    for (std::size_t i = 0; i < kRuntimeInitCount; ++i)
        runtime[i] = scenario.runtime_ids[i] < 0 ? 0u :
            AddressOf(kRuntimeCallbacks[static_cast<std::size_t>(scenario.runtime_ids[i]) % kRuntimeCallbacks.size()]);
    *reinterpret_cast<std::uint32_t*>(image + 0x25004) = scenario.fpmath_present ?
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&FpmathCallback)) : 0u;
    *reinterpret_cast<std::uint32_t*>(image + 0x3d554) = scenario.runtime_callback_present ?
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RuntimeCallback)) : 0u;
}

void StoreCandidateTables(Scenario const& scenario)
{
    for (std::size_t i = 0; i < kPreinitCount; ++i)
        DAT_100221b8[i] = scenario.preinit_ids[i] < 0 ? 0u :
            AddressOf(kPreinitCallbacks[static_cast<std::size_t>(scenario.preinit_ids[i])]);
    for (std::size_t i = 0; i < kRuntimeInitCount; ++i)
        DAT_10022154[i] = scenario.runtime_ids[i] < 0 ? 0u :
            AddressOf(kRuntimeCallbacks[static_cast<std::size_t>(scenario.runtime_ids[i]) % kRuntimeCallbacks.size()]);
    PTR___fpmath_10025004 = scenario.fpmath_present ? &FpmathCallback : nullptr;
    DAT_1003d554 = scenario.runtime_callback_present ? &RuntimeCallback : nullptr;
}

Capture Run(std::uint32_t function, int parameter)
{
    g_event_count = 0;
    Capture result{};
    if (!TryInvoke(function, parameter, &result.invocation))
        std::exit(4);
    result.event_count = g_event_count;
    for (std::uint32_t i = 0; i < result.event_count; ++i)
        result.events[i] = g_events[i];
    return result;
}

std::vector<Event> Expected(Scenario const& scenario, int& result)
{
    std::vector<Event> events;
    if (scenario.fpmath_present)
    {
        events.push_back({0x01, 0});
        if (scenario.fpmath_nonwritable)
            events.push_back({0x10, static_cast<std::uint32_t>(scenario.parameter)});
    }
    events.push_back({0x20, 0});

    result = 0;
    for (int id : scenario.preinit_ids)
    {
        if (id < 0)
            continue;
        events.push_back({0x100u + static_cast<std::uint32_t>(id), 0});
        if (scenario.preinit_results[static_cast<std::size_t>(id)] != 0)
        {
            result = scenario.preinit_results[static_cast<std::size_t>(id)];
            break;
        }
    }
    if (result != 0)
        return events;

    events.push_back({0x21, 1});
    for (int id : scenario.runtime_ids)
        if (id >= 0)
            events.push_back({0x200u + static_cast<std::uint32_t>(id % 8), 0});

    if (scenario.runtime_callback_present)
    {
        events.push_back({0x02, 0});
        if (scenario.runtime_callback_nonwritable)
            events.push_back({0x30, 0x200});
    }
    return events;
}

bool Same(Capture const& capture, std::vector<Event> const& expected, int result)
{
    if (capture.event_count != expected.size() || capture.invocation.result != result ||
        capture.invocation.esp_after_call != -4 ||
        capture.invocation.esp_after_caller_cleanup != 0)
        return false;
    for (std::size_t i = 0; i < expected.size(); ++i)
        if (capture.events[i].kind != expected[i].kind ||
            capture.events[i].value != expected[i].value)
            return false;
    return true;
}

bool CheckScenario(std::uint8_t* image, Scenario const& scenario)
{
    g_scenario = scenario;
    StoreOriginalTables(image, scenario);
    StoreCandidateTables(scenario);

    int expected_result = 0;
    std::vector<Event> const expected = Expected(scenario, expected_result);
    Capture const original = Run(kOriginalEntry, scenario.parameter);
    Capture const candidate = Run(static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&__cinit)), scenario.parameter);
    return Same(original, expected, expected_result) &&
           Same(candidate, expected, expected_result);
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

    auto* const image = MapReference(argv[1]);
    if (!image ||
        !RedirectCall(image, 0x10012c18, 0x10018120,
                      reinterpret_cast<std::uintptr_t>(static_cast<int(__cdecl*)(std::uint8_t*)>(&CinitNonwritableStub))) ||
        !RedirectCall(image, 0x10012c2c, 0x10017a33,
                      reinterpret_cast<std::uintptr_t>(static_cast<void(__stdcall*)()>(&CinitInitpStub))) ||
        !RedirectCall(image, 0x10012c4d, 0x10010529,
                      reinterpret_cast<std::uintptr_t>(static_cast<int(__cdecl*)(void(__cdecl*)())>(&CinitAtexitStub))) ||
        !RedirectCall(image, 0x10012c82, 0x10018120,
                      reinterpret_cast<std::uintptr_t>(static_cast<int(__cdecl*)(std::uint8_t*)>(&CinitNonwritableStub))))
    {
        std::fprintf(stderr, "Could not map image or verify original __cinit call sites.\n");
        if (image)
            VirtualFree(image, 0, MEM_RELEASE);
        return 3;
    }

    std::uint64_t cases = 0;
    auto run = [&](Scenario const& scenario) {
        ++cases;
        return CheckScenario(image, scenario);
    };

    Scenario success{};
    success.parameter = 0x12345678;
    success.fpmath_present = true;
    success.fpmath_nonwritable = true;
    success.runtime_callback_present = true;
    success.runtime_callback_nonwritable = true;
    success.preinit_ids = {0, -1, 1, 2, -1, 3};
    success.runtime_ids = {0, -1, 1, 2, 3, -1, 4, 5, 6, 7, -1, 0,
                           1, 2, 3, 4, 5, 6, 7, 0, -1, 1, 2, 3};
    if (!run(success))
    {
        VirtualFree(image, 0, MEM_RELEASE);
        return 4;
    }

    Scenario preinit_failure = success;
    preinit_failure.preinit_results[2] = 0x1234;
    if (!run(preinit_failure))
    {
        VirtualFree(image, 0, MEM_RELEASE);
        return 5;
    }
    Scenario early_failure = success;
    early_failure.preinit_results[0] = -1;
    if (!run(early_failure))
    {
        VirtualFree(image, 0, MEM_RELEASE);
        return 6;
    }
    Scenario no_fpmath = success;
    no_fpmath.fpmath_present = false;
    if (!run(no_fpmath))
    {
        VirtualFree(image, 0, MEM_RELEASE);
        return 7;
    }
    Scenario writable_callbacks = success;
    writable_callbacks.fpmath_nonwritable = false;
    writable_callbacks.runtime_callback_nonwritable = false;
    if (!run(writable_callbacks))
    {
        VirtualFree(image, 0, MEM_RELEASE);
        return 8;
    }

    std::uint32_t random = 0x243f6a88u;
    constexpr std::uint32_t kRandomCases = 10000;
    for (std::uint32_t test = 0; test < kRandomCases; ++test)
    {
        Scenario scenario{};
        scenario.parameter = static_cast<int>(NextRandom(random));
        scenario.fpmath_present = (NextRandom(random) & 1u) != 0;
        scenario.fpmath_nonwritable = (NextRandom(random) & 1u) != 0;
        scenario.runtime_callback_present = (NextRandom(random) & 1u) != 0;
        scenario.runtime_callback_nonwritable = (NextRandom(random) & 1u) != 0;
        for (int& id : scenario.preinit_ids)
        {
            std::uint32_t const choice = NextRandom(random) % 5;
            id = choice == 0 ? -1 : static_cast<int>((choice - 1) % kPreinitCount);
        }
        for (int& id : scenario.runtime_ids)
        {
            std::uint32_t const choice = NextRandom(random) % 5;
            id = choice == 0 ? -1 : static_cast<int>((choice - 1) % 8);
        }
        for (int& result : scenario.preinit_results)
        {
            std::uint32_t const choice = NextRandom(random) % 5;
            result = choice < 3 ? 0 : (choice == 3 ? -1 : static_cast<int>(NextRandom(random) | 1u));
        }
        if (!run(scenario))
        {
            std::fprintf(stderr, "__cinit mismatch at randomized case %u.\n", test);
            VirtualFree(image, 0, MEM_RELEASE);
            return 9;
        }
    }

    VirtualFree(image, 0, MEM_RELEASE);
    std::printf("PASS: %llu original/candidate/oracle __cinit cases; %u randomized initializer configurations; callback order, early failure, writability gates, return, and cdecl stack matched.\n",
                static_cast<unsigned long long>(cases), kRandomCases);
    std::puts("LIMIT: CRT service routines and callbacks were controlled stubs; actual process startup and GTA were not exercised.");
    return 0;
}
