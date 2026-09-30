#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <cstring>
#include <vector>

extern "C" void __cdecl FUN_10006790(std::uint32_t);
extern "C" void __stdcall FUN_10003f80();
extern "C" std::uint32_t __cdecl FUN_10003fb0(std::uint32_t,
                                                std::uint32_t);
extern "C" void __cdecl FUN_10003fe0(int, int);
extern "C" void __cdecl FUN_100069e0(std::int32_t);
extern "C" void __stdcall FUN_10006ad0();
int __cdecl FUN_100074d0(std::int32_t);

struct CallerPoolManager
{
    std::uint8_t reserved[0x48];
    std::uint32_t pool;
};

struct VehicleHookRecord
{
    std::uint32_t ebx;
    std::uint32_t vehicle_argument;
};

std::int32_t DAT_1003c248{};
#pragma comment(linker, "/alternatename:?DAT_1003c248@@3HC=?DAT_1003c248@@3HA")
CallerPoolManager g_caller_pool_manager{};
std::uint32_t g_caller_pool[64]{};
alignas(16) std::uint8_t g_caller_entities[64][0x40]{};
alignas(16) std::uint8_t g_caller_records[64][0x600]{};
alignas(16) std::uint8_t g_vehicle_instances[64 * 0xa18]{};
std::uint32_t g_vehicle_base_cell{};
std::uint32_t g_vehicle_pool_pointer_cell{};
extern "C" std::uint32_t g_vehicle_hook_count{};
extern "C" VehicleHookRecord g_vehicle_hook_records[3]{};

extern "C" std::int32_t __stdcall FUN_10009360()
{
    return static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(
        &g_caller_pool_manager));
}

double DAT_10024e80{};
float DAT_10024e90{};
double DAT_10024e98{};
double DAT_10024ea0{};
volatile std::uint32_t DAT_1003aedc{};
volatile std::uint32_t DAT_1003aee0{};
volatile std::uint32_t DAT_1003aee4{};
volatile std::uint32_t DAT_1003aee8{};
volatile std::uint32_t DAT_1003aeec{};
volatile std::uint8_t DAT_1003aef0{};
volatile std::int32_t DAT_1003aef4{};
volatile std::uint32_t DAT_1003c1ec{};
volatile std::int32_t DAT_1003c1fc{};
volatile std::uint32_t DAT_1003bc78{};

struct CallerQueryRecord
{
    std::uint32_t receiver;
    std::uint32_t edx_in;
    std::uint32_t selector;
    std::uint32_t result;
    std::uint32_t edx_out;
};

struct CallerDownstreamRecord
{
    std::uint32_t function;
    std::uint32_t argument;
};

volatile std::uint32_t g_caller_query_result[4]{};
volatile std::uint32_t g_caller_query_count{};
CallerQueryRecord g_caller_query_records[8]{};
volatile std::uint32_t g_caller_hash_ecx{};
volatile std::uint32_t g_caller_hash_edx{};
volatile float g_caller_hash_float{};
volatile std::uint32_t g_caller_downstream_count{};
CallerDownstreamRecord g_caller_downstream[8]{};

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000u;
constexpr std::uint32_t kFunctionEntry = 0x10006790u;
constexpr std::uint32_t kCallerEntry = 0x100069e0u;
constexpr std::uint32_t kManagerCall = 0x100069ecu;
constexpr std::uint32_t kCallbackCall = 0x10006a38u;
constexpr std::uint32_t kAdEntry = 0x10006ad0u;
constexpr std::uint32_t kAdManagerCall = 0x10006adcu;
constexpr std::uint32_t kTimerAddress = 0x00b7cb84u;
constexpr std::uint32_t kVehiclePoolPointer = 0x00b74494u;
constexpr std::uint32_t kRotateEntry = 0x0059afa0u;
constexpr std::uint32_t kQueryEntry = 0x006c2180u;
constexpr std::uint32_t kKnownQueryEntry = 0x006c2230u;
constexpr std::uint32_t kRegisterAEntry = 0x007f1200u;
constexpr std::uint32_t kRegisterBEntry = 0x007f0dc0u;
constexpr std::size_t kOriginalFunctionSize = 0x230;
constexpr std::size_t kCandidateFunctionSize = 0x248;
constexpr std::size_t kWrapperFunctionSize = 0x22;
constexpr std::uint32_t kEsiSentinel = 0x13579bdfu;
constexpr std::uint32_t kEdiSentinel = 0x2468ace0u;
constexpr std::uint32_t kEbxSentinel = 0x55aa55aau;

struct Observation
{
    std::uint32_t matrix_this;
    std::uint32_t angle_bits;
    std::uint32_t count;
};

struct Invocation
{
    std::int32_t esp_delta;
    std::uint32_t ebx;
    std::uint32_t esi;
    std::uint32_t edi;
};

struct ApiCall
{
    std::uint32_t api;
    std::uint32_t context;
    std::uint32_t callback;
    std::uint32_t mode;
};

struct QueryObservation
{
    std::uint32_t context;
    std::uint32_t selector;
    std::uint32_t count;
};

struct QueryTrace
{
    std::uint32_t api_kind;
    std::uint32_t context;
    std::uint32_t selector;
    std::uint32_t result;
};

Observation g_observation{};
ApiCall g_calls[2]{};
std::uint32_t g_call_count{};
QueryObservation g_query_observation{};
QueryTrace g_query_trace[16]{};
volatile std::uint32_t g_query_api_kind{};
volatile std::uint32_t g_query_result{};
volatile std::uint32_t g_timer_value{};
volatile std::uint32_t g_esp_before{};
volatile std::uint32_t g_invoke_eax{};
ApiCall g_ad_calls[12]{};
std::uint32_t g_ad_call_count{};

extern "C" void __cdecl TestGtaApiA(std::uint32_t, std::uint32_t,
                                    std::uint32_t);
extern "C" void __cdecl TestGtaApiB(std::uint32_t, std::uint32_t,
                                    std::uint32_t);

std::uint8_t* MapReference(wchar_t const* path)
{
    HANDLE file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
    {
        std::fprintf(stderr, "MapReference CreateFile failed: %lu\n",
                     GetLastError());
        return nullptr;
    }
    LARGE_INTEGER file_size{};
    if (!GetFileSizeEx(file, &file_size) || file_size.QuadPart <= 0 ||
        file_size.QuadPart > 0x7fffffff)
    {
        std::fprintf(stderr, "MapReference file-size check failed: %lu\n",
                     GetLastError());
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> file_bytes(
        static_cast<std::size_t>(file_size.QuadPart));
    DWORD bytes_read = 0;
    const BOOL read_ok = ReadFile(file, file_bytes.data(),
                                  static_cast<DWORD>(file_bytes.size()),
                                  &bytes_read, nullptr);
    CloseHandle(file);
    if (!read_ok || bytes_read != file_bytes.size() ||
        file_bytes.size() < sizeof(IMAGE_DOS_HEADER))
    {
        std::fprintf(stderr,
                     "MapReference read failed: ok=%d read=%lu size=%zu err=%lu\n",
                     read_ok, bytes_read, file_bytes.size(), GetLastError());
        return nullptr;
    }

    auto const* dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(file_bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0 ||
        static_cast<std::size_t>(dos->e_lfanew) + sizeof(IMAGE_NT_HEADERS32) >
            file_bytes.size())
    {
        std::fprintf(stderr, "MapReference DOS validation failed: magic=%04x off=%ld\n",
                     dos->e_magic, dos->e_lfanew);
        return nullptr;
    }
    auto const* nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(
        file_bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC ||
        nt->OptionalHeader.ImageBase != kImageBase)
    {
        std::fprintf(stderr,
                     "MapReference PE validation failed: sig=%08lx machine=%04x magic=%04x base=%08lx\n",
                     nt->Signature, nt->FileHeader.Machine,
                     nt->OptionalHeader.Magic, nt->OptionalHeader.ImageBase);
        return nullptr;
    }

    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(kImageBase), nt->OptionalHeader.SizeOfImage,
        MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(kImageBase))
    {
        std::fprintf(stderr,
                     "MapReference VirtualAlloc failed: ptr=%p size=%08lx err=%lu\n",
                     image, nt->OptionalHeader.SizeOfImage, GetLastError());
        return nullptr;
    }
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, file_bytes.data(), nt->OptionalHeader.SizeOfHeaders);
    auto const* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (section->SizeOfRawData == 0)
            continue;
        if (section->PointerToRawData > file_bytes.size() ||
            section->SizeOfRawData >
                file_bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData >
                nt->OptionalHeader.SizeOfImage - section->VirtualAddress)
        {
            std::fprintf(stderr,
                         "MapReference section %u invalid: rawoff=%08lx raw=%08lx va=%08lx image=%08lx\n",
                         i, section->PointerToRawData, section->SizeOfRawData,
                         section->VirtualAddress, nt->OptionalHeader.SizeOfImage);
            VirtualFree(image, 0, MEM_RELEASE);
            return nullptr;
        }
        std::memcpy(image + section->VirtualAddress,
                    file_bytes.data() + section->PointerToRawData,
                    section->SizeOfRawData);
    }
    std::fprintf(stderr, "MapReference success: base=%p size=%08lx\n", image,
                 nt->OptionalHeader.SizeOfImage);
    return image;
}

extern "C" __declspec(naked) void __fastcall RecordRotateXOnly(
    void*, void*, float)
{
    __asm {
        mov dword ptr [g_observation], ecx
        mov eax, dword ptr [esp + 4]
        mov dword ptr [g_observation + 4], eax
        inc dword ptr [g_observation + 8]
        ret 4
    }
}

extern "C" __declspec(naked) void __fastcall RecordQuery(
    void*, void*, std::uint32_t)
{
    __asm {
        mov dword ptr [g_query_api_kind], 0
        mov dword ptr [g_query_observation], ecx
        mov eax, dword ptr [esp + 4]
        and eax, 0ffh
        mov dword ptr [g_query_observation + 4], eax
        mov edx, dword ptr [g_query_observation + 8]
        cmp edx, 16
        jae query_trace_full
        shl edx, 4
        mov dword ptr [g_query_trace + edx], 0
        mov dword ptr [g_query_trace + edx + 4], ecx
        mov eax, dword ptr [esp + 4]
        and eax, 0ffh
        mov dword ptr [g_query_trace + edx + 8], eax
        mov eax, dword ptr [g_query_result]
        mov dword ptr [g_query_trace + edx + 0ch], eax
    query_trace_full:
        inc dword ptr [g_query_observation + 8]
        mov eax, dword ptr [g_query_result]
        ret 4
    }
}

