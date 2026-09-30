#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" void __cdecl FUN_10006360(std::int32_t);
extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" long double __cdecl FUN_10010120(std::uint32_t, std::uint32_t);
long double __cdecl FUN_0053cc70(std::uint32_t, std::uint32_t);
void __cdecl FUN_007f18b0(std::int32_t, std::int32_t, std::int32_t);

std::int32_t DAT_1003c248{};
double _DAT_10024fa0 = 1.25;

struct Manager
{
    std::uint8_t reserved[0x48]{};
    std::uint32_t* pool{};
};

struct Event
{
    std::uint32_t kind{};
    std::uint32_t ecx{};
    std::uint32_t edx{};
    std::uint32_t a0{};
    std::uint32_t a1{};
    std::uint32_t a2{};
};

extern "C" {
Manager g_manager{};
std::uint32_t g_pool_table[1]{};
alignas(16) std::uint8_t g_pool_record[0x40]{};
alignas(16) std::uint8_t g_pool_info[0x520]{};
alignas(16) std::uint8_t g_vehicle[0xa18]{};
alignas(16) std::uint8_t g_sources[6][0x80]{};
alignas(16) std::uint8_t g_targets[6][0x100]{};
std::uint32_t g_vehicle_base_cell{};
std::uint32_t g_vehicle_base_pointer_cell{};
alignas(16) std::uint8_t g_engine_state[0x20]{};
Event g_events[32]{};
std::uint32_t g_event_count{};
std::uint32_t g_matrix_path_counts[3]{};
}

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000u;
constexpr std::uint32_t kGtaImageBase = 0x00400000u;
constexpr std::uint32_t kEntry = 0x10006360u;
constexpr std::size_t kOriginalSize = 0x426u;
constexpr std::size_t kCandidateSize = 0x3a5u;
constexpr std::array<std::uint32_t, 6> kVehicleSources = {
    0x650u, 0x65cu, 0x654u, 0x660u, 0x658u, 0x664u};
constexpr std::array<std::uint32_t, 6> kPoolOffsets = {
    0x4e8u, 0x4f0u, 0x4f8u, 0x500u, 0x508u, 0x510u};
std::uint8_t* g_gta_image{};

std::uint32_t Ptr32(void const* pointer)
{
    return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

bool PatchCall(std::uint8_t* image, std::uint32_t site,
               std::uint32_t expected_target, std::uint32_t replacement)
{
    auto* instruction = image + (site - kImageBase);
    if (instruction[0] != 0xe8)
        return false;
    std::int32_t displacement{};
    std::memcpy(&displacement, instruction + 1, sizeof(displacement));
    const auto actual = site + 5u + static_cast<std::uint32_t>(displacement);
    if (actual != expected_target)
        return false;
    const auto new_displacement = static_cast<std::int32_t>(
        replacement - (site + 5u));
    std::memcpy(instruction + 1, &new_displacement, sizeof(new_displacement));
    return true;
}

std::size_t ReplaceDword(std::uint8_t* bytes, std::size_t size,
                         std::uint32_t from, std::uint32_t to)
{
    std::size_t count = 0;
    for (std::size_t i = 0; i + sizeof(from) <= size; ++i)
    {
        std::uint32_t value{};
        std::memcpy(&value, bytes + i, sizeof(value));
        if (value == from)
        {
            std::memcpy(bytes + i, &to, sizeof(to));
            ++count;
            i += sizeof(from) - 1;
        }
    }
    return count;
}

std::uint8_t* MapImage(wchar_t const* path, std::uint32_t preferred_base,
                       bool use_preferred_base)
{
    HANDLE file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    LARGE_INTEGER file_size{};
    if (!GetFileSizeEx(file, &file_size) || file_size.QuadPart <= 0 ||
        file_size.QuadPart > 0x7fffffff)
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(static_cast<std::size_t>(file_size.QuadPart));
    DWORD read = 0;
    const BOOL read_ok = ReadFile(file, bytes.data(),
                                  static_cast<DWORD>(bytes.size()), &read, nullptr);
    CloseHandle(file);
    if (!read_ok || read != bytes.size() || bytes.size() < sizeof(IMAGE_DOS_HEADER))
        return nullptr;

    auto const* dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0 ||
        static_cast<std::size_t>(dos->e_lfanew) + sizeof(IMAGE_NT_HEADERS32) >
            bytes.size())
        return nullptr;
    auto const* nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC ||
        nt->OptionalHeader.ImageBase != preferred_base)
        return nullptr;

    void* const requested_base = use_preferred_base
        ? reinterpret_cast<void*>(preferred_base) : nullptr;
    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        requested_base, nt->OptionalHeader.SizeOfImage,
        MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
    if (!image || (use_preferred_base && image != requested_base))
    {
        std::fprintf(stderr,
                     "MapImage allocation failed: preferred=%08x fixed=%u actual=%p size=%08lx error=%lu\n",
                     preferred_base, use_preferred_base ? 1u : 0u, image,
                     nt->OptionalHeader.SizeOfImage,
                     GetLastError());
        return nullptr;
    }
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);
    auto const* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (section->SizeOfRawData == 0)
            continue;
        if (section->PointerToRawData > bytes.size() ||
            section->SizeOfRawData > bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData > nt->OptionalHeader.SizeOfImage -
                                         section->VirtualAddress)
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

