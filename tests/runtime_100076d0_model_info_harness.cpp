#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" int* __cdecl FUN_100076d0(int*, int*);
extern "C" std::int32_t __stdcall FUN_10008e00();
extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" std::uint32_t* __cdecl FUN_10001fb0(std::uint32_t*);
using ReentryFunction = int*(__cdecl*)(int*, int*);

std::int32_t DAT_1003c248 = 0;
std::int32_t DAT_1003c1fc = 0;
float _DAT_1003c1ec = 1.0f;
std::int32_t DAT_1003aef4 = 0;
std::uintptr_t DAT_1003759c = 0;
std::uintptr_t DAT_1003aacc = 0;
std::int32_t _DAT_10024f08 = 1;
std::int32_t DAT_1003bd9c = 0;
std::int32_t DAT_10024a14 = 0;
std::int32_t DAT_10024f90 = 0;
std::int32_t _DAT_10024f90 = 0;
std::int32_t _DAT_10024f94 = 0;
float _DAT_10024e90 = 0.0f;
std::int32_t DAT_1003c250 = 0;
std::int32_t DAT_1003c254 = 0;
std::int32_t _DAT_1003bc00 = 0;
std::int32_t DAT_1003bc78 = 0;
char DAT_1003aef0 = 0;
char DAT_1003aeec = 0;
char DAT_1003aef1 = 0;
std::uint8_t DAT_1003aedc[0x12] = {};
std::uint32_t DAT_100374c0[0x12] = {};
std::int32_t* DAT_10037594 = nullptr;
std::int32_t* _DAT_1003c1a8 = nullptr;
std::int32_t* _DAT_1003bbc0 = nullptr;
std::int32_t* _DAT_1003bc30 = nullptr;
std::int32_t* _DAT_1003c208 = nullptr;

namespace
{
void* g_context = nullptr;
int g_context_calls = 0;
int g_texture_lookup_calls = 0;
int g_texture_lookup_model_ids[8] = {};
char g_texture_lookup_names[8][32] = {};
int g_vehiclelights_lookup_result = 0;
int g_vehiclelights_dam_lookup_result = 0;
void* g_vehicle_system = nullptr;
int g_vehicle_system_calls = 0;
int g_texture_callback_calls = 0;
int g_texture_callback_value = 0;
int* g_texture_callback_parameters = nullptr;
bool g_callback_reentry_enabled = false;
bool g_inside_texture_callback = false;
bool g_callback_reentry_passed = false;
ReentryFunction g_callback_reentry_function = nullptr;
bool g_flip_vehicle_context_on_callback = false;
std::int32_t g_callback_vehicle_context = 0;

void* AllocateLow(std::size_t size)
{
    void* value = VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT,
                               PAGE_READWRITE);
    if (value == nullptr || reinterpret_cast<std::uintptr_t>(value) > 0x7fffffff)
        return nullptr;
    return value;
}

int Fail(const char* message)
{
    std::fprintf(stderr, "FAIL: %s\n", message);
    return 1;
}

int __cdecl TextureLookupStub(int model_id, const char* name)
{
    const int call = g_texture_lookup_calls++;
    if (call < 8)
    {
        g_texture_lookup_model_ids[call] = model_id;
        strncpy_s(g_texture_lookup_names[call],
                  sizeof(g_texture_lookup_names[call]), name, _TRUNCATE);
    }
    if (std::strcmp(name, "vehiclelights") == 0)
        return g_vehiclelights_lookup_result;
    if (std::strcmp(name, "vehiclelights_dam") == 0)
        return g_vehiclelights_dam_lookup_result;
    return 0;
}

void __cdecl TextureCallbackStub(int* parameters, std::int32_t value)
{
    ++g_texture_callback_calls;
    g_texture_callback_parameters = parameters;
    g_texture_callback_value = value;
    if (g_flip_vehicle_context_on_callback)
        DAT_1003c1fc = g_callback_vehicle_context;
    if (!g_callback_reentry_enabled || g_inside_texture_callback)
        return;

    g_inside_texture_callback = true;
    int nested_input[6] = {0, 0x000000f5, 0, 0, 0, 0};
    std::uintptr_t nested_slots[4] = {};
    int nested_cursor = static_cast<int>(
        reinterpret_cast<std::uintptr_t>(nested_slots));
    const auto reentry_function = g_callback_reentry_function != nullptr
                                      ? g_callback_reentry_function
                                      : &FUN_100076d0;
    int* nested_result = reentry_function(nested_input, &nested_cursor);
    g_callback_reentry_passed =
        nested_result == nested_input &&
        nested_slots[0] == reinterpret_cast<std::uintptr_t>(nested_input + 1) &&
        nested_slots[1] == 0x000000f5 &&
        nested_cursor == static_cast<int>(
                             reinterpret_cast<std::uintptr_t>(nested_slots + 2)) &&
        (static_cast<std::uint32_t>(nested_input[1]) & 0xffff) == 0xabcd + 10 &&
        reinterpret_cast<std::uint8_t*>(nested_input)[6] == 0x40 + 10;
    g_inside_texture_callback = false;
}

int LogCandidateException(EXCEPTION_POINTERS* exception)
{
    HMODULE module = nullptr;
    const auto address = reinterpret_cast<LPCSTR>(
        exception->ContextRecord->Eip);
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       address, &module);
    char module_path[MAX_PATH] = {};
    if (module != nullptr)
        GetModuleFileNameA(module, module_path, MAX_PATH);
    std::fprintf(stderr, "candidate exception 0x%08lx at EIP=%08lx\n",
                 static_cast<unsigned long>(
                     exception->ExceptionRecord->ExceptionCode),
                 static_cast<unsigned long>(exception->ContextRecord->Eip));
    std::fprintf(stderr, "fault module %s base=%p\n", module_path, module);
    return EXCEPTION_EXECUTE_HANDLER;
}