extern "C" __declspec(naked) void __fastcall RecordQuery2180(
    void*, void*, std::uint32_t)
{
    __asm {
        mov dword ptr [g_query_api_kind], 1
        mov dword ptr [g_query_observation], ecx
        mov eax, dword ptr [esp + 4]
        and eax, 0ffh
        mov dword ptr [g_query_observation + 4], eax
        mov edx, dword ptr [g_query_observation + 8]
        cmp edx, 16
        jae query2180_trace_full
        shl edx, 4
        mov dword ptr [g_query_trace + edx], 1
        mov dword ptr [g_query_trace + edx + 4], ecx
        mov eax, dword ptr [esp + 4]
        and eax, 0ffh
        mov dword ptr [g_query_trace + edx + 8], eax
        mov eax, dword ptr [g_query_result]
        mov dword ptr [g_query_trace + edx + 0ch], eax
    query2180_trace_full:
        inc dword ptr [g_query_observation + 8]
        mov eax, dword ptr [g_query_result]
        ret 4
    }
}

extern "C" __declspec(naked) void __fastcall RecordQuery2230(
    void*, void*, std::uint32_t)
{
    __asm {
        mov dword ptr [g_query_api_kind], 2
        mov dword ptr [g_query_observation], ecx
        mov eax, dword ptr [esp + 4]
        and eax, 0ffh
        mov dword ptr [g_query_observation + 4], eax
        mov edx, dword ptr [g_query_observation + 8]
        cmp edx, 16
        jae query2230_trace_full
        shl edx, 4
        mov dword ptr [g_query_trace + edx], 2
        mov dword ptr [g_query_trace + edx + 4], ecx
        mov eax, dword ptr [esp + 4]
        and eax, 0ffh
        mov dword ptr [g_query_trace + edx + 8], eax
        mov eax, dword ptr [g_query_result]
        mov dword ptr [g_query_trace + edx + 0ch], eax
    query2230_trace_full:
        inc dword ptr [g_query_observation + 8]
        mov eax, dword ptr [g_query_result]
        ret 4
    }
}

extern "C" __declspec(naked) void __cdecl RecordVehicleHook(std::uint32_t)
{
    __asm {
        mov eax, dword ptr [g_vehicle_hook_count]
        cmp eax, 3
        jae record_vehicle_hook_done
        mov ecx, eax
        shl ecx, 3
        mov edx, dword ptr [esp + 4]
        mov dword ptr [g_vehicle_hook_records + ecx], ebx
        mov dword ptr [g_vehicle_hook_records + ecx + 4], edx
    record_vehicle_hook_done:
        inc dword ptr [g_vehicle_hook_count]
        ret
    }
}

extern "C" void __cdecl TestGtaApiA(std::uint32_t context,
                                    std::uint32_t callback,
                                    std::uint32_t mode)
{
    if (g_call_count < 2)
        g_calls[g_call_count] = {1, context, callback, mode};
    ++g_call_count;
}

extern "C" void __cdecl TestGtaApiB(std::uint32_t context,
                                    std::uint32_t callback,
                                    std::uint32_t mode)
{
    if (g_call_count < 2)
        g_calls[g_call_count] = {2, context, callback, mode};
    ++g_call_count;
}

extern "C" void __cdecl TestAdApiA(std::uint32_t context,
                                   std::uint32_t callback,
                                   std::uint32_t mode)
{
    if (g_ad_call_count < 12)
        g_ad_calls[g_ad_call_count] = {1, context, callback, mode};
    ++g_ad_call_count;
}

extern "C" void __cdecl TestAdApiB(std::uint32_t context,
                                   std::uint32_t callback,
                                   std::uint32_t mode)
{
    if (g_ad_call_count < 12)
        g_ad_calls[g_ad_call_count] = {2, context, callback, mode};
    ++g_ad_call_count;
}

extern "C" __declspec(naked) void __fastcall TestCallerQuery2130(
    void*, std::uint32_t, std::uint32_t)
{
    __asm {
        push ecx
        push edx
        mov eax, dword ptr [g_caller_query_count]
        cmp eax, 8
        jae caller_query_not_stored
        imul eax, eax, 20
        mov ecx, dword ptr [esp + 4]
        mov dword ptr [g_caller_query_records + eax], ecx
        mov ecx, dword ptr [esp]
        mov dword ptr [g_caller_query_records + eax + 4], ecx
        mov ecx, dword ptr [esp + 0Ch]
        mov dword ptr [g_caller_query_records + eax + 8], ecx
        mov edx, ecx
        and edx, 3
        mov edx, dword ptr [g_caller_query_result + edx * 4]
        mov dword ptr [g_caller_query_records + eax + 0Ch], edx
        mov ecx, dword ptr [esp + 0Ch]
        lea edx, dword ptr [ecx + 0A0000000h]
        mov dword ptr [g_caller_query_records + eax + 10h], edx
    caller_query_not_stored:
        inc dword ptr [g_caller_query_count]
        mov ecx, dword ptr [esp + 0Ch]
        and ecx, 3
        mov eax, dword ptr [g_caller_query_result + ecx * 4]
        mov edx, dword ptr [esp + 0Ch]
        add edx, 0A0000000h
        pop ecx
        add esp, 4
        ret 4
    }
}

extern "C" __declspec(naked) std::uint64_t __fastcall FUN_1001ba40(
    std::uint32_t, std::uint32_t)
{
    __asm {
        mov dword ptr [g_caller_hash_ecx], ecx
        mov dword ptr [g_caller_hash_edx], edx
        fstp dword ptr [g_caller_hash_float]
        mov eax, 7
        mov edx, 12345678h
        ret
    }
}

void RecordCallerDownstream(std::uint32_t function, std::uint32_t argument)
{
    const auto index = g_caller_downstream_count;
    if (index < 8)
        g_caller_downstream[index] = {function, argument};
    ++g_caller_downstream_count;
}

extern "C" void __cdecl FUN_10006360(std::int32_t argument)
{
    RecordCallerDownstream(1, static_cast<std::uint32_t>(argument));
}

extern "C" void __stdcall FUN_10006a50()
{
    RecordCallerDownstream(3, 0);
}

extern "C" void __cdecl FUN_10005860(std::int32_t argument)
{
    RecordCallerDownstream(5, static_cast<std::uint32_t>(argument));
}

extern "C" void __cdecl RecordCaller069e0(std::int32_t argument)
{
    RecordCallerDownstream(2, static_cast<std::uint32_t>(argument));
}

extern "C" void __stdcall RecordCaller06ad0()
{
    RecordCallerDownstream(4, 0);
}

extern "C" __declspec(naked) void __cdecl InvokeTarget(
    std::uint32_t, std::uint32_t, std::uint8_t*, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        mov ebx, dword ptr [ebp + 10h]
        mov esi, 13579BDFh
        mov edi, 2468ACE0h
        mov dword ptr [g_esp_before], esp
        mov eax, dword ptr [ebp + 8]
        push dword ptr [ebp + 0Ch]
        call eax
        mov dword ptr [g_invoke_eax], eax
        add esp, 4
        mov edx, dword ptr [ebp + 14h]
        mov ecx, esp
        sub ecx, dword ptr [g_esp_before]
        mov dword ptr [edx], ecx
        mov dword ptr [edx + 4], ebx
        mov dword ptr [edx + 8], esi
        mov dword ptr [edx + 0Ch], edi
        lea esp, dword ptr [ebp - 0Ch]
        pop edi
        pop esi
        pop ebx
        pop ebp
        ret
    }
}

extern "C" __declspec(naked) void __cdecl InvokeEdiTarget(
    std::uint32_t, std::uint32_t, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        mov ebx, 55AA55AAh
        mov esi, 13579BDFh
        mov edi, dword ptr [ebp + 0Ch]
        mov dword ptr [g_esp_before], esp
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, dword ptr [ebp + 10h]
        mov ecx, esp
        sub ecx, dword ptr [g_esp_before]
        mov dword ptr [edx], ecx
        mov dword ptr [edx + 4], ebx
        mov dword ptr [edx + 8], esi
        mov dword ptr [edx + 0Ch], edi
        pop edi
        pop esi
        pop ebx
        pop ebp
        ret
    }
}

int EdiInvocationExceptionFilter(EXCEPTION_POINTERS* exception)
{
    const auto* const context = exception->ContextRecord;
    std::fprintf(stderr,
        "10006ad0 SEH exception=%08lx EIP=%08lx EAX=%08lx ECX=%08lx EDX=%08lx EBX=%08lx ESI=%08lx EDI=%08lx EBP=%08lx ESP=%08lx stack=%08lx,%08lx,%08lx,%08lx\n",
        exception->ExceptionRecord->ExceptionCode, context->Eip, context->Eax,
        context->Ecx, context->Edx, context->Ebx, context->Esi, context->Edi,
        context->Ebp, context->Esp,
        reinterpret_cast<const std::uint32_t*>(context->Esp)[0],
        reinterpret_cast<const std::uint32_t*>(context->Esp)[1],
        reinterpret_cast<const std::uint32_t*>(context->Esp)[2],
        reinterpret_cast<const std::uint32_t*>(context->Esp)[3]);
    return EXCEPTION_EXECUTE_HANDLER;
}

void SafeInvokeEdiTarget(std::uint32_t target, std::uint32_t edi,
                         Invocation* invocation)
{
    __try
    {
        InvokeEdiTarget(target, edi, invocation);
    }
    __except(EdiInvocationExceptionFilter(GetExceptionInformation()))
    {
        invocation->esp_delta = INT32_MIN;
    }
}

std::size_t ReplaceImmediate(std::uint8_t* code, std::size_t size,
                             std::uint32_t from, std::uint32_t to,
                             bool require_mov_eax)
{
    std::size_t patched = 0;
    for (std::size_t i = 0; i + sizeof(from) <= size; ++i)
    {
        if (require_mov_eax && (i == 0 || code[i - 1] != 0xb8))
            continue;
        std::uint32_t value = 0;
        std::memcpy(&value, code + i, sizeof(value));
        if (value == from)
        {
            std::memcpy(code + i, &to, sizeof(to));
            ++patched;
            i += sizeof(from) - 1;
        }
    }
    return patched;
}

