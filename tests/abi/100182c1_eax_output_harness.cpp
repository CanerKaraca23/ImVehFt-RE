#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

extern "C" int __cdecl FUN_100182c1(
    std::uint32_t*, const char*, std::uint32_t, int, std::uint8_t);

extern "C" std::uintptr_t DAT_1003c420[1] = {};
extern "C" std::uint8_t DAT_10039a0c = 0;

static std::uint8_t g_osfile_table[32 * 0x40] = {};
static unsigned long g_doserrno = 0;
static int g_errno = 0;
static int g_invalid_parameter_calls = 0;
static bool g_fail_os_handle_allocation = true;

extern "C" int __cdecl FUN_1001b1a5(std::uint32_t* value)
{
    *value = 0;
    return 0;
}

extern "C" unsigned long* __cdecl ___doserrno()
{
    return &g_doserrno;
}

extern "C" int* __cdecl __errno()
{
    return &g_errno;
}

extern "C" void __stdcall FUN_1001189f()
{
    ++g_invalid_parameter_calls;
}

extern "C" std::uint32_t __cdecl __alloc_osfhnd()
{
    return g_fail_os_handle_allocation ? 0xffffffffU : 0U;
}

extern "C" void __cdecl __dosmaperr(DWORD) {}
extern "C" void __cdecl __set_osfhnd(int handle, std::intptr_t os_handle)
{
    std::memcpy(g_osfile_table + handle * 0x40, &os_handle, sizeof(os_handle));
}
extern "C" long __cdecl __lseek_nolock(int, long, int) { return -1; }
extern "C" int __cdecl __close_nolock(int) { return 0; }
extern "C" int __cdecl __read_nolock(int, void*, unsigned int) { return 0; }
extern "C" int __cdecl __chsize_nolock(int, std::int64_t) { return 0; }
extern "C" std::int64_t __cdecl __lseeki64_nolock(int, std::int64_t, int) { return -1; }
extern "C" int __cdecl __write(int, const void*, unsigned int) { return 0; }
extern "C" void __cdecl __free_osfhnd(int) {}

extern "C" __declspec(noreturn) void __cdecl __invoke_watson(
    const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t)
{
    ExitProcess(3);
}

static int invoke_with_eax_output(
    std::uint32_t* output_handle,
    std::uint32_t* local_context,
    const char* filename,
    std::uint32_t flags,
    int share_mode,
    std::uint32_t security_flags)
{
    int result = -1;
    __asm {
        push security_flags
        push share_mode
        push flags
        push filename
        push local_context
        mov eax, output_handle
        call FUN_100182c1
        add esp, 14h
        mov result, eax
    }
    return result;
}

static bool run_case(
    const char* label,
    std::uint32_t flags,
    int expected_result,
    int expected_errno,
    int expected_invalid_calls)
{
    std::uint32_t output_handle = 0x13572468U;
    std::uint32_t local_context = 0;
    g_errno = 0;
    g_doserrno = 99;
    g_invalid_parameter_calls = 0;
    g_fail_os_handle_allocation = true;

    const int result = invoke_with_eax_output(
        &output_handle, &local_context, "unused-by-stubbed-error-path",
        flags, 0x10, 0);
    const bool passed = result == expected_result
        && output_handle == 0xffffffffU
        && g_errno == expected_errno
        && g_doserrno == 0
        && g_invalid_parameter_calls == expected_invalid_calls;

    std::printf(
        "%s: %s (ret=%d out=0x%08X errno=%d doserrno=%lu invalid=%d)\n",
        label, passed ? "PASS" : "FAIL", result, output_handle,
        g_errno, g_doserrno, g_invalid_parameter_calls);
    return passed;
}

static bool run_successful_open_case(
    const char* label, std::uint32_t flags, bool remove_before_open = false)
{
    char temp_directory[MAX_PATH] = {};
    char filename[MAX_PATH] = {};
    if (GetTempPathA(MAX_PATH, temp_directory) == 0
        || GetTempFileNameA(temp_directory, "ivf", 0, filename) == 0)
    {
        std::printf("%s: FAIL (temporary file setup failed)\n", label);
        return false;
    }
    if (remove_before_open && !DeleteFileA(filename))
    {
        std::printf("%s: FAIL (could not prepare new-file path)\n", label);
        DeleteFileA(filename);
        return false;
    }

    std::memset(g_osfile_table, 0, sizeof(g_osfile_table));
    DAT_1003c420[0] = reinterpret_cast<std::uintptr_t>(g_osfile_table);
    g_errno = 0;
    g_doserrno = 0;
    g_invalid_parameter_calls = 0;
    g_fail_os_handle_allocation = false;

    std::uint32_t output_handle = 0x13572468U;
    std::uint32_t local_context = 0;
    const int result = invoke_with_eax_output(
        &output_handle, &local_context, filename, flags, 0x10, 0);

    HANDLE os_handle = INVALID_HANDLE_VALUE;
    std::memcpy(&os_handle, g_osfile_table, sizeof(os_handle));
    const bool passed = result == 0
        && output_handle == 0
        && local_context == 1
        && os_handle != INVALID_HANDLE_VALUE
        && os_handle != nullptr
        && GetFileType(os_handle) == FILE_TYPE_DISK
        && g_errno == 0
        && g_invalid_parameter_calls == 0;

    std::printf(
        "%s: %s (ret=%d fd=%u context=%u os_handle=%p errno=%d)\n",
        label,
        passed ? "PASS" : "FAIL", result, output_handle, local_context,
        os_handle, g_errno);

    if (os_handle != INVALID_HANDLE_VALUE && os_handle != nullptr)
        CloseHandle(os_handle);
    DeleteFileA(filename);
    return passed;
}

int main()
{
    const bool invalid_mode = run_case("invalid access mode", 3, 22, 22, 1);
    const bool no_access_allocation_failure = run_case(
        "no-access mode reaches OS-handle allocation", 0, 24, 24, 0);
    const bool write_mode_allocation_failure = run_case(
        "write mode reaches OS-handle allocation", 1, 24, 24, 0);
    const bool read_write_mode_allocation_failure = run_case(
        "read-write mode reaches OS-handle allocation", 2, 24, 24, 0);
    const bool successful_read_open = run_successful_open_case(
        "real CreateFileA read open", 0);
    const bool successful_write_open = run_successful_open_case(
        "real CreateFileA write open", 1);
    const bool successful_read_write_open = run_successful_open_case(
        "real CreateFileA read-write open", 2);
    const bool successful_open_always = run_successful_open_case(
        "real CreateFileA OPEN_ALWAYS", 1 | 0x100);
    const bool successful_truncate_existing = run_successful_open_case(
        "real CreateFileA TRUNCATE_EXISTING", 1 | 0x200);
    const bool successful_create_always = run_successful_open_case(
        "real CreateFileA CREATE_ALWAYS", 1 | 0x300);
    const bool successful_create_new = run_successful_open_case(
        "real CreateFileA CREATE_NEW", 1 | 0x500, true);
    return invalid_mode && no_access_allocation_failure
            && write_mode_allocation_failure && read_write_mode_allocation_failure
            && successful_read_open && successful_write_open
            && successful_read_write_open && successful_open_always
            && successful_truncate_existing && successful_create_always
            && successful_create_new
        ? 0
        : 1;
}