bool RedirectAddressOperands(std::uint32_t texture_lookup_target,
                             std::uint32_t* model_lookup_cell,
                             std::uint32_t* vehicle_pool_cell,
                             std::uint32_t texture_callback_target,
                             std::uint32_t* vehicle_light_cell,
                             std::uint32_t* vehicle_damage_cell,
                             std::uint32_t* vehicle_alt_cell)
{
    auto* image = reinterpret_cast<std::uint8_t*>(GetModuleHandleW(nullptr));
    auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(image);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return false;
    auto* nt = reinterpret_cast<IMAGE_NT_HEADERS32*>(image + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386)
        return false;

    struct Patch
    {
        std::uint32_t from;
        std::uint32_t to;
        unsigned expected;
        unsigned found;
    } patches[] = {
        {0x007f39f0, texture_lookup_target, 4, 0},
        {0x00c8800c, reinterpret_cast<std::uint32_t>(model_lookup_cell), 1, 0},
        {0x00b74494, reinterpret_cast<std::uint32_t>(vehicle_pool_cell), 3, 0},
        {0x0074dbc0, texture_callback_target, 2, 0},
        {0x00b4e47c, reinterpret_cast<std::uint32_t>(vehicle_light_cell), 3, 0},
        {0x00b4e68c, reinterpret_cast<std::uint32_t>(vehicle_damage_cell), 2, 0},
        {0x00b4e690, reinterpret_cast<std::uint32_t>(vehicle_alt_cell), 1, 0},
    };
    std::vector<std::vector<std::uint8_t*>> patch_sites(
        sizeof(patches) / sizeof(patches[0]));

    auto* candidate_code_section = static_cast<IMAGE_SECTION_HEADER*>(nullptr);
    auto* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned section_index = 0;
         section_index < nt->FileHeader.NumberOfSections;
         ++section_index, ++section)
    {
        if (std::memcmp(section->Name, ".xcode", 6) != 0)
            continue;
        if (candidate_code_section != nullptr ||
            (section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0 ||
            section->Misc.VirtualSize < sizeof(std::uint32_t))
        {
            std::fprintf(stderr,
                         "expected exactly one nonempty executable .xcode section\n");
            return false;
        }
        candidate_code_section = section;
    }
    if (candidate_code_section == nullptr)
    {
        std::fprintf(stderr, "candidate executable .xcode section not found\n");
        return false;
    }

    auto* code = image + candidate_code_section->VirtualAddress;
    const auto code_size = static_cast<std::size_t>(
        candidate_code_section->Misc.VirtualSize);
    for (std::size_t offset = 0;
         offset <= code_size - sizeof(std::uint32_t); ++offset)
    {
        std::uint32_t operand = 0;
        std::memcpy(&operand, code + offset, sizeof(operand));
        for (auto& patch : patches)
        {
            if (operand == patch.from)
            {
                const std::size_t index = static_cast<std::size_t>(
                    &patch - patches);
                patch_sites[index].push_back(code + offset);
                break;
            }
        }
    }
    for (std::size_t i = 0; i < sizeof(patches) / sizeof(patches[0]); ++i)
    {
        patches[i].found = static_cast<unsigned>(patch_sites[i].size());
        if (patches[i].found != patches[i].expected)
        {
            std::fprintf(stderr, "operand %08lx: found %u, expected %u\n",
                         static_cast<unsigned long>(patches[i].from),
                         patches[i].found, patches[i].expected);
            return false;
        }
    }

    for (std::size_t i = 0; i < patch_sites.size(); ++i)
    {
        for (std::size_t j = i + 1; j < patch_sites.size(); ++j)
        {
            for (const auto* left : patch_sites[i])
            {
                for (const auto* right : patch_sites[j])
                {
                    const auto left_address = reinterpret_cast<std::uintptr_t>(left);
                    const auto right_address = reinterpret_cast<std::uintptr_t>(right);
                    if (left_address < right_address + sizeof(std::uint32_t) &&
                        right_address < left_address + sizeof(std::uint32_t))
                    {
                        std::fprintf(stderr,
                                     "overlapping fixed-address patch sites at %p/%p\n",
                                     static_cast<const void*>(left),
                                     static_cast<const void*>(right));
                        return false;
                    }
                }
            }
        }
    }

    for (std::size_t i = 0; i < patch_sites.size(); ++i)
    {
        for (auto* site : patch_sites[i])
        {
            DWORD old_protection = 0;
            if (!VirtualProtect(site, sizeof(patches[i].to),
                                PAGE_EXECUTE_READWRITE, &old_protection))
                return false;
            std::memcpy(site, &patches[i].to, sizeof(patches[i].to));
            DWORD ignored = 0;
            if (!VirtualProtect(site, sizeof(patches[i].to), old_protection,
                                &ignored))
                return false;
            FlushInstructionCache(GetCurrentProcess(), site,
                                  sizeof(patches[i].to));
        }
    }
    return true;
}

struct RawPatch
{
    std::uint32_t from;
    std::uint32_t to;
    unsigned expected;
    unsigned found;
};

struct RawPatchSeed
{
    std::uint32_t from;
    unsigned expected;
};

const RawPatchSeed kOriginal076d0PatchSeeds[] = {
    {0x007f39f0, 4}, {0x0074dbc0, 4}, {0x00c8800c, 1},
    {0x00b74494, 3}, {0x00b4e47c, 3}, {0x00b4e68c, 2},
    {0x00b4e690, 1}, {0x10024a14, 1}, {0x10024e90, 2},
    {0x10024f08, 2}, {0x10024f90, 1}, {0x10024f94, 4},
    {0x100374c0, 1}, {0x10037594, 4}, {0x1003759c, 1},
    {0x1003aacc, 1}, {0x1003aedc, 1}, {0x1003aeec, 1},
    {0x1003aef0, 1}, {0x1003aef1, 1}, {0x1003aef4, 1},
    {0x1003bbc0, 1}, {0x1003bc00, 1}, {0x1003bc30, 1},
    {0x1003bc78, 4}, {0x1003bd9c, 2}, {0x1003c1a8, 1},
    {0x1003c1ec, 2}, {0x1003c1fc, 7}, {0x1003c208, 1},
    {0x1003c248, 3}, {0x1003c250, 2}, {0x1003c254, 2},
};

std::uint8_t* MapPreferredImage(const char* path)
{
    constexpr std::uint32_t preferred_base = 0x10000000;
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    const DWORD file_size = GetFileSize(file, nullptr);
    if (file_size == INVALID_FILE_SIZE ||
        file_size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(file_size);
    DWORD read = 0;
    const BOOL read_ok = ReadFile(file, bytes.data(), file_size, &read, nullptr);
    CloseHandle(file);
    if (!read_ok || read != file_size)
        return nullptr;

    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
        return nullptr;
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != preferred_base)
        return nullptr;

    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(preferred_base)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(preferred_base)))
        return nullptr;
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);
    const auto* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (section->SizeOfRawData == 0)
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

bool ReplaceRawOperands(std::uint8_t* code, std::size_t code_size,
                        RawPatch* patches, std::size_t patch_count)
{
    DWORD old_protection = 0;
    if (!VirtualProtect(code, code_size, PAGE_EXECUTE_READWRITE,
                        &old_protection))
        return false;
    for (std::size_t offset = 0;
         offset + sizeof(std::uint32_t) <= code_size; ++offset)
    {
        std::uint32_t operand = 0;
        std::memcpy(&operand, code + offset, sizeof(operand));
        for (std::size_t i = 0; i < patch_count; ++i)
        {
            if (operand == patches[i].from)
            {
                std::memcpy(code + offset, &patches[i].to,
                            sizeof(patches[i].to));
                ++patches[i].found;
                break;
            }
        }
    }
    DWORD ignored = 0;
    const bool restored = VirtualProtect(code, code_size, old_protection,
                                         &ignored) != 0;
    if (!restored)
        return false;
    for (std::size_t i = 0; i < patch_count; ++i)
    {
        if (patches[i].found != patches[i].expected)
        {
            std::fprintf(stderr,
                         "original operand %08lx: found %u expected %u\n",
                         static_cast<unsigned long>(patches[i].from),
                         patches[i].found, patches[i].expected);
            return false;
        }
    }
    FlushInstructionCache(GetCurrentProcess(), code, code_size);
    return true;
}