bool PatchRelativeCall(std::uint8_t* site, std::uint32_t expected_target,
                      std::uint32_t replacement)
{
    if (site[0] != 0xe8)
        return false;
    std::int32_t old_displacement = 0;
    std::memcpy(&old_displacement, site + 1, sizeof(old_displacement));
    const auto site_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(site));
    const auto actual_target = site_address + 5u +
        static_cast<std::uint32_t>(old_displacement);
    if (actual_target != expected_target)
        return false;
    const auto displacement = static_cast<std::int64_t>(replacement) -
        static_cast<std::int64_t>(site_address + 5u);
    if (displacement < INT32_MIN || displacement > INT32_MAX)
        return false;
    const auto new_displacement = static_cast<std::int32_t>(displacement);
    std::memcpy(site + 1, &new_displacement, sizeof(new_displacement));
    return true;
}

bool InstallRuntimeSubstitutes(std::uint8_t* original)
{
    auto* const original_entry = original + (kFunctionEntry - kImageBase);
    auto* const candidate_entry = reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uintptr_t>(&FUN_10006790));
    auto* const original_wrapper = original + (0x10003f80u - kImageBase);
    auto* const candidate_wrapper = reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uintptr_t>(&FUN_10003f80));
    DWORD old_protection = 0;
    if (!VirtualProtect(candidate_entry, kCandidateFunctionSize,
                        PAGE_EXECUTE_READWRITE, &old_protection))
        return false;
    DWORD wrapper_old_protection = 0;
    if (!VirtualProtect(candidate_wrapper, kWrapperFunctionSize,
                        PAGE_EXECUTE_READWRITE, &wrapper_old_protection))
    {
        DWORD ignored = 0;
        VirtualProtect(candidate_entry, kCandidateFunctionSize, old_protection,
                       &ignored);
        return false;
    }

    const auto rotate_recorder = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RecordRotateXOnly));
    const auto timer_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_timer_value));
    const auto query_recorder = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RecordQuery));
    const auto register_a_recorder = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestGtaApiA));
    const auto register_b_recorder = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestGtaApiB));
    const auto original_wrapper_a_sites = ReplaceImmediate(
        original_wrapper, kWrapperFunctionSize, kRegisterAEntry,
        register_a_recorder, false);
    const auto candidate_wrapper_a_sites = ReplaceImmediate(
        candidate_wrapper, kWrapperFunctionSize, kRegisterAEntry,
        register_a_recorder, false);
    const auto original_wrapper_b_sites = ReplaceImmediate(
        original_wrapper, kWrapperFunctionSize, kRegisterBEntry,
        register_b_recorder, false);
    const auto candidate_wrapper_b_sites = ReplaceImmediate(
        candidate_wrapper, kWrapperFunctionSize, kRegisterBEntry,
        register_b_recorder, false);
    const auto original_rotate_sites = ReplaceImmediate(
        original_entry, kOriginalFunctionSize, kRotateEntry,
        rotate_recorder, true);
    const auto candidate_rotate_sites = ReplaceImmediate(
        candidate_entry, kCandidateFunctionSize, kRotateEntry,
        rotate_recorder, true);
    const auto original_timer_sites = ReplaceImmediate(
        original_entry, kOriginalFunctionSize, kTimerAddress, timer_cell, false);
    const auto candidate_timer_sites = ReplaceImmediate(
        candidate_entry, kCandidateFunctionSize, kTimerAddress, timer_cell,
        false);
    const auto original_query_sites = ReplaceImmediate(
        original_entry, kOriginalFunctionSize, kQueryEntry, query_recorder,
        false);
    const auto candidate_query_sites = ReplaceImmediate(
        candidate_entry, kCandidateFunctionSize, kQueryEntry, query_recorder,
        false);
    const auto original_known_query_sites = ReplaceImmediate(
        original_entry, kOriginalFunctionSize, kKnownQueryEntry,
        query_recorder, false);
    const auto candidate_known_query_sites = ReplaceImmediate(
        candidate_entry, kCandidateFunctionSize, kKnownQueryEntry,
        query_recorder, false);
    const auto original_register_a_sites = ReplaceImmediate(
        original_entry, kOriginalFunctionSize, kRegisterAEntry,
        register_a_recorder, false);
    const auto candidate_register_a_sites = ReplaceImmediate(
        candidate_entry, kCandidateFunctionSize, kRegisterAEntry,
        register_a_recorder, false);
    const auto original_register_b_sites = ReplaceImmediate(
        original_entry, kOriginalFunctionSize, kRegisterBEntry,
        register_b_recorder, false);
    const auto candidate_register_b_sites = ReplaceImmediate(
        candidate_entry, kCandidateFunctionSize, kRegisterBEntry,
        register_b_recorder, false);

    DWORD ignored = 0;
    VirtualProtect(candidate_wrapper, kWrapperFunctionSize,
                   wrapper_old_protection, &ignored);
    VirtualProtect(candidate_entry, kCandidateFunctionSize, old_protection,
                   &ignored);
    FlushInstructionCache(GetCurrentProcess(), original_entry,
                          kOriginalFunctionSize);
    FlushInstructionCache(GetCurrentProcess(), candidate_entry,
                          kCandidateFunctionSize);
    if (original_rotate_sites != 1 || candidate_rotate_sites != 1 ||
        original_timer_sites == 0 || candidate_timer_sites == 0 ||
        original_query_sites != 1 || candidate_query_sites != 1 ||
        original_known_query_sites != 2 || candidate_known_query_sites == 0 ||
        original_wrapper_a_sites != 1 || candidate_wrapper_a_sites != 1 ||
        original_wrapper_b_sites != 1 || candidate_wrapper_b_sites != 1 ||
        original_register_a_sites != 2 || candidate_register_a_sites != 2 ||
        original_register_b_sites != 2 || candidate_register_b_sites != 2)
    {
        std::fprintf(stderr,
                     "Patch counts mismatch: rotate=%zu/%zu timer=%zu/%zu query=%zu/%zu knownQuery=%zu/%zu wrapperA=%zu/%zu wrapperB=%zu/%zu registerA=%zu/%zu registerB=%zu/%zu\n",
                     original_rotate_sites, candidate_rotate_sites,
                     original_timer_sites, candidate_timer_sites,
                     original_query_sites, candidate_query_sites,
                     original_known_query_sites, candidate_known_query_sites,
                     original_wrapper_a_sites, candidate_wrapper_a_sites,
                     original_wrapper_b_sites, candidate_wrapper_b_sites,
                     original_register_a_sites, candidate_register_a_sites,
                     original_register_b_sites, candidate_register_b_sites);
        return false;
    }
    return true;
}

void SetTimer(std::uint32_t value)
{
    g_timer_value = value;
}

void ResetRegistration(std::uint32_t query_result)
{
    std::memset(g_calls, 0, sizeof(g_calls));
    g_call_count = 0;
    g_query_observation = {};
    std::memset(g_query_trace, 0, sizeof(g_query_trace));
    g_query_api_kind = 0;
    g_query_result = query_result;
}

void ResetAdObservation(std::uint32_t query_result)
{
    std::memset(g_ad_calls, 0, sizeof(g_ad_calls));
    g_ad_call_count = 0;
    g_query_observation = {};
    std::memset(g_query_trace, 0, sizeof(g_query_trace));
    g_query_api_kind = 0;
    g_query_result = query_result;
}

bool SameRegistration(ApiCall const (&left)[2], std::uint32_t left_count,
                      ApiCall const (&right)[2], std::uint32_t right_count,
                      std::uint32_t left_cb_a, std::uint32_t left_cb_b,
                      std::uint32_t right_cb_a, std::uint32_t right_cb_b,
                      std::uint32_t mode)
{
    return left_count == 2 && right_count == 2 &&
           left[0].api == 1 && right[0].api == 1 &&
           left[1].api == 2 && right[1].api == 2 &&
           left[0].context == right[0].context &&
           left[1].context == right[1].context &&
           left[0].mode == mode && right[0].mode == mode &&
           left[1].mode == mode && right[1].mode == mode &&
           left[0].callback == left_cb_a && left[1].callback == left_cb_b &&
           right[0].callback == right_cb_a && right[1].callback == right_cb_b;
}

bool SameObservation(Observation const& left, Observation const& right,
                    std::uint8_t const* left_record,
                    std::uint8_t const* right_record);

bool RunRegistrationCase(std::uint8_t* original, std::uint32_t query_result,
                         std::uint8_t registration_flag,
                         bool should_register, std::uint8_t final_state,
                         std::uint32_t index)
{
    std::array<std::uint8_t, 0x20> original_record{};
    std::array<std::uint8_t, 0x20> candidate_record{};
    original_record.fill(0xa5);
    original_record[4] = 0;
    original_record[5] = 0x37;
    original_record[0x14] = 1;
    original_record[0x15] = registration_flag;
    const std::uint32_t registered_context = 0x12345678u;
    std::memcpy(original_record.data(), &registered_context,
                sizeof(registered_context));
    candidate_record = original_record;
    constexpr std::uint32_t param1 = 0x23456000u;
    constexpr std::uint32_t left_cb_a = 0x10003fe0u;
    constexpr std::uint32_t left_cb_b = 0x10003fb0u;
    const auto right_cb_a = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10003fe0));
    const auto right_cb_b = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10003fb0));

    ResetRegistration(query_result);
    Invocation original_invocation{};
    const auto original_entry = static_cast<std::uint32_t>(
                                    reinterpret_cast<std::uintptr_t>(original)) +
                                (kFunctionEntry - kImageBase);
    InvokeTarget(original_entry, param1, original_record.data(),
                 &original_invocation);
    const ApiCall original_calls[2] = {g_calls[0], g_calls[1]};
    const auto original_count = g_call_count;
    const auto original_query = g_query_observation;
    const auto original_after = original_record;

    ResetRegistration(query_result);
    Invocation candidate_invocation{};
    InvokeTarget(static_cast<std::uint32_t>(
                     reinterpret_cast<std::uintptr_t>(&FUN_10006790)),
                 param1, candidate_record.data(), &candidate_invocation);
    const ApiCall candidate_calls[2] = {g_calls[0], g_calls[1]};
    const auto candidate_count = g_call_count;
    const auto candidate_query = g_query_observation;

    const bool query_matches = original_query.context == param1 + 0x5a0u &&
        candidate_query.context == original_query.context &&
        original_query.selector == 0x37u &&
        candidate_query.selector == original_query.selector &&
        original_query.count == 1 && candidate_query.count == 1;
    const bool calls_match = should_register
        ? SameRegistration(original_calls, original_count, candidate_calls,
                           candidate_count, left_cb_a, left_cb_b, right_cb_a,
                           right_cb_b, query_result == 0 ? 1u : 0u)
        : original_count == 0 && candidate_count == 0;
    const bool abi_matches = original_invocation.esp_delta == 0 &&
        candidate_invocation.esp_delta == 0 &&
        original_invocation.ebx == reinterpret_cast<std::uint32_t>(original_record.data()) &&
        candidate_invocation.ebx == reinterpret_cast<std::uint32_t>(candidate_record.data()) &&
        original_invocation.esi == kEsiSentinel && candidate_invocation.esi == kEsiSentinel &&
        original_invocation.edi == kEdiSentinel && candidate_invocation.edi == kEdiSentinel;
    const bool matched = query_matches && calls_match && abi_matches &&
        original_after == candidate_record &&
        candidate_record[0x14] == final_state;
    if (!matched)
    {
        std::fprintf(stderr,
            "Registration mismatch case=%u query=%u flag=%u calls=%u/%u query-context=%08x/%08x selector=%08x/%08x state=%u/%u ABI esp=%d/%d\n",
            index, query_result, registration_flag, original_count,
            candidate_count, original_query.context, candidate_query.context,
            original_query.selector, candidate_query.selector,
            original_after[0x14], candidate_record[0x14],
            original_invocation.esp_delta, candidate_invocation.esp_delta);
        return false;
    }
    return true;
}

