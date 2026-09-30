#include <cstdint>
#include <windows.h>

extern "C" {
std::uintptr_t __security_cookie = 0x12345678U;
DWORD DAT_10029490 = 0xBB40E64EU;
DWORD DAT_10029494 = ~0xBB40E64EU;
volatile unsigned char gs_probe_sink = 0;
}

extern "C" void __cdecl ___security_init_cookie();
extern "C" void __cdecl gs_guarded_probe();

extern "C" void __cdecl gs_consume_buffer(unsigned char* buffer)
{
    gs_probe_sink = buffer[0];
}

static void write_text(const char* text)
{
    DWORD written = 0;
    DWORD length = 0;
    while (text[length]) {
        ++length;
    }
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteFile(output, text, length, &written, nullptr);
}

static bool has_sync_control(const char* text)
{
    static const char needle[] = "sync-control";
    for (; *text; ++text) {
        unsigned int i = 0;
        while (needle[i] && text[i] == needle[i]) {
            ++i;
        }
        if (!needle[i]) {
            return true;
        }
    }
    return false;
}

extern "C" __declspec(noreturn) void __cdecl ___report_gsfailure()
{
    write_text("CANDIDATE_GS_CHECK_FAILED\n");
    ExitProcess(86);
}

extern "C" void* __cdecl memset(void* destination, int value, size_t count)
{
    volatile unsigned char* bytes = static_cast<volatile unsigned char*>(destination);
    while (count--) {
        *bytes++ = static_cast<unsigned char>(value);
    }
    return destination;
}

extern "C" void __cdecl probe_entry()
{
    ___security_init_cookie();
    if (has_sync_control(GetCommandLineA())) {
        DAT_10029490 = static_cast<DWORD>(__security_cookie);
        DAT_10029494 = ~DAT_10029490;
        write_text("SYNC_CONTROL\n");
    } else {
        write_text("ACTUAL_LEGACY_INITIALIZER\n");
    }

    gs_guarded_probe();
    write_text("CANDIDATE_GS_CHECK_PASSED\n");
    ExitProcess(0);
}