bool RedirectOriginalCall(std::uint8_t* code, std::uint32_t call_va,
                          std::uint32_t expected_target,
                          std::uint32_t replacement)
{
    constexpr std::uint32_t function_va = 0x100076d0;
    constexpr std::size_t function_size = 0x87e;
    const std::size_t offset = call_va - function_va;
    if (offset + 5 > function_size || code[offset] != 0xe8)
        return false;
    std::int32_t old_relative = 0;
    std::memcpy(&old_relative, code + offset + 1, sizeof(old_relative));
    const std::uint32_t old_target = call_va + 5 + old_relative;
    if (old_target != expected_target)
    {
        std::fprintf(stderr, "original call %08lx targets %08lx expected %08lx\n",
                     static_cast<unsigned long>(call_va),
                     static_cast<unsigned long>(old_target),
                     static_cast<unsigned long>(expected_target));
        return false;
    }
    const auto new_relative = static_cast<std::int32_t>(
        replacement - (call_va + 5));
    std::memcpy(code + offset + 1, &new_relative, sizeof(new_relative));
    return true;
}

extern "C" int __cdecl StubStrncmp(const char* left, const char* right,
                                    std::size_t count)
{
    return std::strncmp(left, right, count);
}

bool PatchOriginal076d0(std::uint8_t* image,
                        std::uint32_t* model_lookup_cell,
                        std::uint32_t* vehicle_pool_cell,
                        std::uint32_t* vehicle_light_cell,
                        std::uint32_t* vehicle_damage_cell,
                        std::uint32_t* vehicle_alt_cell,
                        std::int32_t* callback_values)
{
    constexpr std::uint32_t base = 0x10000000;
    constexpr std::uint32_t function_va = 0x100076d0;
    constexpr std::size_t function_size = 0x87e;
    auto* code = image + (function_va - base);
    const std::uint32_t targets[] = {
        reinterpret_cast<std::uint32_t>(&TextureLookupStub),
        reinterpret_cast<std::uint32_t>(&TextureCallbackStub),
        reinterpret_cast<std::uint32_t>(model_lookup_cell),
        reinterpret_cast<std::uint32_t>(vehicle_pool_cell),
        reinterpret_cast<std::uint32_t>(vehicle_light_cell),
        reinterpret_cast<std::uint32_t>(vehicle_damage_cell),
        reinterpret_cast<std::uint32_t>(vehicle_alt_cell),
        reinterpret_cast<std::uint32_t>(&DAT_10024a14),
        reinterpret_cast<std::uint32_t>(&_DAT_10024e90),
        reinterpret_cast<std::uint32_t>(&_DAT_10024f08),
        reinterpret_cast<std::uint32_t>(&_DAT_10024f90),
        reinterpret_cast<std::uint32_t>(&_DAT_10024f94),
        reinterpret_cast<std::uint32_t>(&DAT_100374c0),
        reinterpret_cast<std::uint32_t>(&DAT_10037594),
        reinterpret_cast<std::uint32_t>(&DAT_1003759c),
        reinterpret_cast<std::uint32_t>(&DAT_1003aacc),
        reinterpret_cast<std::uint32_t>(&DAT_1003aedc),
        reinterpret_cast<std::uint32_t>(&DAT_1003aeec),
        reinterpret_cast<std::uint32_t>(&DAT_1003aef0),
        reinterpret_cast<std::uint32_t>(&DAT_1003aef1),
        reinterpret_cast<std::uint32_t>(&DAT_1003aef4),
        reinterpret_cast<std::uint32_t>(&_DAT_1003bbc0),
        reinterpret_cast<std::uint32_t>(&_DAT_1003bc00),
        reinterpret_cast<std::uint32_t>(&_DAT_1003bc30),
        reinterpret_cast<std::uint32_t>(&DAT_1003bc78),
        reinterpret_cast<std::uint32_t>(&DAT_1003bd9c),
        reinterpret_cast<std::uint32_t>(callback_values),
        reinterpret_cast<std::uint32_t>(&_DAT_1003c1ec),
        reinterpret_cast<std::uint32_t>(&DAT_1003c1fc),
        reinterpret_cast<std::uint32_t>(&_DAT_1003c208),
        reinterpret_cast<std::uint32_t>(&DAT_1003c248),
        reinterpret_cast<std::uint32_t>(&DAT_1003c250),
        reinterpret_cast<std::uint32_t>(&DAT_1003c254),
    };
    constexpr std::size_t patch_count =
        sizeof(kOriginal076d0PatchSeeds) / sizeof(kOriginal076d0PatchSeeds[0]);
    static_assert(sizeof(targets) / sizeof(targets[0]) == patch_count);
    RawPatch patches[patch_count]{};
    for (std::size_t i = 0; i < patch_count; ++i)
    {
        patches[i].from = kOriginal076d0PatchSeeds[i].from;
        patches[i].to = targets[i];
        patches[i].expected = kOriginal076d0PatchSeeds[i].expected;
    }
    if (!ReplaceRawOperands(code, function_size, patches,
                            sizeof(patches) / sizeof(patches[0])))
        return false;

    const auto stub = [](auto function) {
        return static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(function));
    };
    return RedirectOriginalCall(code, 0x100076e9, 0x10009360,
                                stub(&FUN_10009360)) &&
           RedirectOriginalCall(code, 0x1000779d, 0x10001fb0,
                                stub(&FUN_10001fb0)) &&
           RedirectOriginalCall(code, 0x1000780e, 0x10001fb0,
                                stub(&FUN_10001fb0)) &&
           RedirectOriginalCall(code, 0x10007985, 0x10010d8b,
                                stub(&StubStrncmp)) &&
           RedirectOriginalCall(code, 0x100079b5, 0x10010d8b,
                                stub(&StubStrncmp)) &&
           RedirectOriginalCall(code, 0x100079ce, 0x10010d8b,
                                stub(&StubStrncmp)) &&
           RedirectOriginalCall(code, 0x10007b32, 0x10008e00,
                                stub(&FUN_10008e00)) &&
           RedirectOriginalCall(code, 0x10007b6c, 0x10008e00,
                                stub(&FUN_10008e00)) &&
           RedirectOriginalCall(code, 0x10007dba, 0x10009360,
                                stub(&FUN_10009360)) &&
           RedirectOriginalCall(code, 0x10007e28, 0x10009360,
                                stub(&FUN_10009360));
}
} // namespace