bool RunKnownRegistrationCase(std::uint8_t* original, std::uint8_t file_type,
                              std::uint32_t query_result,
                              std::uint8_t registration_flag,
                              std::uint32_t index)
{
    std::array<std::uint8_t, 0x20> original_record{};
    std::array<std::uint8_t, 0x20> candidate_record{};
    original_record.fill(0xa5);
    original_record[4] = file_type;
    original_record[5] = 0x42;
    original_record[0x14] = 3;
    original_record[0x15] = registration_flag;
    const std::uint32_t registered_context = 0x87654321u;
    const float rotation_value = 0.375f;
    const std::uint32_t elapsed = 500u;
    const std::uint32_t previous = 0u;
    std::memcpy(original_record.data(), &registered_context,
                sizeof(registered_context));
    std::memcpy(original_record.data() + 8, &rotation_value,
                sizeof(rotation_value));
    std::memcpy(original_record.data() + 0xc, &elapsed, sizeof(elapsed));
    std::memcpy(original_record.data() + 0x10, &previous, sizeof(previous));
    candidate_record = original_record;
    constexpr std::uint32_t param1 = 0x23456000u;
    constexpr std::uint32_t expected_ref_callback_a = 0x10003fe0u;
    constexpr std::uint32_t expected_ref_callback_b = 0x10003fb0u;
    const auto expected_candidate_callback_a = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10003fe0));
    const auto expected_candidate_callback_b = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10003fb0));

    SetTimer(0u);
    ResetRegistration(query_result);
    g_observation = {};
    Invocation original_invocation{};
    const auto original_entry = static_cast<std::uint32_t>(
                                    reinterpret_cast<std::uintptr_t>(original)) +
                                (kFunctionEntry - kImageBase);
    InvokeTarget(original_entry, param1, original_record.data(),
                 &original_invocation);
    const ApiCall original_calls[2] = {g_calls[0], g_calls[1]};
    const auto original_call_count = g_call_count;
    const auto original_query = g_query_observation;
    const auto original_observation = g_observation;
    const auto original_after = original_record;

    SetTimer(0u);
    ResetRegistration(query_result);
    g_observation = {};
    Invocation candidate_invocation{};
    InvokeTarget(static_cast<std::uint32_t>(
                     reinterpret_cast<std::uintptr_t>(&FUN_10006790)),
                 param1, candidate_record.data(), &candidate_invocation);
    const ApiCall candidate_calls[2] = {g_calls[0], g_calls[1]};
    const auto candidate_call_count = g_call_count;
    const auto candidate_query = g_query_observation;
    const auto candidate_observation = g_observation;

    const std::uint32_t expected_query_calls = query_result == 0 ? 1u : 2u;
    const bool query_matches = original_query.context == param1 + 0x5a0u &&
        candidate_query.context == original_query.context &&
        original_query.selector == 0x42u &&
        candidate_query.selector == original_query.selector &&
        original_query.count == expected_query_calls &&
        candidate_query.count == original_query.count;
    const bool should_register =
        (query_result <= 1u && registration_flag == 2u) ||
        (query_result > 1u && registration_flag == 0u);
    const auto expected_mode = query_result <= 1u ? 1u : 0u;
    const bool calls_match = should_register
        ? SameRegistration(original_calls, original_call_count,
                           candidate_calls, candidate_call_count,
                           expected_ref_callback_a,
                           expected_ref_callback_b,
                           expected_candidate_callback_a,
                           expected_candidate_callback_b, expected_mode)
        : original_call_count == 0 && candidate_call_count == 0;
    const bool abi_matches = original_invocation.esp_delta == 0 &&
        candidate_invocation.esp_delta == 0 &&
        original_invocation.ebx == reinterpret_cast<std::uint32_t>(original_record.data()) &&
        candidate_invocation.ebx == reinterpret_cast<std::uint32_t>(candidate_record.data()) &&
        original_invocation.esi == kEsiSentinel && candidate_invocation.esi == kEsiSentinel &&
        original_invocation.edi == kEdiSentinel && candidate_invocation.edi == kEdiSentinel;
    const bool matched = query_matches && calls_match && abi_matches &&
        original_after == candidate_record &&
        SameObservation(original_observation, candidate_observation,
                        original_record.data(), candidate_record.data());
    if (!matched)
    {
        std::fprintf(stderr,
            "Known-registration mismatch case=%u type=%u result=%u flag=%u calls=%u/%u q-count=%u/%u qctx=%08x/%08x qarg=%08x/%08x state=%u/%u obs=%u/%u ABI=%d/%d flags={query:%d calls:%d abi:%d record:%d obs:%d} regs={%08x,%08x,%08x}/{%08x,%08x,%08x} expectcb={%08x,%08x}/{%08x,%08x} API0={%u,%08x,%08x,%u}/{%u,%08x,%08x,%u} API1={%u,%08x,%08x,%u}/{%u,%08x,%08x,%u}\n",
            index, file_type, query_result, registration_flag,
            original_call_count, candidate_call_count,
            original_query.count, candidate_query.count,
            original_query.context, candidate_query.context,
            original_query.selector, candidate_query.selector,
            original_after[0x14], candidate_record[0x14],
            original_observation.count, candidate_observation.count,
            original_invocation.esp_delta, candidate_invocation.esp_delta,
            query_matches, calls_match, abi_matches,
            original_after == candidate_record,
            SameObservation(original_observation, candidate_observation,
                            original_record.data(), candidate_record.data()),
            original_invocation.ebx, original_invocation.esi,
            original_invocation.edi, candidate_invocation.ebx,
            candidate_invocation.esi, candidate_invocation.edi,
            expected_ref_callback_a, expected_ref_callback_b,
            expected_candidate_callback_a, expected_candidate_callback_b,
            original_calls[0].api, original_calls[0].context,
            original_calls[0].callback, original_calls[0].mode,
            candidate_calls[0].api, candidate_calls[0].context,
            candidate_calls[0].callback, candidate_calls[0].mode,
            original_calls[1].api, original_calls[1].context,
            original_calls[1].callback, original_calls[1].mode,
            candidate_calls[1].api, candidate_calls[1].context,
            candidate_calls[1].callback, candidate_calls[1].mode);
        return false;
    }
    return true;
}

void InitializeRecord(std::array<std::uint8_t, 0x20>& bytes,
                      std::uint32_t elapsed, std::uint32_t previous,
                      float input, std::uint8_t state)
{
    bytes.fill(0xa5);
    const std::uint32_t matrix_owner = 0x12345000u;
    std::memcpy(bytes.data(), &matrix_owner, sizeof(matrix_owner));
    bytes[4] = 1;   // avoid the registration state branches
    bytes[0x14] = state; // original rotate/transition state
    bytes[0x15] = 0; // allow state-machine work
    std::memcpy(bytes.data() + 8, &input, sizeof(input));
    std::memcpy(bytes.data() + 0xc, &elapsed, sizeof(elapsed));
    std::memcpy(bytes.data() + 0x10, &previous, sizeof(previous));
}

bool SameObservation(Observation const& left, Observation const& right,
                     std::uint8_t const* left_record,
                     std::uint8_t const* right_record)
{
    if (left.count != right.count)
        return false;
    if (left.count == 0)
        return true;
    std::uint32_t left_owner = 0;
    std::uint32_t right_owner = 0;
    std::memcpy(&left_owner, left_record, sizeof(left_owner));
    std::memcpy(&right_owner, right_record, sizeof(right_owner));
    return left.matrix_this == left_owner + 0x10u &&
           right.matrix_this == right_owner + 0x10u &&
           left.matrix_this == right.matrix_this &&
           left.angle_bits == right.angle_bits;
}