bool RebaseGtaHelpers()
{
    constexpr std::uint32_t kAngleFunction = 0x0053cc70u;
    constexpr std::size_t kAngleFunctionSize = 0x146u;
    constexpr std::array<std::uint32_t, 6> kAbsoluteDataReferences = {
        0x00858b50u, 0x00858fe4u, 0x00858c1cu,
        0x00863ac4u, 0x00858cb8u, 0x00858cbcu};
    auto* const angle_code = g_gta_image + (kAngleFunction - kGtaImageBase);
    std::array<std::size_t, kAbsoluteDataReferences.size()> counts{};
    for (std::size_t i = 0; i < kAbsoluteDataReferences.size(); ++i)
    {
        const auto target = Ptr32(g_gta_image) +
            (kAbsoluteDataReferences[i] - kGtaImageBase);
        counts[i] = ReplaceDword(angle_code, kAngleFunctionSize,
                                 kAbsoluteDataReferences[i], target);
    }
    constexpr std::array<std::size_t, 6> expected = {7, 2, 4, 2, 2, 1};
    constexpr std::uint32_t kMatrixHelper = 0x007f18b0u;
    constexpr std::size_t kMatrixHelperSize = 0x6fu;
    auto* const matrix_code = g_gta_image + (kMatrixHelper - kGtaImageBase);
    const auto global_world = Ptr32(g_gta_image) + (0x00c979bcu - kGtaImageBase);
    const auto global_offset = Ptr32(g_gta_image) + (0x00c97b24u - kGtaImageBase);
    const auto world_count = ReplaceDword(matrix_code, kMatrixHelperSize,
                                          0x00c979bcu, global_world);
    const auto offset_count = ReplaceDword(matrix_code, kMatrixHelperSize,
                                           0x00c97b24u, global_offset);
    const auto engine_state = Ptr32(g_engine_state);
    const std::uint32_t world_flags = 0x00020000u;
    std::memcpy(g_gta_image + (0x00c979bcu - kGtaImageBase),
                &engine_state, sizeof(engine_state));
    std::memset(g_gta_image + (0x00c97b24u - kGtaImageBase), 0,
                sizeof(std::uint32_t));
    std::memcpy(g_engine_state + 4, &world_flags, sizeof(world_flags));
    return counts == expected && world_count == 1 && offset_count == 1;
}

void AddEvent(std::uint32_t kind, std::uint32_t ecx, std::uint32_t edx,
              std::uint32_t a0, std::uint32_t a1, std::uint32_t a2)
{
    if (g_event_count >= std::size(g_events))
        return;
    g_events[g_event_count++] = {kind, ecx, edx, a0, a1, a2};
}

void SetMemory(std::uint8_t* base, std::uint32_t offset, std::uint32_t value)
{
    std::memcpy(base + offset, &value, sizeof(value));
}

bool SafeInvoke(std::uint32_t address, std::int32_t argument, char const* label)
{
    __try
    {
        reinterpret_cast<void(__cdecl*)(std::int32_t)>(address)(argument);
        return true;
    }
    __except ((std::fprintf(stderr, "%s fault code=%08lx address=%p eax=%08lx ebx=%08lx ecx=%08lx edx=%08lx\n", label,
                            GetExceptionCode(),
                            GetExceptionInformation()->ExceptionRecord->ExceptionAddress,
                            GetExceptionInformation()->ContextRecord->Eax,
                            GetExceptionInformation()->ContextRecord->Ebx,
                            GetExceptionInformation()->ContextRecord->Ecx,
                            GetExceptionInformation()->ContextRecord->Edx),
              EXCEPTION_EXECUTE_HANDLER))
    {
        return false;
    }
}