extern "C" __declspec(naked) int* __cdecl InvokeWithSeededEntrySlot(
    int*, int*, std::uintptr_t)
{
    __asm
    {
        push ebp
        mov ebp, esp
        sub esp, 40h
        push dword ptr [ebp + 0ch]
        push dword ptr [ebp + 08h]
        mov eax, dword ptr [ebp + 10h]
        ; After the two argument pushes, this is the callee's [EBP-8] slot.
        mov dword ptr [esp - 10h], eax
        call FUN_100076d0
        add esp, 8
        mov esp, ebp
        pop ebp
        ret
    }
}

extern "C" __declspec(naked) int* __cdecl
InvokeWithSeededOriginalEntrySlot(int*, int*, std::uintptr_t,
                                  std::uintptr_t)
{
    __asm
    {
        push ebp
        mov ebp, esp
        sub esp, 40h
        push dword ptr [ebp + 0ch]
        push dword ptr [ebp + 08h]
        mov eax, dword ptr [ebp + 10h]
        ; Seed the original function's [EBP-8] after the two argument pushes.
        mov dword ptr [esp - 10h], eax
        call dword ptr [ebp + 14h]
        add esp, 8
        mov esp, ebp
        pop ebp
        ret
    }
}

extern "C" std::int32_t __stdcall FUN_10008e00()
{
    ++g_context_calls;
    return static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(g_context));
}

extern "C" std::int32_t __stdcall FUN_10009360()
{
    ++g_vehicle_system_calls;
    return static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(g_vehicle_system));
}

extern "C" std::uint32_t* __cdecl FUN_10001fb0(std::uint32_t* value)
{
    return value;
}