bool RunCase(std::uint8_t* original, std::uint32_t timer, std::uint32_t elapsed,
             std::uint32_t previous, float input, std::uint8_t state,
             std::uint32_t index)
{
    std::array<std::uint8_t, 0x20> original_record{};
    std::array<std::uint8_t, 0x20> candidate_record{};
    InitializeRecord(original_record, elapsed, previous, input, state);
    candidate_record = original_record;
    SetTimer(timer);

    Invocation original_invocation{};
    Invocation candidate_invocation{};
    g_observation = {};
    const auto original_entry = static_cast<std::uint32_t>(
                                    reinterpret_cast<std::uintptr_t>(original)) +
                                (kFunctionEntry - kImageBase);
    InvokeTarget(original_entry, 0, original_record.data(),
                 &original_invocation);
    const Observation original_observation = g_observation;
    const auto original_after = original_record;

    SetTimer(timer);
    g_observation = {};
    InvokeTarget(static_cast<std::uint32_t>(
                     reinterpret_cast<std::uintptr_t>(&FUN_10006790)),
                 0, candidate_record.data(), &candidate_invocation);
    const Observation candidate_observation = g_observation;

    const bool balanced = original_invocation.esp_delta == 0 &&
                          candidate_invocation.esp_delta == 0 &&
                          original_invocation.ebx ==
                              reinterpret_cast<std::uint32_t>(original_record.data()) &&
                          candidate_invocation.ebx ==
                              reinterpret_cast<std::uint32_t>(candidate_record.data()) &&
                          original_invocation.esi == kEsiSentinel &&
                          candidate_invocation.esi == kEsiSentinel &&
                          original_invocation.edi == kEdiSentinel &&
                          candidate_invocation.edi == kEdiSentinel;
    const bool matched = balanced && original_after == candidate_record &&
                         SameObservation(original_observation,
                                         candidate_observation,
                                         original_record.data(),
                                         candidate_record.data());
    if (!matched)
    {
        std::fprintf(stderr,
                     "Mismatch case=%u state=%u timer=%08x elapsed=%08x previous=%08x input=%g; obs orig={count:%u this:%08x angle:%08x} cand={count:%u this:%08x angle:%08x}; abi orig={esp:%d ebx:%08x esi:%08x edi:%08x} cand={esp:%d ebx:%08x esi:%08x edi:%08x}\n",
                     index, state, timer, elapsed, previous, input,
                     original_observation.count, original_observation.matrix_this,
                     original_observation.angle_bits, candidate_observation.count,
                     candidate_observation.matrix_this,
                     candidate_observation.angle_bits,
                     original_invocation.esp_delta, original_invocation.ebx,
                     original_invocation.esi, original_invocation.edi,
                     candidate_invocation.esp_delta, candidate_invocation.ebx,
                     candidate_invocation.esi, candidate_invocation.edi);
        return false;
    }
    return true;
}

bool InstallCallerSubstitutes(std::uint8_t* original,
                              std::array<std::uint8_t, 5>& saved_candidate_entry,
                              DWORD& candidate_old_protection)
{
    constexpr std::size_t original_caller_size = 0x6d;
    constexpr std::size_t candidate_caller_size = 0x66;
    auto* const original_caller = original + (kCallerEntry - kImageBase);
    auto* const candidate_caller = reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uintptr_t>(&FUN_100069e0));
    auto* const candidate_callback = reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uintptr_t>(&FUN_10006790));
    const auto pool_pointer_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_vehicle_pool_pointer_cell));
    const auto hook_recorder = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RecordVehicleHook));
    const auto manager_recorder = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10009360));

    DWORD caller_old_protection = 0;
    if (!VirtualProtect(candidate_caller, candidate_caller_size,
                        PAGE_EXECUTE_READWRITE, &caller_old_protection))
        return false;

    const auto original_pool_sites = ReplaceImmediate(
        original_caller, original_caller_size, kVehiclePoolPointer, pool_pointer_cell,
        false);
    const auto candidate_pool_sites = ReplaceImmediate(
        candidate_caller, candidate_caller_size, kVehiclePoolPointer,
        pool_pointer_cell, false);
    if (original_pool_sites != 1 || candidate_pool_sites != 1)
    {
        DWORD ignored = 0;
        VirtualProtect(candidate_caller, candidate_caller_size,
                       caller_old_protection, &ignored);
        std::fprintf(stderr, "Caller vehicle-pool pointer patch counts: %zu/%zu\n",
                     original_pool_sites, candidate_pool_sites);
        return false;
    }
    std::memcpy(original + (0x1003c248u - kImageBase), &DAT_1003c248,
                sizeof(DAT_1003c248));

    if (!PatchRelativeCall(original + (kManagerCall - kImageBase),
                           0x10009360u, manager_recorder) ||
        !PatchRelativeCall(original + (kCallbackCall - kImageBase),
                           kFunctionEntry, hook_recorder))
    {
        DWORD ignored = 0;
        VirtualProtect(candidate_caller, candidate_caller_size,
                       caller_old_protection, &ignored);
        std::fprintf(stderr, "Original caller relative-call precondition failed.\n");
        return false;
    }
    DWORD caller_ignored = 0;
    VirtualProtect(candidate_caller, candidate_caller_size,
                   caller_old_protection, &caller_ignored);
    if (!VirtualProtect(candidate_callback, saved_candidate_entry.size(),
                        PAGE_EXECUTE_READWRITE, &candidate_old_protection))
        return false;
    std::memcpy(saved_candidate_entry.data(), candidate_callback,
                saved_candidate_entry.size());
    candidate_callback[0] = 0xe9;
    const auto candidate_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(candidate_callback));
    const auto displacement = static_cast<std::int32_t>(
        static_cast<std::int64_t>(hook_recorder) -
        static_cast<std::int64_t>(candidate_address + 5u));
    std::memcpy(candidate_callback + 1, &displacement, sizeof(displacement));
    FlushInstructionCache(GetCurrentProcess(), original_caller,
                          original_caller_size);
    FlushInstructionCache(GetCurrentProcess(), candidate_caller,
                          candidate_caller_size);
    FlushInstructionCache(GetCurrentProcess(), candidate_callback,
                          saved_candidate_entry.size());
    return true;
}

void InitializeCallerFixture()
{
    g_vehicle_base_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(g_vehicle_instances));
    g_vehicle_pool_pointer_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_vehicle_base_cell));
    DAT_1003c248 = 0;
    g_caller_pool_manager = {};
    g_caller_pool_manager.pool = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(g_caller_pool));
    for (std::uint32_t index = 0; index < 64; ++index)
    {
        g_caller_pool[index] = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(g_caller_entities[index]));
        std::memset(g_caller_entities[index], 0,
                    sizeof(g_caller_entities[index]));
        const auto records_address = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(g_caller_records[index]));
        std::memcpy(g_caller_entities[index] + 0x28, &records_address,
                    sizeof(records_address));
        std::memset(g_caller_records[index], 0,
                    sizeof(g_caller_records[index]));
        for (std::uint32_t slot = 0; slot < 3; ++slot)
        {
            auto* const record = g_caller_records[index] + 0x4a0 + slot * 0x18;
            const std::uint32_t context =
                0x87654000u + index * 4u + slot;
            const float rotation = 0.25f + static_cast<float>(slot);
            const std::uint32_t elapsed = 250u + slot;
            const std::uint32_t previous = 0;
            std::memcpy(record, &context, sizeof(context));
            record[4] = 1;
            record[5] = 0x42;
            std::memcpy(record + 8, &rotation, sizeof(rotation));
            std::memcpy(record + 0xc, &elapsed, sizeof(elapsed));
            std::memcpy(record + 0x10, &previous, sizeof(previous));
            record[0x14] = 2;
            record[0x15] = 1;
        }
    }
    g_vehicle_hook_count = 0;
    std::memset(g_vehicle_hook_records, 0, sizeof(g_vehicle_hook_records));
}

bool RunCallerCase(std::uint8_t* original, std::uint32_t vehicle_index,
                   std::uint32_t case_index)
{
    InitializeCallerFixture();
    const auto vehicle_address = g_vehicle_base_cell + vehicle_index * 0xa18u;
    Invocation original_invocation{};
    const auto original_entry = static_cast<std::uint32_t>(
                                    reinterpret_cast<std::uintptr_t>(original)) +
                                (kCallerEntry - kImageBase);
    InvokeTarget(original_entry, vehicle_address, nullptr,
                 &original_invocation);
    const auto original_count = g_vehicle_hook_count;
    const VehicleHookRecord original_calls[3] = {
        g_vehicle_hook_records[0], g_vehicle_hook_records[1],
        g_vehicle_hook_records[2]};

    InitializeCallerFixture();
    Invocation candidate_invocation{};
    InvokeTarget(static_cast<std::uint32_t>(
                     reinterpret_cast<std::uintptr_t>(&FUN_100069e0)),
                 vehicle_address, nullptr, &candidate_invocation);
    const auto candidate_count = g_vehicle_hook_count;
    const VehicleHookRecord candidate_calls[3] = {
        g_vehicle_hook_records[0], g_vehicle_hook_records[1],
        g_vehicle_hook_records[2]};

    bool matched = original_count == 3 && candidate_count == 3 &&
        original_invocation.esp_delta == 0 && candidate_invocation.esp_delta == 0 &&
        original_invocation.ebx == candidate_invocation.ebx &&
        original_invocation.esi == candidate_invocation.esi &&
        original_invocation.edi == candidate_invocation.edi &&
        original_invocation.esi == kEsiSentinel &&
        original_invocation.edi == kEdiSentinel;
    for (std::uint32_t slot = 0; slot < 3; ++slot)
    {
        const auto expected_record = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(g_caller_records[vehicle_index]) +
            0x4a0u + slot * 0x18u);
        matched = matched && original_calls[slot].ebx == expected_record &&
            candidate_calls[slot].ebx == expected_record &&
            original_calls[slot].vehicle_argument == vehicle_address &&
            candidate_calls[slot].vehicle_argument == vehicle_address;
    }
    if (!matched)
    {
        std::fprintf(stderr,
            "Caller mismatch case=%u index=%u calls=%u/%u ESP=%d/%d ABI EBX=%08x/%08x vehicle=%08x expected-record0=%08x actual-record0=%08x/%08x arg0=%08x/%08x\n",
            case_index, vehicle_index, original_count, candidate_count,
            original_invocation.esp_delta, candidate_invocation.esp_delta,
            original_invocation.ebx, candidate_invocation.ebx, vehicle_address,
            static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
                g_caller_records[vehicle_index]) + 0x4a0u), original_calls[0].ebx,
            candidate_calls[0].ebx, original_calls[0].vehicle_argument,
            candidate_calls[0].vehicle_argument);
        return false;
    }
    return true;
}