void ResetFixture(std::uint32_t status, std::uint32_t disabled_sources,
                  std::uint32_t disabled_targets)
{
    std::memset(&g_manager, 0, sizeof(g_manager));
    std::memset(g_pool_table, 0, sizeof(g_pool_table));
    std::memset(g_pool_record, 0, sizeof(g_pool_record));
    std::memset(g_pool_info, 0, sizeof(g_pool_info));
    std::memset(g_vehicle, 0, sizeof(g_vehicle));
    std::memset(g_sources, 0, sizeof(g_sources));
    std::memset(g_targets, 0, sizeof(g_targets));
    g_event_count = 0;

    g_manager.pool = g_pool_table;
    g_pool_table[0] = Ptr32(g_pool_record);
    SetMemory(g_pool_record, 0x28, Ptr32(g_pool_info));
    g_vehicle_base_cell = Ptr32(g_vehicle);
    g_vehicle_base_pointer_cell = Ptr32(&g_vehicle_base_cell);
    std::memset(g_engine_state, 0, sizeof(g_engine_state));
    SetMemory(g_engine_state, 4, 0x00020000u);
    SetMemory(g_vehicle, 0x594, status);

    constexpr std::array<std::uint32_t, 6> kSpecialSources = {
        0x5b0u, 0x5b4u, 0u, 0u, 0u, 0u};
    for (std::uint32_t i = 0; i < 6; ++i)
    {
        const auto source_offset = (status == 9u || status == 10u)
            ? kSpecialSources[i] : kVehicleSources[i];
        const auto source = (disabled_sources & (1u << i))
            ? 0u : Ptr32(g_sources[i]);
        if (source_offset != 0)
            SetMemory(g_vehicle, source_offset, source);
        const auto target = (disabled_targets & (1u << i))
            ? 0u : Ptr32(g_targets[i]);
        SetMemory(g_pool_info, kPoolOffsets[i], target);

        const std::uint32_t x = 0x3f000000u + i * 0x1000u;
        const std::uint32_t y = 0x40000000u + i * 0x1000u;
        SetMemory(g_sources[i], 0x10, x);
        SetMemory(g_sources[i], 0x14, y);
        SetMemory(g_sources[i], 0x40, 0x11110000u + i);
        SetMemory(g_sources[i], 0x44, 0x22220000u + i);
        SetMemory(g_sources[i], 0x48, 0x33330000u + i);
        SetMemory(g_targets[i], 4, Ptr32(g_targets[(i + 1u) % 6u]));
        SetMemory(g_targets[i], 0x1c, (i & 1u) == 0 ? 0x00020000u : 0u);
    }
}

struct Snapshot
{
    std::array<Event, 32> events{};
    std::uint32_t event_count{};
    std::array<std::array<std::uint8_t, 0x100>, 6> targets{};
};

Snapshot Run(std::uint32_t address, std::uint32_t status,
             std::uint32_t disabled_sources, std::uint32_t disabled_targets)
{
    ResetFixture(status, disabled_sources, disabled_targets);
    if (!SafeInvoke(address, static_cast<std::int32_t>(Ptr32(g_vehicle)),
                    address == kEntry ? "original" : "candidate"))
        ExitProcess(3);
    Snapshot result{};
    result.event_count = g_event_count;
    std::memcpy(result.events.data(), g_events,
                result.events.size() * sizeof(Event));
    for (std::size_t i = 0; i < 6; ++i)
        std::memcpy(result.targets[i].data(), g_targets[i],
                    result.targets[i].size());
    return result;
}

bool Equal(Snapshot const& lhs, Snapshot const& rhs)
{
    return lhs.event_count == rhs.event_count &&
        std::memcmp(lhs.events.data(), rhs.events.data(),
                    lhs.event_count * sizeof(Event)) == 0 &&
        std::memcmp(lhs.targets.data(), rhs.targets.data(),
                    sizeof(lhs.targets)) == 0;
}