int main(int argc, char** argv)
{
    auto* lookup_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* lookup_table_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* lookup_table = static_cast<std::int32_t*>(AllocateLow(0x100));
    auto* model_record_table = static_cast<std::int32_t**>(AllocateLow(16));
    auto* model_record = static_cast<std::uint8_t*>(AllocateLow(0x100));
    auto* callback_values = static_cast<std::int32_t*>(AllocateLow(16));
    auto* vehicle_pool_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* vehicle_pool = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* vehicle_objects = static_cast<std::uint8_t*>(AllocateLow(0x1000));
    auto* vehicle_system = static_cast<std::uint8_t*>(AllocateLow(0x100));
    auto* vehicle_array_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* vehicle_array = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* vehicle_record = static_cast<std::uint8_t*>(AllocateLow(0x100));
    auto* vehicle_texture_name = static_cast<std::uint8_t*>(AllocateLow(0x100));
    auto* vehicle_model_id_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* light_texture_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* damage_texture_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    auto* alt_texture_cell = static_cast<std::uint32_t*>(AllocateLow(16));
    if (lookup_cell == nullptr || lookup_table_cell == nullptr ||
        lookup_table == nullptr ||
        model_record_table == nullptr || model_record == nullptr ||
        callback_values == nullptr ||
        vehicle_pool_cell == nullptr || vehicle_pool == nullptr ||
        vehicle_objects == nullptr || vehicle_system == nullptr ||
        vehicle_array_cell == nullptr || vehicle_array == nullptr ||
        vehicle_record == nullptr || vehicle_texture_name == nullptr ||
        vehicle_model_id_cell == nullptr ||
        light_texture_cell == nullptr || damage_texture_cell == nullptr ||
        alt_texture_cell == nullptr)
        return Fail("could not allocate address-redirected test globals");
    *lookup_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(lookup_table_cell));
    *lookup_table_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(lookup_table));
    *model_record_table = reinterpret_cast<std::int32_t*>(model_record);
    *reinterpret_cast<std::int16_t*>(model_record + 10) = 1;
    lookup_table[3] = 0; // model id 1 * 0x0c; bypass texture-specific branches
    DAT_1003759c = reinterpret_cast<std::uintptr_t>(model_record_table);
    *light_texture_cell = 0;
    *damage_texture_cell = 0x6000;
    *alt_texture_cell = 0;
    *vehicle_model_id_cell = 0;
    callback_values[0] = 0x1357;
    _DAT_1003c1a8 = callback_values;
    constexpr char kOtherTextureName[] = "other_texture_name";
    std::memcpy(vehicle_texture_name + 0x10, kOtherTextureName,
                sizeof(kOtherTextureName));

    *vehicle_pool_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_pool));
    *vehicle_pool = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_objects));
    *vehicle_array_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_array));
    *vehicle_array = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_record));
    *reinterpret_cast<std::uint32_t*>(vehicle_system + 0x48) =
        *vehicle_array_cell;
    *reinterpret_cast<std::uint32_t*>(vehicle_record + 0x28) =
        0; // model-info pointer is installed after allocation below
    g_vehicle_system = vehicle_system;

    auto* context = static_cast<std::uint8_t*>(AllocateLow(0x100));
    auto* model_info = static_cast<std::uint8_t*>(AllocateLow(0x600));
    auto* textures = static_cast<std::uint8_t*>(AllocateLow(16 * 0x20));
    if (context == nullptr || model_info == nullptr || textures == nullptr)
        return Fail("could not allocate low-address test structures");

    *reinterpret_cast<std::uint32_t*>(vehicle_record + 0x28) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(model_info));

    if (!RedirectAddressOperands(
            reinterpret_cast<std::uint32_t>(&TextureLookupStub), lookup_cell,
            vehicle_pool_cell,
            reinterpret_cast<std::uint32_t>(&TextureCallbackStub),
            light_texture_cell, damage_texture_cell, alt_texture_cell))
        return Fail("could not redirect exactly the expected GTA fixed-address operands");

    std::uint8_t* original_image = nullptr;
    using OriginalFunction = int*(__cdecl*)(int*, int*);
    OriginalFunction original_function = nullptr;
    if (argc > 1)
    {
        original_image = MapPreferredImage(argv[1]);
        if (original_image == nullptr ||
            !PatchOriginal076d0(original_image, lookup_cell,
                                vehicle_pool_cell, light_texture_cell,
                                damage_texture_cell, alt_texture_cell,
                                callback_values))
            return Fail("could not load and precisely redirect original 100076d0");
        original_function = reinterpret_cast<OriginalFunction>(
            static_cast<std::uintptr_t>(0x100076d0));
    }

    *reinterpret_cast<std::uint32_t*>(context + 0x28) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(model_info));
    *reinterpret_cast<std::uint32_t*>(model_info + 0x350) = 1;
    for (std::size_t index = 0; index < 16; ++index)
    {
        const std::size_t item_offset = 0x354 + index * 0x14;
        auto* texture = textures + index * 0x20;
        *reinterpret_cast<std::uint32_t*>(model_info + item_offset + 0x0c) =
            static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(texture));
        *reinterpret_cast<std::uint16_t*>(texture + 8) =
            static_cast<std::uint16_t>(0xabcd + index);
        texture[10] = static_cast<std::uint8_t>(0x40 + index);
        model_info[item_offset + 9] = 0; // stop after selected data writes
    }
    g_context = context;

    int input[6] = {0, 0, 0, 0, 0, 0};
    for (int route = 0; route < 2; ++route)
    {
        DAT_1003c1fc = route == 0
                           ? 0
                           : static_cast<std::int32_t>(
                                 reinterpret_cast<std::uintptr_t>(vehicle_objects));
        for (std::size_t index = 0; index < 16; ++index)
        {
            const auto selector = static_cast<std::uint32_t>(0xff - index);
            const auto expected_word = static_cast<std::uint16_t>(0xabcd + index);
            const auto expected_byte = static_cast<std::uint8_t>(0x40 + index);
            input[0] = route == 0
                           ? 0
                           : static_cast<int>(reinterpret_cast<std::uintptr_t>(
                                 vehicle_texture_name));
            if (route != 0)
            {
                *damage_texture_cell = static_cast<std::uint32_t>(input[0]);
                DAT_1003aacc = static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(vehicle_model_id_cell)) -
                    8u - static_cast<std::uint32_t>(input[0]);
            }
            input[1] = static_cast<int>(selector);

            std::uintptr_t slots[4] = {};
            int cursor = static_cast<int>(reinterpret_cast<std::uintptr_t>(slots));
            int initial_input[6] = {};
            std::memcpy(initial_input, input, sizeof(initial_input));
            const int candidate_context_before = g_context_calls;
            const int candidate_vehicle_before = g_vehicle_system_calls;
            const int candidate_lookup_before = g_texture_lookup_calls;
            const int candidate_callback_before = g_texture_callback_calls;
            int* result = nullptr;
            __try
            {
                result = FUN_100076d0(input, &cursor);
            }
            __except (LogCandidateException(GetExceptionInformation()))
            {
                return 2;
            }
            if (result != input)
                return Fail("return pointer did not equal the input structure");
            const int expected_generic_calls = route == 0
                                                   ? static_cast<int>((index + 1) * 2)
                                                   : 32;
            const int expected_vehicle_calls = route == 0
                                                   ? 0
                                                   : static_cast<int>((index + 1) * 3);
            if (g_context_calls != expected_generic_calls)
            {
                std::fprintf(stderr, "route=%d selector=%02lx generic-calls=%d expected=%d vehicle-calls=%d\n",
                             route, static_cast<unsigned long>(selector),
                             g_context_calls, expected_generic_calls,
                             g_vehicle_system_calls);
                return Fail("unexpected number of generic context lookups");
            }
            if (g_vehicle_system_calls != expected_vehicle_calls)
                return Fail("unexpected number of vehicle-system lookups");
            if (g_texture_lookup_calls != 0)
                return Fail("texture lookup stub unexpectedly ran in the zero-id path");
            if (slots[0] != reinterpret_cast<std::uintptr_t>(input + 1))
                return Fail("write-slot address was not input[1]");
            if (slots[1] != selector)
                return Fail("write-slot did not preserve the original selector value");
            const std::uintptr_t expected_cursor = reinterpret_cast<std::uintptr_t>(
                slots + (route == 0 ? 2 : 4));
            if (cursor != static_cast<int>(expected_cursor))
                return Fail("write-slot cursor did not advance exactly eight bytes");
            if (route != 0 &&
                (slots[2] != reinterpret_cast<std::uintptr_t>(input + 1) ||
                 slots[3] != 0x00ffffff))
                return Fail("vehicle-context path did not emit its second color write slot");
            if ((static_cast<std::uint32_t>(input[1]) & 0xffff) != expected_word)
                return Fail("selected item did not supply its unique texture word");
            if (reinterpret_cast<std::uint8_t*>(input)[6] != expected_byte)
                return Fail("selected item did not supply its unique texture byte");

            if (original_function != nullptr)
            {
                int candidate_output[6] = {};
                std::uintptr_t candidate_slots[4] = {};
                std::memcpy(candidate_output, input, sizeof(candidate_output));
                std::memcpy(candidate_slots, slots, sizeof(candidate_slots));
                const int candidate_cursor = cursor;
                const int candidate_context_calls = g_context_calls;
                const int candidate_vehicle_calls = g_vehicle_system_calls;
                const int candidate_lookup_calls = g_texture_lookup_calls;
                const int candidate_callback_calls = g_texture_callback_calls;

                std::memcpy(input, initial_input, sizeof(initial_input));
                std::memset(slots, 0, sizeof(slots));
                cursor = static_cast<int>(reinterpret_cast<std::uintptr_t>(slots));
                int* original_result = nullptr;
                __try
                {
                    original_result = original_function(input, &cursor);
                }
                __except (LogCandidateException(GetExceptionInformation()))
                {
                    return 2;
                }

                const int original_context_delta =
                    g_context_calls - candidate_context_calls;
                const int original_vehicle_delta =
                    g_vehicle_system_calls - candidate_vehicle_calls;
                const int original_lookup_delta =
                    g_texture_lookup_calls - candidate_lookup_calls;
                const int original_callback_delta =
                    g_texture_callback_calls - candidate_callback_calls;
                const bool matched = original_result == input &&
                    std::memcmp(input, candidate_output, sizeof(candidate_output)) == 0 &&
                    std::memcmp(slots, candidate_slots, sizeof(candidate_slots)) == 0 &&
                    cursor == candidate_cursor &&
                    original_context_delta ==
                        candidate_context_calls - candidate_context_before &&
                    original_vehicle_delta ==
                        candidate_vehicle_calls - candidate_vehicle_before &&
                    original_lookup_delta ==
                        candidate_lookup_calls - candidate_lookup_before &&
                    original_callback_delta ==
                        candidate_callback_calls - candidate_callback_before;
                g_context_calls = candidate_context_calls;
                g_vehicle_system_calls = candidate_vehicle_calls;
                g_texture_lookup_calls = candidate_lookup_calls;
                g_texture_callback_calls = candidate_callback_calls;
                if (!matched)
                {
                    std::fprintf(stderr,
                        "original/candidate mismatch route=%d selector=%02lx ctx=%d/%d vehicle=%d/%d lookup=%d/%d callback=%d/%d cursor=%08lx/%08lx\n",
                        route, static_cast<unsigned long>(selector),
                        original_context_delta,
                        candidate_context_calls - candidate_context_before,
                        original_vehicle_delta,
                        candidate_vehicle_calls - candidate_vehicle_before,
                        original_lookup_delta,
                        candidate_lookup_calls - candidate_lookup_before,
                        original_callback_delta,
                        candidate_callback_calls - candidate_callback_before,
                        static_cast<unsigned long>(cursor),
                        static_cast<unsigned long>(candidate_cursor));
                    return Fail("original-binary differential mismatch in model-info route");
                }
            }
        }
    }

    constexpr int kVehicleLightSelector = 0x00abcdef;
    constexpr int kModelTextureId = 0x1234;
    constexpr int kVehicleLightsFound = 0x33330000;
    auto* damage_replacement = reinterpret_cast<std::uint8_t*>(textures + 0x1e0);
    lookup_table[3] = kModelTextureId;
    *damage_texture_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_texture_name));
    std::memcpy(vehicle_texture_name + 0x10, "vehiclelights",
                sizeof("vehiclelights"));
    DAT_1003aacc = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_model_id_cell)) -
        8u - static_cast<std::uint32_t>(
                 reinterpret_cast<std::uintptr_t>(vehicle_texture_name));
    DAT_100374c0[0] = kVehicleLightSelector;
    DAT_1003aedc[0] = '\x02'; // exercise the damaged-lights replacement path
    g_texture_lookup_calls = 0;
    g_vehiclelights_lookup_result = kVehicleLightsFound;
    g_vehiclelights_dam_lookup_result = static_cast<int>(
        reinterpret_cast<std::uintptr_t>(damage_replacement));
    input[0] = static_cast<int>(
        reinterpret_cast<std::uintptr_t>(vehicle_texture_name));
    input[1] = kVehicleLightSelector;
    std::uintptr_t light_slots[4] = {};
    int light_cursor = static_cast<int>(
        reinterpret_cast<std::uintptr_t>(light_slots));
    int light_initial_input[6] = {};
    std::memcpy(light_initial_input, input, sizeof(light_initial_input));
    const int light_context_before = g_context_calls;
    const int light_vehicle_before = g_vehicle_system_calls;
    const int light_callback_before = g_texture_callback_calls;
    int* light_result = FUN_100076d0(input, &light_cursor);
    if (light_result != input || g_texture_lookup_calls != 2 ||
        g_texture_lookup_model_ids[0] != kModelTextureId ||
        g_texture_lookup_model_ids[1] != kModelTextureId ||
        std::strcmp(g_texture_lookup_names[0], "vehiclelights") != 0 ||
        std::strcmp(g_texture_lookup_names[1], "vehiclelights_dam") != 0)
        return Fail("vehicle-lights texture lookup order or arguments did not match");
    if (light_slots[0] != reinterpret_cast<std::uintptr_t>(input + 1) ||
        light_slots[1] != static_cast<std::uint32_t>(kVehicleLightSelector) ||
        light_slots[2] != reinterpret_cast<std::uintptr_t>(input) ||
        light_slots[3] != static_cast<std::uint32_t>(
                              reinterpret_cast<std::uintptr_t>(vehicle_texture_name)) ||
        light_cursor != static_cast<int>(
                           reinterpret_cast<std::uintptr_t>(light_slots + 4)))
        return Fail("damaged-lights path emitted unexpected write-slot records");
    if (input[0] != static_cast<int>(
                        reinterpret_cast<std::uintptr_t>(damage_replacement)) ||
        static_cast<std::uint32_t>(input[1]) != 0x00ffffff)
        return Fail("damaged-lights path did not install the lookup result");

    if (original_function != nullptr)
    {
        int candidate_output[6] = {};
        std::uintptr_t candidate_slots[4] = {};
        int candidate_lookup_ids[8] = {};
        char candidate_lookup_names[8][32] = {};
        std::memcpy(candidate_output, input, sizeof(candidate_output));
        std::memcpy(candidate_slots, light_slots, sizeof(candidate_slots));
        std::memcpy(candidate_lookup_ids, g_texture_lookup_model_ids,
                    sizeof(candidate_lookup_ids));
        std::memcpy(candidate_lookup_names, g_texture_lookup_names,
                    sizeof(candidate_lookup_names));
        const int candidate_cursor = light_cursor;
        const int candidate_context_calls = g_context_calls;
        const int candidate_vehicle_calls = g_vehicle_system_calls;
        const int candidate_lookup_calls = g_texture_lookup_calls;
        const int candidate_callback_calls = g_texture_callback_calls;

        lookup_table[3] = kModelTextureId;
        *damage_texture_cell = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(vehicle_texture_name));
        DAT_1003aacc = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(vehicle_model_id_cell)) - 8u -
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(vehicle_texture_name));
        DAT_100374c0[0] = kVehicleLightSelector;
        DAT_1003aedc[0] = '\x02';
        DAT_1003c1fc = static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(vehicle_objects));
        std::memcpy(vehicle_texture_name + 0x10, "vehiclelights",
                    sizeof("vehiclelights"));
        std::memcpy(input, light_initial_input, sizeof(light_initial_input));
        std::memset(light_slots, 0, sizeof(light_slots));
        light_cursor = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(light_slots));
        g_texture_lookup_calls = 0;
        const int original_context_before = g_context_calls;
        const int original_vehicle_before = g_vehicle_system_calls;
        const int original_callback_before = g_texture_callback_calls;
        int* original_result = nullptr;
        __try
        {
            original_result = original_function(input, &light_cursor);
        }
        __except (LogCandidateException(GetExceptionInformation()))
        {
            return 2;
        }

        const int original_lookup_calls = g_texture_lookup_calls;
        const int original_context_delta =
            g_context_calls - original_context_before;
        const int original_vehicle_delta =
            g_vehicle_system_calls - original_vehicle_before;
        const int original_callback_delta =
            g_texture_callback_calls - original_callback_before;
        const bool matched = original_result == input &&
            std::memcmp(input, candidate_output, sizeof(candidate_output)) == 0 &&
            std::memcmp(light_slots, candidate_slots, sizeof(candidate_slots)) == 0 &&
            light_cursor == candidate_cursor &&
            original_lookup_calls == candidate_lookup_calls &&
            std::memcmp(g_texture_lookup_model_ids, candidate_lookup_ids,
                        sizeof(candidate_lookup_ids)) == 0 &&
            std::memcmp(g_texture_lookup_names, candidate_lookup_names,
                        sizeof(candidate_lookup_names)) == 0 &&
            original_context_delta ==
                candidate_context_calls - light_context_before &&
            original_vehicle_delta ==
                candidate_vehicle_calls - light_vehicle_before &&
            original_callback_delta ==
                candidate_callback_calls - light_callback_before;
        g_context_calls = candidate_context_calls;
        g_vehicle_system_calls = candidate_vehicle_calls;
        g_texture_lookup_calls = candidate_lookup_calls;
        g_texture_callback_calls = candidate_callback_calls;
        if (!matched)
        {
            std::fprintf(stderr,
                "original/candidate mismatch route=vehiclelights ctx=%d/%d vehicle=%d/%d lookup=%d/%d cursor=%08lx/%08lx\n",
                original_context_delta,
                candidate_context_calls - light_context_before,
                original_vehicle_delta,
                candidate_vehicle_calls - light_vehicle_before,
                original_lookup_calls, candidate_lookup_calls,
                static_cast<unsigned long>(light_cursor),
                static_cast<unsigned long>(candidate_cursor));
            return Fail("original-binary differential mismatch in vehicle-lights path");
        }
    }

    lookup_table[3] = 0;
    DAT_100374c0[0] = 0;
    DAT_1003aedc[0] = 0;

    auto* grunge_texture = static_cast<std::uint8_t*>(AllocateLow(0x100));
    if (grunge_texture == nullptr)
        return Fail("could not allocate callback-path texture data");
    constexpr char kGrungeName[] = "vehiclegrunge256";
    std::memcpy(grunge_texture + 0x10, kGrungeName, sizeof(kGrungeName));
    DAT_1003c1fc = 0;
    DAT_1003aacc = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_model_id_cell)) -
        8u - static_cast<std::uint32_t>(
                 reinterpret_cast<std::uintptr_t>(grunge_texture));
    input[0] = static_cast<int>(reinterpret_cast<std::uintptr_t>(grunge_texture));
    input[1] = 0x000000f5;
    std::uintptr_t callback_slots[4] = {};
    int callback_cursor = static_cast<int>(
        reinterpret_cast<std::uintptr_t>(callback_slots));
    int callback_initial_input[6] = {};
    std::memcpy(callback_initial_input, input, sizeof(callback_initial_input));
    const int callback_context_before = g_context_calls;
    const int callback_vehicle_before = g_vehicle_system_calls;
    const int callback_lookup_before = g_texture_lookup_calls;
    const int callback_count_before = g_texture_callback_calls;
    g_callback_reentry_enabled = true;
    int* callback_result = FUN_100076d0(input, &callback_cursor);
    g_callback_reentry_enabled = false;
    if (callback_result != input || g_texture_callback_calls != 1 ||
        g_texture_callback_value != 0x1357 ||
        g_texture_callback_parameters != input)
        return Fail("grunge callback did not receive its expected x86 arguments once");
    if (!g_callback_reentry_passed)
        return Fail("candidate did not complete the controlled nested callback call");
    if (callback_slots[0] != reinterpret_cast<std::uintptr_t>(input + 1) ||
        callback_slots[1] != 0x000000f5 ||
        callback_cursor != static_cast<int>(
                               reinterpret_cast<std::uintptr_t>(callback_slots + 2)))
        return Fail("callback route outer invocation emitted an unexpected write slot");
    if ((static_cast<std::uint32_t>(input[1]) & 0xffff) != 0xabcd + 10 ||
        reinterpret_cast<std::uint8_t*>(input)[6] != 0x40 + 10)
        return Fail("callback route outer invocation did not complete model-info copy");

    if (original_function != nullptr)
    {
        int candidate_output[6] = {};
        std::uintptr_t candidate_slots[4] = {};
        std::memcpy(candidate_output, input, sizeof(candidate_output));
        std::memcpy(candidate_slots, callback_slots, sizeof(candidate_slots));
        const int candidate_cursor = callback_cursor;
        const int candidate_context_calls = g_context_calls;
        const int candidate_vehicle_calls = g_vehicle_system_calls;
        const int candidate_lookup_calls = g_texture_lookup_calls;
        const int candidate_callback_calls = g_texture_callback_calls;

        std::memcpy(input, callback_initial_input,
                    sizeof(callback_initial_input));
        std::memset(callback_slots, 0, sizeof(callback_slots));
        callback_cursor = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(callback_slots));
        DAT_1003c1fc = 0;
        g_callback_reentry_enabled = true;
        g_callback_reentry_function = original_function;
        g_callback_reentry_passed = false;
        g_inside_texture_callback = false;
        g_texture_callback_calls = 0;
        g_texture_callback_parameters = nullptr;
        g_texture_callback_value = 0;
        const int original_context_before = g_context_calls;
        const int original_vehicle_before = g_vehicle_system_calls;
        const int original_lookup_before = g_texture_lookup_calls;
        const int original_callback_before = g_texture_callback_calls;
        int* original_result = nullptr;
        __try
        {
            original_result = original_function(input, &callback_cursor);
        }
        __except (LogCandidateException(GetExceptionInformation()))
        {
            return 2;
        }
        g_callback_reentry_enabled = false;
        g_callback_reentry_function = nullptr;

        const bool matched = original_result == input &&
            std::memcmp(input, candidate_output, sizeof(candidate_output)) == 0 &&
            std::memcmp(callback_slots, candidate_slots,
                        sizeof(candidate_slots)) == 0 &&
            callback_cursor == candidate_cursor &&
            g_callback_reentry_passed &&
            g_texture_callback_calls - original_callback_before ==
                candidate_callback_calls - callback_count_before &&
            g_texture_callback_parameters == input &&
            g_texture_callback_value == 0x1357 &&
            g_context_calls - original_context_before ==
                candidate_context_calls - callback_context_before &&
            g_vehicle_system_calls - original_vehicle_before ==
                candidate_vehicle_calls - callback_vehicle_before &&
            g_texture_lookup_calls - original_lookup_before ==
                candidate_lookup_calls - callback_lookup_before;
        g_context_calls = candidate_context_calls;
        g_vehicle_system_calls = candidate_vehicle_calls;
        g_texture_lookup_calls = candidate_lookup_calls;
        g_texture_callback_calls = candidate_callback_calls;
        if (!matched)
            return Fail("original-binary differential mismatch in nested callback re-entry path");
    }

    auto* flip_texture = static_cast<std::uint8_t*>(AllocateLow(0x100));
    auto* palette_context = static_cast<std::uint8_t*>(AllocateLow(0x80));
    auto* palette_data = static_cast<std::uint8_t*>(AllocateLow(0x20));
    if (flip_texture == nullptr || palette_context == nullptr ||
        palette_data == nullptr)
        return Fail("could not allocate stack-slot flip-path state");
    std::memcpy(flip_texture + 0x10, kGrungeName, sizeof(kGrungeName));
    std::int32_t palette_indices[4] = {2, 0, 0, 0};
    DAT_10037594 = palette_indices;
    *reinterpret_cast<std::uint32_t*>(palette_context + 0x2c) = 4;
    *reinterpret_cast<std::uint32_t*>(palette_context + 0x30) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(palette_data));
    palette_data[8] = 0x31;
    palette_data[9] = 0x42;
    palette_data[10] = 0x53;
    DAT_1003aacc = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_model_id_cell)) -
        8u - static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(flip_texture));
    DAT_1003c1fc = 0; // Entry path must leave [EBP-8] untouched.
    input[0] = static_cast<int>(reinterpret_cast<std::uintptr_t>(flip_texture));
    input[1] = 0x0000ff3c; // palette index 2
    std::uintptr_t flip_slots[2] = {};
    int flip_cursor = static_cast<int>(reinterpret_cast<std::uintptr_t>(flip_slots));
    int flip_initial_input[6] = {};
    std::memcpy(flip_initial_input, input, sizeof(flip_initial_input));
    g_texture_callback_calls = 0;
    g_flip_vehicle_context_on_callback = true;
    g_callback_vehicle_context = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(vehicle_objects));
    const int flip_context_before = g_context_calls;
    const int flip_vehicle_before = g_vehicle_system_calls;
    const int flip_lookup_before = g_texture_lookup_calls;
    const int flip_callback_before = g_texture_callback_calls;
    int* flip_result = InvokeWithSeededEntrySlot(
        input, &flip_cursor,
        reinterpret_cast<std::uintptr_t>(palette_context));
    g_flip_vehicle_context_on_callback = false;
    if (flip_result != input || g_texture_callback_calls != 1 ||
        g_texture_callback_parameters != input ||
        g_texture_callback_value != 0x1357 ||
        DAT_1003c1fc != g_callback_vehicle_context)
        return Fail("callback did not flip the context global in the intended frame");
    if (flip_slots[0] != reinterpret_cast<std::uintptr_t>(input + 1) ||
        flip_slots[1] != 0x0000ff3c ||
        flip_cursor != static_cast<int>(
                           reinterpret_cast<std::uintptr_t>(flip_slots + 2)))
        return Fail("stack-slot flip path emitted unexpected palette write records");
    if (reinterpret_cast<std::uint8_t*>(input)[4] != 0x31 ||
        reinterpret_cast<std::uint8_t*>(input)[5] != 0x42 ||
        reinterpret_cast<std::uint8_t*>(input)[6] != 0x53)
        return Fail("post-callback palette path did not consume the seeded raw stack slot");

    if (original_function != nullptr)
    {
        int candidate_output[6] = {};
        std::uintptr_t candidate_slots[2] = {};
        std::memcpy(candidate_output, input, sizeof(candidate_output));
        std::memcpy(candidate_slots, flip_slots, sizeof(candidate_slots));
        const int candidate_cursor = flip_cursor;
        const int candidate_context_calls = g_context_calls;
        const int candidate_vehicle_calls = g_vehicle_system_calls;
        const int candidate_lookup_calls = g_texture_lookup_calls;
        const int candidate_callback_calls = g_texture_callback_calls;

        std::memcpy(input, flip_initial_input, sizeof(flip_initial_input));
        std::memset(flip_slots, 0, sizeof(flip_slots));
        flip_cursor = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(flip_slots));
        DAT_1003c1fc = 0;
        DAT_10037594 = palette_indices;
        g_texture_callback_calls = 0;
        g_texture_callback_parameters = nullptr;
        g_texture_callback_value = 0;
        g_flip_vehicle_context_on_callback = true;
        const int original_callback_before = g_texture_callback_calls;
        int* original_result = InvokeWithSeededOriginalEntrySlot(
            input, &flip_cursor,
            reinterpret_cast<std::uintptr_t>(palette_context),
            reinterpret_cast<std::uintptr_t>(original_function));
        const int original_context_delta =
            g_context_calls - candidate_context_calls;
        const int original_vehicle_delta =
            g_vehicle_system_calls - candidate_vehicle_calls;
        const int original_lookup_delta =
            g_texture_lookup_calls - candidate_lookup_calls;
        const int original_callback_delta =
            g_texture_callback_calls - original_callback_before;
        const bool matched = original_result == input &&
            std::memcmp(input, candidate_output, sizeof(candidate_output)) == 0 &&
            std::memcmp(flip_slots, candidate_slots, sizeof(candidate_slots)) == 0 &&
            flip_cursor == candidate_cursor &&
            DAT_1003c1fc == g_callback_vehicle_context &&
            g_texture_callback_parameters == input &&
            g_texture_callback_value == 0x1357 &&
            reinterpret_cast<std::uint8_t*>(input)[4] == 0x31 &&
            reinterpret_cast<std::uint8_t*>(input)[5] == 0x42 &&
            reinterpret_cast<std::uint8_t*>(input)[6] == 0x53 &&
            original_context_delta ==
                candidate_context_calls - flip_context_before &&
            original_vehicle_delta ==
                candidate_vehicle_calls - flip_vehicle_before &&
            original_lookup_delta ==
                candidate_lookup_calls - flip_lookup_before &&
            original_callback_delta ==
                candidate_callback_calls - flip_callback_before;
        g_context_calls = candidate_context_calls;
        g_vehicle_system_calls = candidate_vehicle_calls;
        g_texture_lookup_calls = candidate_lookup_calls;
        g_texture_callback_calls = candidate_callback_calls;
        g_flip_vehicle_context_on_callback = false;
        if (!matched)
        {
            std::fprintf(stderr,
                "stack-flip differential details: input=%d slots=%d cursor=%08lx/%08lx global=%08lx/%08lx callback=%d param=%d value=%08lx palette=%02x,%02x,%02x context=%d/%d vehicle=%d/%d lookup=%d/%d callback-count=%d/%d\\n",
                std::memcmp(input, candidate_output, sizeof(candidate_output)) == 0,
                std::memcmp(flip_slots, candidate_slots, sizeof(candidate_slots)) == 0,
                static_cast<unsigned long>(flip_cursor),
                static_cast<unsigned long>(candidate_cursor),
                static_cast<unsigned long>(DAT_1003c1fc),
                static_cast<unsigned long>(g_callback_vehicle_context),
                g_texture_callback_parameters == input,
                g_texture_callback_value == 0x1357,
                static_cast<unsigned long>(g_texture_callback_value),
                reinterpret_cast<std::uint8_t*>(input)[4],
                reinterpret_cast<std::uint8_t*>(input)[5],
                reinterpret_cast<std::uint8_t*>(input)[6],
                original_context_delta,
                candidate_context_calls - flip_context_before,
                original_vehicle_delta,
                candidate_vehicle_calls - flip_vehicle_before,
                original_lookup_delta,
                candidate_lookup_calls - flip_lookup_before,
                original_callback_delta,
                candidate_callback_calls - flip_callback_before);
            return Fail("original-binary differential mismatch in callback-time stack-slot path");
        }
    }

    DAT_1003c1fc = 0;
    DAT_10037594 = nullptr;

    std::puts("PASS: address-redirected PE32 harness ran both model-info routes for all 16 selectors, damaged-vehicle-lights lookup, controlled callback re-entry, and a callback-time context-global flip with a seeded entry stack slot.");
    std::puts("SCOPE: address-redirected candidate-object tests also covered a synthetic callback that flips DAT_1003c1fc after entry while consuming a deliberately seeded [EBP-8] value; this validates stack-slot preservation only, not whether a real callback causes that transition.");
    return 0;
}
