#include <windows.h>
#include <cstdint>
#include <cstdio>

extern "C" void ___security_init_cookie();
extern "C" int __cdecl record_startup(
    std::int32_t, std::int32_t, std::uint32_t);
extern void __stdcall entry(std::uint32_t, std::int32_t, std::int32_t);
extern "C" int __stdcall entry_original_assembly(
    std::uint32_t, std::int32_t, std::int32_t);

struct CallRecord
{
    volatile LONG cookie_calls;
    volatile LONG startup_calls;
    volatile std::int32_t startup_ecx;
    volatile std::int32_t startup_edx;
    volatile std::uint32_t startup_stack_arg;
};

static CallRecord g_record{};

extern "C" void ___security_init_cookie()
{
    InterlockedIncrement(&g_record.cookie_calls);
}

extern "C" int __cdecl record_startup(
    std::int32_t ecx_arg,
    std::int32_t edx_arg,
    std::uint32_t stack_arg)
{
    InterlockedIncrement(&g_record.startup_calls);
    g_record.startup_ecx = ecx_arg;
    g_record.startup_edx = edx_arg;
    g_record.startup_stack_arg = stack_arg;
    return static_cast<int>(
        0x51a70000u ^ static_cast<std::uint32_t>(ecx_arg) ^
        (_rotl(static_cast<std::uint32_t>(edx_arg), 7)) ^
        (_rotl(stack_arg, 17)));
}

extern "C" __declspec(naked) int __fastcall ___DllMainCRTStartup(
    std::int32_t, std::int32_t, std::uint32_t)
{
    __asm {
        push    dword ptr [esp + 4]
        push    edx
        push    ecx
        call    record_startup
        add     esp, 0Ch
        ret
    }
}

extern "C" __declspec(naked) int __cdecl call_candidate_entry(
    std::uint32_t, std::int32_t, std::int32_t)
{
    __asm {
        push    ebp
        mov     ebp, esp
        push    dword ptr [ebp + 10h]
        push    dword ptr [ebp + 0Ch]
        push    dword ptr [ebp + 8]
        call    entry
        mov     esp, ebp
        pop     ebp
        ret
    }
}

extern "C" __declspec(naked) int __cdecl call_original_entry_assembly(
    std::uint32_t, std::int32_t, std::int32_t)
{
    __asm {
        push    ebp
        mov     ebp, esp
        push    dword ptr [ebp + 10h]
        push    dword ptr [ebp + 0Ch]
        push    dword ptr [ebp + 8]
        call    entry_original_assembly
        mov     esp, ebp
        pop     ebp
        ret
    }
}

extern "C" __declspec(naked) int __stdcall entry_original_assembly(
    std::uint32_t, std::int32_t, std::int32_t)
{
    __asm {
        mov     edi, edi
        push    ebp
        mov     ebp, esp
        cmp     dword ptr [ebp + 0Ch], 1
        jnz     original_skip_cookie
        call    ___security_init_cookie
    original_skip_cookie:
        push    dword ptr [ebp + 8]
        mov     ecx, dword ptr [ebp + 10h]
        mov     edx, dword ptr [ebp + 0Ch]
        call    ___DllMainCRTStartup
        pop     ecx
        pop     ebp
        ret     0Ch
    }
}

struct Snapshot
{
    int result;
    LONG cookie_calls;
    LONG startup_calls;
    std::int32_t startup_ecx;
    std::int32_t startup_edx;
    std::uint32_t startup_stack_arg;
};

using EntryCall = int(__cdecl*)(std::uint32_t, std::int32_t, std::int32_t);

static Snapshot invoke(EntryCall call, std::uint32_t p1, std::int32_t p2,
                       std::int32_t p3)
{
    g_record = {};
    int const result = call(p1, p2, p3);
    return {
        result,
        g_record.cookie_calls,
        g_record.startup_calls,
        g_record.startup_ecx,
        g_record.startup_edx,
        g_record.startup_stack_arg
    };
}

static bool same(const Snapshot& left, const Snapshot& right)
{
    return left.result == right.result &&
           left.cookie_calls == right.cookie_calls &&
           left.startup_calls == right.startup_calls &&
           left.startup_ecx == right.startup_ecx &&
           left.startup_edx == right.startup_edx &&
           left.startup_stack_arg == right.startup_stack_arg;
}

int main()
{
    std::uint32_t state = 0x100111b3u;
    unsigned mismatches = 0;
    constexpr unsigned kCases = 10000;

    for (unsigned index = 0; index != kCases; ++index)
    {
        state = state * 1664525u + 1013904223u;
        std::uint32_t const p1 = state;
        state = state * 1664525u + 1013904223u;
        std::int32_t const p2 = index < 3
            ? static_cast<std::int32_t>(index == 0 ? 1 : index - 1)
            : static_cast<std::int32_t>(state);
        state = state * 1664525u + 1013904223u;
        std::int32_t const p3 = static_cast<std::int32_t>(state);

        Snapshot const original = invoke(
            call_original_entry_assembly, p1, p2, p3);
        Snapshot const candidate = invoke(
            call_candidate_entry, p1, p2, p3);
        if (!same(original, candidate))
        {
            if (mismatches < 5)
            {
                std::printf(
                    "mismatch case=%u p1=%08lx p2=%08lx p3=%08lx "
                    "orig_ret=%08lx cand_ret=%08lx orig_ecx=%08lx "
                    "cand_ecx=%08lx orig_edx=%08lx cand_edx=%08lx\n",
                    index, p1, static_cast<std::uint32_t>(p2),
                    static_cast<std::uint32_t>(p3),
                    static_cast<std::uint32_t>(original.result),
                    static_cast<std::uint32_t>(candidate.result),
                    static_cast<std::uint32_t>(original.startup_ecx),
                    static_cast<std::uint32_t>(candidate.startup_ecx),
                    static_cast<std::uint32_t>(original.startup_edx),
                    static_cast<std::uint32_t>(candidate.startup_edx));
            }
            ++mismatches;
        }
    }

    std::printf("cases=%u mismatches=%u\n", kCases, mismatches);
    return mismatches == 0 ? 0 : 1;
}