bool PatchOriginalAndCandidate(std::uint8_t* original,
                               std::uint32_t candidate_entry)
{
    const auto manager_stub = Ptr32(reinterpret_cast<void*>(&FUN_10009360));
    const auto original_rotate = Ptr32(
        g_gta_image + (0x0059b020u - kGtaImageBase));
    const auto original_angle = Ptr32(reinterpret_cast<void*>(&FUN_0053cc70));
    const auto original_triad = Ptr32(reinterpret_cast<void*>(&FUN_007f18b0));
    const auto original_vehicle_base = Ptr32(&g_vehicle_base_pointer_cell);

    DWORD old{};
    auto* candidate = reinterpret_cast<std::uint8_t*>(candidate_entry);
    if (!VirtualProtect(candidate, kCandidateSize, PAGE_EXECUTE_READWRITE, &old))
        return false;
    const auto candidate_rotate_sites = ReplaceDword(
        candidate, kCandidateSize, 0x0059b020u, original_rotate);
    const auto candidate_base_sites = ReplaceDword(
        candidate, kCandidateSize, 0x00b74494u, original_vehicle_base);
    VirtualProtect(candidate, kCandidateSize, old, &old);

    const auto entry = original + (kEntry - kImageBase);
    const auto original_rotate_sites = ReplaceDword(
        entry, kOriginalSize, 0x0059b020u, original_rotate);
    const auto original_angle_sites = ReplaceDword(
        entry, kOriginalSize, 0x0053cc70u, original_angle);
    const auto original_triad_sites = ReplaceDword(
        entry, kOriginalSize, 0x007f18b0u, original_triad);
    const auto original_base_sites = ReplaceDword(
        entry, kOriginalSize, 0x00b74494u, original_vehicle_base);
    const bool manager_call = PatchCall(original, 0x1000636fu,
                                        0x10009360u, manager_stub);
    const auto original_wrapper_angle_sites = ReplaceDword(
        original + (0x10010120u - kImageBase), 0x3fu,
        0x0053cc70u, original_angle);
    auto* const candidate_wrapper = reinterpret_cast<std::uint8_t*>(
        Ptr32(reinterpret_cast<void*>(&FUN_10010120)));
    DWORD wrapper_old{};
    if (!VirtualProtect(candidate_wrapper, 0x3fu, PAGE_EXECUTE_READWRITE,
                        &wrapper_old))
        return false;
    const auto candidate_wrapper_angle_sites = ReplaceDword(
        candidate_wrapper, 0x3fu, 0x0053cc70u, original_angle);
    VirtualProtect(candidate_wrapper, 0x3fu, wrapper_old, &wrapper_old);
    FlushInstructionCache(GetCurrentProcess(), entry, kOriginalSize);
    FlushInstructionCache(GetCurrentProcess(), candidate, kCandidateSize);
    FlushInstructionCache(GetCurrentProcess(), candidate_wrapper, 0x3fu);
    return candidate_rotate_sites == 7 && candidate_base_sites == 1 &&
        original_rotate_sites == 7 && original_angle_sites == 6 &&
        original_triad_sites == 7 && original_base_sites == 1 &&
        manager_call && original_wrapper_angle_sites == 1 &&
        candidate_wrapper_angle_sites == 1;
}
} // namespace

extern "C" std::int32_t __stdcall FUN_10009360()
{
    return static_cast<std::int32_t>(Ptr32(&g_manager));
}

long double __cdecl FUN_0053cc70(std::uint32_t a0, std::uint32_t a1)
{
    AddEvent(1, 0, 0, a0, a1, 0);
    using GtaAngleHelper = long double(__cdecl*)(std::uint32_t, std::uint32_t);
    const auto original = reinterpret_cast<GtaAngleHelper>(
        Ptr32(g_gta_image) + (0x0053cc70u - kGtaImageBase));
    return original(a0, a1);
}

void __cdecl FUN_007f18b0(std::int32_t a0, std::int32_t a1,
                         std::int32_t a2)
{
    const auto flags_second = *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(static_cast<std::uint32_t>(a1)) + 0x0cu);
    const auto flags_third = *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(static_cast<std::uint32_t>(a2)) + 0x0cu);
    const std::uint32_t path = (flags_second & 0x00020000u) != 0
        ? 0u : ((flags_third & 0x00020000u) != 0 ? 1u : 2u);
    ++g_matrix_path_counts[path];
    AddEvent(4u + path, 0, 0, static_cast<std::uint32_t>(a0),
             static_cast<std::uint32_t>(a1), static_cast<std::uint32_t>(a2));
    using GtaMatrixUpdate = void(__cdecl*)(std::int32_t, std::int32_t,
                                          std::int32_t);
    const auto original = reinterpret_cast<GtaMatrixUpdate>(
        Ptr32(g_gta_image) + (0x007f18b0u - kGtaImageBase));
    original(a0, a1, a2);
}