bool InstallAdSubstitutes(std::uint8_t* original)
{
    constexpr std::size_t original_size = 0x105;
    constexpr std::size_t candidate_size = 0xec;
    auto* const original_entry = original + (kAdEntry - kImageBase);
    auto* const candidate_entry = reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uintptr_t>(&FUN_10006ad0));
    const auto pool_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_vehicle_pool_pointer_cell));
    const auto query2180 = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RecordQuery2180));
    const auto query2230 = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RecordQuery2230));
    const auto api_a = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestAdApiA));
    const auto api_b = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestAdApiB));
    const auto manager_stub = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10009360));

    DWORD old_protection = 0;
    if (!VirtualProtect(candidate_entry, candidate_size,
                        PAGE_EXECUTE_READWRITE, &old_protection))
        return false;
    const auto original_pool_sites = ReplaceImmediate(
        original_entry, original_size, kVehiclePoolPointer, pool_cell, false);
    const auto candidate_pool_sites = ReplaceImmediate(
        candidate_entry, candidate_size, kVehiclePoolPointer, pool_cell, false);
    const auto original_query2180_sites = ReplaceImmediate(
        original_entry, original_size, kQueryEntry, query2180, false);
    const auto candidate_query2180_sites = ReplaceImmediate(
        candidate_entry, candidate_size, kQueryEntry, query2180, false);
    const auto original_query2230_sites = ReplaceImmediate(
        original_entry, original_size, kKnownQueryEntry, query2230, false);
    const auto candidate_query2230_sites = ReplaceImmediate(
        candidate_entry, candidate_size, kKnownQueryEntry, query2230, false);
    const auto original_api_a_sites = ReplaceImmediate(
        original_entry, original_size, kRegisterAEntry, api_a, false);
    const auto candidate_api_a_sites = ReplaceImmediate(
        candidate_entry, candidate_size, kRegisterAEntry, api_a, false);
    const auto original_api_b_sites = ReplaceImmediate(
        original_entry, original_size, kRegisterBEntry, api_b, false);
    const auto candidate_api_b_sites = ReplaceImmediate(
        candidate_entry, candidate_size, kRegisterBEntry, api_b, false);
    const bool manager_call_patched = PatchRelativeCall(
        original + (kAdManagerCall - kImageBase), 0x10009360u, manager_stub);
    DWORD ignored = 0;
    VirtualProtect(candidate_entry, candidate_size, old_protection, &ignored);
    FlushInstructionCache(GetCurrentProcess(), original_entry, original_size);
    FlushInstructionCache(GetCurrentProcess(), candidate_entry, candidate_size);
    std::memcpy(original + (0x1003c248u - kImageBase), &DAT_1003c248,
                sizeof(DAT_1003c248));

    const bool counts_match = original_pool_sites == 1 &&
        candidate_pool_sites == 1 && original_query2180_sites == 1 &&
        candidate_query2180_sites == 1 && original_query2230_sites == 1 &&
        candidate_query2230_sites == 1 && original_api_a_sites == 2 &&
        candidate_api_a_sites >= 1 && original_api_b_sites == 2 &&
        candidate_api_b_sites >= 1 && manager_call_patched;
    if (!counts_match)
    {
        std::fprintf(stderr,
            "10006ad0 patch mismatch: pool=%zu/%zu q2180=%zu/%zu q2230=%zu/%zu apiA=%zu/%zu apiB=%zu/%zu manager=%u\n",
            original_pool_sites, candidate_pool_sites,
            original_query2180_sites, candidate_query2180_sites,
            original_query2230_sites, candidate_query2230_sites,
            original_api_a_sites, candidate_api_a_sites,
            original_api_b_sites, candidate_api_b_sites,
            manager_call_patched ? 1u : 0u);
    }
    return counts_match;
}

void InitializeAdFixture(std::uint32_t vehicle_index, std::uint32_t status)
{
    InitializeCallerFixture();
    auto* const vehicle = g_vehicle_instances + vehicle_index * 0xa18u;
    std::memcpy(vehicle + 0x594, &status, sizeof(status));
    constexpr std::array<std::uint8_t, 6> file_types = {0u, 2u, 3u, 4u, 6u, 1u};
    for (std::uint32_t slot = 0; slot < file_types.size(); ++slot)
    {
        auto* const record = g_caller_records[vehicle_index] + 0x328 + slot * 8;
        const std::uint32_t context = 0x8abc0000u + vehicle_index * 8u + slot;
        std::memcpy(record, &context, sizeof(context));
        record[4] = file_types[slot];
        record[5] = static_cast<std::uint8_t>(0x50u + slot);
    }
}

bool RunAdCase(std::uint8_t* original, std::uint32_t vehicle_index,
               std::uint32_t status, std::uint32_t query_result,
               std::uint32_t case_index)
{
    const auto vehicle_address = g_vehicle_base_cell + vehicle_index * 0xa18u;
    InitializeAdFixture(vehicle_index, status);
    ResetAdObservation(query_result);
    Invocation original_invocation{};
    const auto original_entry = static_cast<std::uint32_t>(
                                    reinterpret_cast<std::uintptr_t>(original)) +
                                (kAdEntry - kImageBase);
    InvokeEdiTarget(original_entry, vehicle_address, &original_invocation);
    const auto original_calls = g_ad_call_count;
    const auto original_queries = g_query_observation.count;
    const ApiCall original_api_calls[12] = {
        g_ad_calls[0], g_ad_calls[1], g_ad_calls[2], g_ad_calls[3],
        g_ad_calls[4], g_ad_calls[5], g_ad_calls[6], g_ad_calls[7],
        g_ad_calls[8], g_ad_calls[9], g_ad_calls[10], g_ad_calls[11]};
    QueryTrace original_query_calls[16]{};
    std::memcpy(original_query_calls, g_query_trace,
                sizeof(original_query_calls));

    InitializeAdFixture(vehicle_index, status);
    ResetAdObservation(query_result);
    Invocation candidate_invocation{};
    SafeInvokeEdiTarget(static_cast<std::uint32_t>(
                            reinterpret_cast<std::uintptr_t>(&FUN_10006ad0)),
                        vehicle_address, &candidate_invocation);
    const auto candidate_calls = g_ad_call_count;
    const auto candidate_queries = g_query_observation.count;

    const bool status_enabled = status == 0u || status == 1u ||
                                status == 0xbu;
    constexpr std::array<std::uint8_t, 4> eligible_slots = {0u, 1u, 2u, 3u};
    const auto expected_queries = status_enabled ? 4u : 0u;
    const auto expected_api_calls = status_enabled ? 8u : 0u;
    const bool abi_matches = original_invocation.esp_delta == 0 &&
        candidate_invocation.esp_delta == 0 &&
        original_invocation.ebx == kEbxSentinel &&
        candidate_invocation.ebx == kEbxSentinel &&
        original_invocation.esi == kEsiSentinel &&
        candidate_invocation.esi == kEsiSentinel &&
        original_invocation.edi == vehicle_address &&
        candidate_invocation.edi == vehicle_address;
    bool matched = abi_matches && original_calls == expected_api_calls &&
        candidate_calls == expected_api_calls &&
        original_queries == expected_queries &&
        candidate_queries == expected_queries;

    if (status_enabled)
    {
        for (std::uint32_t query = 0; query < expected_queries; ++query)
        {
            const auto slot = eligible_slots[query];
            const std::uint32_t expected_kind = slot == 0 ? 1u : 2u;
            const auto expected_query_context = vehicle_address + 0x5a0u;
            const auto expected_selector = static_cast<std::uint32_t>(0x50u + slot);
            const auto& left = original_query_calls[query];
            const auto& right = g_query_trace[query];
            matched = matched && left.api_kind == expected_kind &&
                right.api_kind == expected_kind &&
                left.context == expected_query_context &&
                right.context == expected_query_context &&
                left.selector == expected_selector &&
                right.selector == expected_selector &&
                left.result == query_result && right.result == query_result;

            const std::uint32_t mode = slot == 0
                ? (query_result == 0 ? 1u : 0u)
                : (query_result < 2 ? 1u : 0u);
            const auto api_index = query * 2;
            const auto ref_callback_a = 0x10003fe0u;
            const auto ref_callback_b = 0x10003fb0u;
            const auto candidate_callback_a = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(&FUN_10003fe0));
            const auto candidate_callback_b = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(&FUN_10003fb0));
            const auto expected_context = 0x8abc0000u +
                vehicle_index * 8u + slot;
            const auto& ref_a = original_api_calls[api_index];
            const auto& ref_b = original_api_calls[api_index + 1];
            const auto& cand_a = g_ad_calls[api_index];
            const auto& cand_b = g_ad_calls[api_index + 1];
            matched = matched && ref_a.api == 1 && cand_a.api == 1 &&
                ref_b.api == 2 && cand_b.api == 2 &&
                ref_a.context == expected_context && cand_a.context == expected_context &&
                ref_b.context == expected_context && cand_b.context == expected_context &&
                ref_a.callback == ref_callback_a &&
                cand_a.callback == candidate_callback_a &&
                ref_b.callback == ref_callback_b &&
                cand_b.callback == candidate_callback_b &&
                ref_a.mode == mode && cand_a.mode == mode &&
                ref_b.mode == mode && cand_b.mode == mode;
        }
    }
    if (!matched)
    {
        std::fprintf(stderr,
            "10006ad0 mismatch case=%u index=%u status=%u query=%u APIs=%u/%u queries=%u/%u ABI={%d/%d ebx=%08x/%08x esi=%08x/%08x edi=%08x/%08x}\n",
            case_index, vehicle_index, status, query_result,
            original_calls, candidate_calls, original_queries,
            candidate_queries, original_invocation.esp_delta,
            candidate_invocation.esp_delta, original_invocation.ebx,
            candidate_invocation.ebx, original_invocation.esi,
            candidate_invocation.esi, original_invocation.edi,
            candidate_invocation.edi);
        return false;
    }
    return true;
}

std::size_t PatchCallsTo(std::uint8_t* code, std::size_t size,
                         std::uint32_t old_target,
                         std::uint32_t replacement)
{
    std::size_t patched = 0;
    for (std::size_t offset = 0; offset + 5 <= size; ++offset)
    {
        if (code[offset] != 0xe8)
            continue;
        std::int32_t displacement = 0;
        std::memcpy(&displacement, code + offset + 1, sizeof(displacement));
        const auto site = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(code + offset));
        if (site + 5u + static_cast<std::uint32_t>(displacement) == old_target)
        {
            if (!PatchRelativeCall(code + offset, old_target, replacement))
                return 0;
            ++patched;
            offset += 4;
        }
    }
    return patched;
}