int wmain(int argc, wchar_t** argv)
{
    if (argc != 3)
    {
        std::fprintf(stderr,
                     "usage: runtime_10006360_differential <asi> <gta_sa.exe>\n");
        return 2;
    }
    auto* original = MapImage(argv[1], kImageBase, true);
    if (!original)
    {
        std::fprintf(stderr, "could not map pinned original ASI\n");
        return 2;
    }
    g_gta_image = MapImage(argv[2], kGtaImageBase, false);
    if (!g_gta_image || !RebaseGtaHelpers())
    {
        std::fprintf(stderr, "could not map/rebase GTA angle-helper image\n");
        return 2;
    }
    const auto candidate_entry = Ptr32(reinterpret_cast<void*>(&FUN_10006360));
    if (!PatchOriginalAndCandidate(original, candidate_entry))
    {
        std::fprintf(stderr, "original/candidate external-call patch count mismatch\n");
        return 2;
    }
    std::memcpy(original + (0x1003c248u - kImageBase), &DAT_1003c248,
                sizeof(DAT_1003c248));
    std::memcpy(original + (0x10024fa0u - kImageBase), &_DAT_10024fa0,
                sizeof(_DAT_10024fa0));

    std::uint32_t cases = 0;
    constexpr std::array<std::uint32_t, 4> normal_statuses = {0, 1, 2, 0xb};
    for (const auto status : normal_statuses)
    {
        for (std::uint32_t source_mask = 0; source_mask < 64; ++source_mask)
        {
            for (std::uint32_t target_mask : {0u, 21u, 42u, 63u})
            {
                const auto reference = Run(kEntry, status, source_mask, target_mask);
                const auto candidate = Run(candidate_entry, status, source_mask,
                                           target_mask);
                ++cases;
                if (!Equal(reference, candidate))
                {
                    std::fprintf(stderr,
                        "mismatch status=%u source-mask=%02x target-mask=%02x events=%u/%u\n",
                        status, source_mask, target_mask,
                        reference.event_count, candidate.event_count);
                    return 1;
                }
            }
        }
    }
    constexpr std::array<std::uint32_t, 2> special_statuses = {9, 10};
    for (const auto status : special_statuses)
    {
        for (std::uint32_t source_mask = 0; source_mask < 4; ++source_mask)
        {
            for (std::uint32_t target_mask : {0u, 16u, 32u, 48u})
            {
                const auto reference = Run(kEntry, status, source_mask, target_mask);
                const auto candidate = Run(candidate_entry, status, source_mask,
                                           target_mask);
                ++cases;
                if (!Equal(reference, candidate))
                {
                    std::fprintf(stderr,
                        "mismatch status=%u source-mask=%02x target-mask=%02x events=%u/%u\n",
                        status, source_mask, target_mask,
                        reference.event_count, candidate.event_count);
                    return 1;
                }
            }
        }
    }
    for (const auto status : {3u, 8u, 12u})
    {
        const auto reference = Run(kEntry, status, 0, 0);
        const auto candidate = Run(candidate_entry, status, 0, 0);
        ++cases;
        if (!Equal(reference, candidate))
        {
            std::fprintf(stderr, "unsupported-status mismatch status=%u\n", status);
            return 1;
        }
    }
    if (g_matrix_path_counts[0] == 0 || g_matrix_path_counts[1] == 0 ||
        g_matrix_path_counts[2] != 0)
    {
        std::fprintf(stderr,
            "matrix helper branch coverage unexpected: first=%u second=%u fallback=%u\n",
            g_matrix_path_counts[0], g_matrix_path_counts[1],
            g_matrix_path_counts[2]);
        return 1;
    }
    std::printf("10006360 mapped original/candidate differential: %u/%u cases passed; real matrix-helper branches=%u/%u; fallback=%u\n",
                cases, cases, g_matrix_path_counts[0],
                g_matrix_path_counts[1], g_matrix_path_counts[2]);
    return 0;
}