bool InstallCaller074d0Substitutes(std::uint8_t* original)
{
    constexpr std::size_t original_size = 0x1f7;
    constexpr std::size_t candidate_size = 0x36c;
    constexpr std::uint32_t entry = 0x100074d0u;
    auto* const original_entry = original + (entry - kImageBase);
    auto* const candidate_entry = reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uintptr_t>(&FUN_100074d0));
    const auto pool_cell = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_vehicle_pool_pointer_cell));
    const auto query = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestCallerQuery2130));
    const auto hash = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_1001ba40));
    const auto down_int_a = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10006360));
    const auto down_int_b = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RecordCaller069e0));
    const auto down_void_a = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10006a50));
    const auto down_void_b = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RecordCaller06ad0));
    const auto down_int_c = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10005860));
    const auto manager = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10009360));

    DWORD old_protection = 0;
    if (!VirtualProtect(candidate_entry, candidate_size,
                        PAGE_EXECUTE_READWRITE, &old_protection))
        return false;
    const auto original_pool_sites = ReplaceImmediate(
        original_entry, original_size, kVehiclePoolPointer, pool_cell, false);
    const auto candidate_pool_sites = ReplaceImmediate(
        candidate_entry, candidate_size, kVehiclePoolPointer, pool_cell, false);
    const auto original_query_sites = ReplaceImmediate(
        original_entry, original_size, 0x006c2130u, query, false);
    const auto candidate_query_sites = ReplaceImmediate(
        candidate_entry, candidate_size, 0x006c2130u, query, false);
    const auto candidate_069e0_sites = PatchCallsTo(
        candidate_entry, candidate_size,
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&FUN_100069e0)),
        down_int_b);
    const auto candidate_06ad0_sites = PatchCallsTo(
        candidate_entry, candidate_size,
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&FUN_10006ad0)),
        down_void_b);

    bool original_calls = true;
    original_calls = original_calls && PatchRelativeCall(
        original + (0x100074dcu - kImageBase), 0x10009360u, manager);
    original_calls = original_calls && PatchRelativeCall(
        original + (0x10007694u - kImageBase), 0x1001ba40u, hash);
    original_calls = original_calls && PatchRelativeCall(
        original + (0x100076a2u - kImageBase), 0x10006360u, down_int_a);
    original_calls = original_calls && PatchRelativeCall(
        original + (0x100076a8u - kImageBase), 0x100069e0u, down_int_b);
    original_calls = original_calls && PatchRelativeCall(
        original + (0x100076adu - kImageBase), 0x10006a50u, down_void_a);
    original_calls = original_calls && PatchRelativeCall(
        original + (0x100076b2u - kImageBase), 0x10006ad0u, down_void_b);
    original_calls = original_calls && PatchRelativeCall(
        original + (0x100076b8u - kImageBase), 0x10005860u, down_int_c);
    DWORD ignored = 0;
    VirtualProtect(candidate_entry, candidate_size, old_protection, &ignored);
    FlushInstructionCache(GetCurrentProcess(), original_entry, original_size);
    FlushInstructionCache(GetCurrentProcess(), candidate_entry, candidate_size);

    const bool passed = original_pool_sites == 1 && candidate_pool_sites == 1 &&
        original_query_sites == 4 && candidate_query_sites == 4 &&
        candidate_069e0_sites == 1 && candidate_06ad0_sites == 1 &&
        original_calls;
    if (!passed)
        std::fprintf(stderr,
            "100074d0 patch mismatch pool=%zu/%zu query=%zu/%zu calls=%zu/%zu orig=%u\n",
            original_pool_sites, candidate_pool_sites, original_query_sites,
            candidate_query_sites, candidate_069e0_sites,
            candidate_06ad0_sites, original_calls ? 1u : 0u);
    return passed;
}

struct Caller074d0Globals
{
    std::uint32_t aedc;
    std::uint32_t aee0;
    std::uint32_t aee4;
    std::uint32_t aee8;
    std::uint32_t aeec;
    std::uint8_t aef0;
    std::int32_t aef4;
    std::uint32_t c1ec;
    std::int32_t c1fc;
    std::uint32_t bc78;
};

void ResetCaller074d0Output(std::uint8_t* original)
{
    std::memset(original + (0x1003aedcu - kImageBase), 0, 0x1c);
    std::memset(original + (0x1003bc78u - kImageBase), 0, 4);
    std::memset(original + (0x1003c1ecu - kImageBase), 0, 4);
    std::memset(original + (0x1003c1fcu - kImageBase), 0, 4);
    std::memcpy(original + (0x1003c248u - kImageBase), &DAT_1003c248,
                sizeof(DAT_1003c248));
    DAT_1003aedc = 0;
    DAT_1003aee0 = 0;
    DAT_1003aee4 = 0;
    DAT_1003aee8 = 0;
    DAT_1003aeec = 0;
    DAT_1003aef0 = 0;
    DAT_1003aef4 = 0;
    DAT_1003c1ec = 0;
    DAT_1003c1fc = 0;
    DAT_1003bc78 = 0;
    std::memset(g_caller_query_records, 0, sizeof(g_caller_query_records));
    std::memset(g_caller_downstream, 0, sizeof(g_caller_downstream));
    for (auto& result : g_caller_query_result)
        result = 0;
    g_caller_query_count = 0;
    g_caller_hash_ecx = 0;
    g_caller_hash_edx = 0;
    g_caller_hash_float = 0;
    g_caller_downstream_count = 0;
}

Caller074d0Globals ReadCaller074d0Globals(std::uint8_t* original)
{
    Caller074d0Globals result{};
    std::memcpy(&result.aedc, original + (0x1003aedcu - kImageBase), 4);
    std::memcpy(&result.aee0, original + (0x1003aee0u - kImageBase), 4);
    std::memcpy(&result.aee4, original + (0x1003aee4u - kImageBase), 4);
    std::memcpy(&result.aee8, original + (0x1003aee8u - kImageBase), 4);
    std::memcpy(&result.aeec, original + (0x1003AEECu - kImageBase), 4);
    std::memcpy(&result.aef0, original + (0x1003aef0u - kImageBase), 1);
    std::memcpy(&result.aef4, original + (0x1003aef4u - kImageBase), 4);
    std::memcpy(&result.c1ec, original + (0x1003c1ecu - kImageBase), 4);
    std::memcpy(&result.c1fc, original + (0x1003c1fcu - kImageBase), 4);
    std::memcpy(&result.bc78, original + (0x1003bc78u - kImageBase), 4);
    return result;
}

Caller074d0Globals ReadCaller074d0CandidateGlobals()
{
    return {DAT_1003aedc, DAT_1003aee0, DAT_1003aee4, DAT_1003aee8,
            DAT_1003aeec, DAT_1003aef0, DAT_1003aef4, DAT_1003c1ec,
            DAT_1003c1fc, DAT_1003bc78};
}

void InitializeCaller074d0Fixture(std::uint8_t* original,
                                  std::uint32_t vehicle_index,
                                  std::uint32_t status,
                                  std::uint8_t flags,
                                  std::uint32_t test_index,
                                  std::array<std::uint32_t, 4> const& results)
{
    InitializeCallerFixture();
    ResetCaller074d0Output(original);
    auto* const vehicle = g_vehicle_instances + vehicle_index * 0xa18u;
    std::memcpy(vehicle + 0x594, &status, 4);
    std::memcpy(vehicle + 0x584, &flags, 1);
    const std::int16_t model = static_cast<std::int16_t>(0x120 + test_index);
    std::memcpy(vehicle + 0x22, &model, 2);
    const float value = -0.375f + static_cast<float>(test_index) * 0.125f;
    std::memcpy(vehicle + 0x4b0, &value, 4);
    auto* const entity = g_caller_entities[vehicle_index];
    const std::array<std::uint32_t, 5> words = {
        0xa5000000u + test_index, 0x11223344u + test_index,
        0x55667788u + test_index, 0x99aabbccu + test_index,
        0xddeeff00u + test_index};
    std::memcpy(entity + 4, &words[0], 4);
    std::memcpy(entity + 8, &words[1], 4);
    std::memcpy(entity + 12, &words[2], 4);
    std::memcpy(entity + 16, &words[3], 4);
    std::memcpy(entity + 20, &words[4], 4);
    entity[24] = static_cast<std::uint8_t>(0x40u + test_index);
    for (std::uint32_t selector = 0; selector < 4; ++selector)
        g_caller_query_result[selector] = results[selector];
    std::memcpy(original + (0x1003c248u - kImageBase), &DAT_1003c248, 4);
}

bool SameCaller074d0Globals(Caller074d0Globals const& left,
                            Caller074d0Globals const& right)
{
    return left.aedc == right.aedc && left.aee0 == right.aee0 &&
        left.aee4 == right.aee4 && left.aee8 == right.aee8 &&
        left.aeec == right.aeec && left.aef0 == right.aef0 &&
        left.aef4 == right.aef4 && left.c1ec == right.c1ec &&
        left.c1fc == right.c1fc && left.bc78 == right.bc78;
}

bool RunCaller074d0Case(std::uint8_t* original, std::uint32_t status,
                        std::uint8_t flags,
                        std::array<std::uint32_t, 4> const& results,
                        std::uint32_t test_index)
{
    constexpr std::uint32_t vehicle_index = 17;
    const auto vehicle = g_vehicle_base_cell + vehicle_index * 0xa18u;
    const auto original_entry = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(original)) +
        (0x100074d0u - kImageBase);
    const auto candidate_entry = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_100074d0));
    InitializeCaller074d0Fixture(original, vehicle_index, status, flags,
                                 test_index, results);
    Invocation left_invocation{};
    auto* const sentinel = reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(kEbxSentinel));
    InvokeTarget(original_entry, vehicle, sentinel, &left_invocation);
    const auto left_return = g_invoke_eax;
    const auto left_globals = ReadCaller074d0Globals(original);
    const auto left_query_count = g_caller_query_count;
    CallerQueryRecord left_queries[8]{};
    std::memcpy(left_queries, g_caller_query_records, sizeof(left_queries));
    const auto left_hash_ecx = g_caller_hash_ecx;
    const auto left_hash_edx = g_caller_hash_edx;
    const float left_hash_float = g_caller_hash_float;
    const auto left_downstream_count = g_caller_downstream_count;
    CallerDownstreamRecord left_downstream[8]{};
    std::memcpy(left_downstream, g_caller_downstream,
                sizeof(left_downstream));

    InitializeCaller074d0Fixture(original, vehicle_index, status, flags,
                                 test_index, results);
    Invocation right_invocation{};
    InvokeTarget(candidate_entry, vehicle, sentinel, &right_invocation);
    const auto right_return = g_invoke_eax;
    const auto right_globals = ReadCaller074d0CandidateGlobals();
    const float right_hash_float = g_caller_hash_float;

    bool matched = left_return == vehicle && right_return == vehicle &&
        left_invocation.esp_delta == 0 && right_invocation.esp_delta == 0 &&
        left_invocation.ebx == right_invocation.ebx &&
        left_invocation.esi == right_invocation.esi &&
        left_invocation.edi == right_invocation.edi &&
        SameCaller074d0Globals(left_globals, right_globals) &&
        left_query_count == g_caller_query_count &&
        left_downstream_count == g_caller_downstream_count &&
        left_hash_ecx == g_caller_hash_ecx &&
        left_hash_edx == g_caller_hash_edx &&
        std::memcmp(&left_hash_float, &right_hash_float,
                    sizeof(left_hash_float)) == 0 &&
        std::memcmp(left_queries, g_caller_query_records,
                    sizeof(left_queries)) == 0 &&
        std::memcmp(left_downstream, g_caller_downstream,
                    sizeof(left_downstream)) == 0 &&
        left_query_count <= 8 && left_downstream_count == 5;
    for (std::uint32_t index = 0; index < left_query_count && matched; ++index)
        matched = left_queries[index].receiver == vehicle + 0x5a0u &&
                  left_queries[index].edx_in == 0 &&
                  left_queries[index].edx_out ==
                      (0xa0000000u + left_queries[index].selector);
    if (!matched)
        std::fprintf(stderr,
            "100074d0 mismatch case=%u status=%u flags=%02x query=%u/%u downstream=%u/%u hash={%08x/%08x %08x/%08x} stack=%d/%d globals={%08x,%08x,%08x,%08x,%08x,%02x,%08x,%08x,%08x,%08x}/{%08x,%08x,%08x,%08x,%08x,%02x,%08x,%08x,%08x,%08x} traces=%u/%u calls=%u/%u\n",
            test_index, status, flags, left_query_count, g_caller_query_count,
            left_downstream_count, g_caller_downstream_count,
            left_hash_ecx, g_caller_hash_ecx, left_hash_edx,
            g_caller_hash_edx, left_invocation.esp_delta,
            right_invocation.esp_delta,
            left_globals.aedc,left_globals.aee0,left_globals.aee4,
            left_globals.aee8,left_globals.aeec,left_globals.aef0,
            static_cast<std::uint32_t>(left_globals.aef4),left_globals.c1ec,
            static_cast<std::uint32_t>(left_globals.c1fc),left_globals.bc78,
            right_globals.aedc,right_globals.aee0,right_globals.aee4,
            right_globals.aee8,right_globals.aeec,right_globals.aef0,
            static_cast<std::uint32_t>(right_globals.aef4),right_globals.c1ec,
            static_cast<std::uint32_t>(right_globals.c1fc),right_globals.bc78,
            std::memcmp(left_queries,g_caller_query_records,sizeof(left_queries)),
            std::memcmp(left_downstream,g_caller_downstream,sizeof(left_downstream)),
            left_return,right_return);
    return matched;
}
} // namespace

int wmain(int argc, wchar_t** argv)
{
    static_assert(sizeof(void*) == 4, "Run this harness as PE32/x86.");
    if (argc != 2)
    {
        std::fwprintf(stderr, L"usage: harness <pinned-ImVehFt.asi>\n");
        return 2;
    }
    auto* original = MapReference(argv[1]);
    if (!original)
    {
        std::fprintf(stderr, "Could not map original ASI at its preferred base.\n");
        return 4;
    }
    if (!InstallRuntimeSubstitutes(original))
        return 5;
    auto const* image = original;
    std::memcpy(&DAT_10024e80, image + (0x10024e80u - kImageBase),
                sizeof(DAT_10024e80));
    std::memcpy(&DAT_10024e90, image + (0x10024e90u - kImageBase),
                sizeof(DAT_10024e90));
    std::memcpy(&DAT_10024e98, image + (0x10024e98u - kImageBase),
                sizeof(DAT_10024e98));
    std::memcpy(&DAT_10024ea0, image + (0x10024ea0u - kImageBase),
                sizeof(DAT_10024ea0));

    constexpr std::array<std::array<std::uint32_t, 3>, 4> registration_cases = {{
        {{0u, 2u, 0u}}, // query says absent; deregister and clear local state
        {{0u, 1u, 1u}}, // query says absent; no registration transition
        {{1u, 0u, 2u}}, // query says present; register and enter state 2
        {{1u, 2u, 1u}}, // query says present; no registration transition
    }};
    std::uint32_t registration_count = 0;
    for (const auto& test : registration_cases)
    {
        const auto query_result = test[0];
        const auto registration_flag = static_cast<std::uint8_t>(test[1]);
        const bool should_register = (query_result == 0 && registration_flag == 2) ||
                                     (query_result != 0 && registration_flag == 0);
        if (!RunRegistrationCase(original, query_result, registration_flag,
                                 should_register,
                                 static_cast<std::uint8_t>(test[2]),
                                 registration_count))
            return 5;
        ++registration_count;
    }
    constexpr std::array<std::uint8_t, 3> known_types = {2u, 3u, 4u};
    constexpr std::array<std::array<std::uint32_t, 2>, 4> known_cases = {{
        {{0u, 2u}}, // known/not-installed; register in mode 1
        {{1u, 2u}}, // second query confirms known; register in mode 1
        {{2u, 1u}}, // unknown type and non-transition flag
        {{2u, 0u}}, // unknown type; unregister in mode 0
    }};
    std::uint32_t known_registration_count = 0;
    for (const auto file_type : known_types)
    {
        for (const auto& test : known_cases)
        {
            if (!RunKnownRegistrationCase(
                    original, file_type, test[0],
                    static_cast<std::uint8_t>(test[1]),
                    known_registration_count))
                return 5;
            ++known_registration_count;
        }
    }

    constexpr std::array<std::uint32_t, 6> timers = {
        0u, 1u, 0x7fffffffu, 0x80000000u, 0xfffffffeu, 0xffffffffu};
    constexpr std::array<std::uint32_t, 6> previous_values = {
        0u, 1u, 0x7fffffffu, 0x80000000u, 0xfffffffeu, 0xffffffffu};
    constexpr std::array<std::uint32_t, 8> elapsed_values = {
        0u, 1u, 2u, 0x7fffffffu, 0x80000000u, 0xfffffffdu,
        0xfffffffeu, 0xffffffffu};
    constexpr std::array<float, 9> inputs = {
        0.0f, -0.0f, 0.25f, -0.25f, 1.0f, -1.0f,
        100.0f, 1.0e-20f, 1.0e20f};

    std::uint32_t cases = 0;
    constexpr std::array<std::uint8_t, 2> states = {2u, 3u};
    for (const auto state : states)
    {
      for (const auto timer : timers)
      {
        for (const auto previous : previous_values)
        {
            const std::uint32_t delta = timer - previous;
            for (const auto elapsed : elapsed_values)
            {
                for (const auto input : inputs)
                {
                    if (!RunCase(original, timer, elapsed, previous, input,
                                 state, cases))
                        return 5;
                    ++cases;
                }
                if (!RunCase(original, timer, delta, previous, 0.75f, state,
                             cases))
                    return 5;
                ++cases;
            }
        }
      }
    }

    std::array<std::uint8_t, 5> saved_candidate_entry{};
    DWORD candidate_entry_protection = 0;
    if (!InstallCallerSubstitutes(original, saved_candidate_entry,
                                  candidate_entry_protection))
        return 6;
    constexpr std::array<std::uint32_t, 3> vehicle_indices = {0u, 1u, 17u};
    std::uint32_t caller_cases = 0;
    bool caller_tests_passed = true;
    for (const auto vehicle_index : vehicle_indices)
    {
        if (!RunCallerCase(original, vehicle_index, caller_cases))
        {
            caller_tests_passed = false;
            break;
        }
        ++caller_cases;
    }
    auto* const candidate_callback = reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uintptr_t>(&FUN_10006790));
    DWORD ignored = 0;
    if (!VirtualProtect(candidate_callback, saved_candidate_entry.size(),
                        PAGE_EXECUTE_READWRITE, &ignored))
        return 6;
    std::memcpy(candidate_callback, saved_candidate_entry.data(),
                saved_candidate_entry.size());
    VirtualProtect(candidate_callback, saved_candidate_entry.size(),
                    candidate_entry_protection, &ignored);
    FlushInstructionCache(GetCurrentProcess(), candidate_callback,
                          saved_candidate_entry.size());
    if (!caller_tests_passed)
        return 6;

    if (!InstallAdSubstitutes(original))
        return 7;
    constexpr std::array<std::uint32_t, 4> ad_statuses = {
        0u, 1u, 0xbu, 2u};
    constexpr std::array<std::uint32_t, 3> ad_query_results = {0u, 1u, 2u};
    std::uint32_t ad_cases = 0;
    for (const auto status : ad_statuses)
    {
        for (const auto query_result : ad_query_results)
        {
            if (!RunAdCase(original, 17u, status, query_result, ad_cases))
                return 7;
            ++ad_cases;
        }
    }

    if (!InstallCaller074d0Substitutes(original))
        return 8;
    constexpr std::array<std::uint32_t, 4> caller_statuses = {
        0u, 1u, 2u, 0xbu};
    constexpr std::array<std::uint8_t, 3> caller_flags = {
        0x00u, 0x05u, 0x0fu};
    constexpr std::array<std::array<std::uint32_t, 4>, 2> caller_results = {{
        {{0u, 0u, 0u, 0u}},
        {{1u, 0u, 1u, 0u}},
    }};
    std::uint32_t caller074d0_cases = 0;
    for (const auto status : caller_statuses)
    {
        for (const auto flags : caller_flags)
        {
            for (const auto& results : caller_results)
            {
                if (!RunCaller074d0Case(original, status, flags, results,
                                         caller074d0_cases))
                    return 8;
                ++caller074d0_cases;
            }
        }
    }

    std::printf("PASS: %u state-2/state-3 arithmetic cases, %u direct registration cases, %u wrapper cases, %u mapped 0x100069e0 caller cases, %u mapped 0x10006ad0 query/API cases, and %u mapped 0x100074d0 caller cases; callback records, vehicle args, query receiver/register/stack contracts, x87 hash input, global outputs, downstream calls, stack balance, and callee-saved registers matched.\n",
                cases, registration_count, known_registration_count,
                caller_cases, ad_cases, caller074d0_cases);
    std::puts("LIMIT: query/GTA APIs and CMatrix::SetRotateXOnly are deterministic recorders; this does not cover live GTA side effects, unrelated states/callers, initialization, production ASI linking/layout, or in-game behavior.");
    return 0;
}
