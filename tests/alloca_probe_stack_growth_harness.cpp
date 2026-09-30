#include <windows.h>
#include <cstdint>
#include <cstdio>

extern "C" void __stdcall __alloca_probe();
extern "C" std::uint32_t __stdcall __alloca_probe_8();
extern "C" std::uint32_t __stdcall __alloca_probe_16();

struct ProbeObservation
{
    std::uint32_t stack_delta;
    std::uint32_t frame_low_bits;
};

struct WorkerResult
{
    volatile DWORD exception_code;
    volatile LONG checks;
    volatile LONG failures;
};

static constexpr std::uint32_t kSizes[] = {
    0x00000000, 0x00000001, 0x00000007, 0x00000008, 0x00000009,
    0x00000fff, 0x00001000, 0x00001001, 0x00001fff, 0x00002000,
    0x00002001, 0x00007fff, 0x00008000, 0x00010000, 0x0001ffff,
    0x00020000, 0x0003ffff, 0x00040000, 0x00070000
};

extern "C" __declspec(naked) void __cdecl invoke_probe(
    std::uint32_t, ProbeObservation*)
{
    __asm {
        push    ebp
        mov     ebp, esp
        mov     eax, dword ptr [ebp + 8]
        call    __alloca_probe
        mov     edx, dword ptr [ebp + 0Ch]
        mov     ecx, ebp
        sub     ecx, esp
        mov     dword ptr [edx], ecx
        mov     ecx, ebp
        and     ecx, 0Fh
        mov     dword ptr [edx + 4], ecx
        mov     esp, ebp
        pop     ebp
        ret
    }
}

extern "C" __declspec(naked) void __cdecl invoke_probe_8(
    std::uint32_t, ProbeObservation*)
{
    __asm {
        push    ebp
        mov     ebp, esp
        mov     eax, dword ptr [ebp + 8]
        call    __alloca_probe_8
        mov     edx, dword ptr [ebp + 0Ch]
        mov     ecx, ebp
        sub     ecx, esp
        mov     dword ptr [edx], ecx
        mov     ecx, ebp
        and     ecx, 0Fh
        mov     dword ptr [edx + 4], ecx
        mov     esp, ebp
        pop     ebp
        ret
    }
}

extern "C" __declspec(naked) void __cdecl invoke_probe_16(
    std::uint32_t, ProbeObservation*)
{
    __asm {
        push    ebp
        mov     ebp, esp
        mov     eax, dword ptr [ebp + 8]
        call    __alloca_probe_16
        mov     edx, dword ptr [ebp + 0Ch]
        mov     ecx, ebp
        sub     ecx, esp
        mov     dword ptr [edx], ecx
        mov     ecx, ebp
        and     ecx, 0Fh
        mov     dword ptr [edx + 4], ecx
        mov     esp, ebp
        pop     ebp
        ret
    }
}

static DWORD WINAPI run_probes(void* parameter)
{
    auto* result = static_cast<WorkerResult*>(parameter);
    ProbeObservation observation{};
    using Probe = void(__cdecl*)(std::uint32_t, ProbeObservation*);
    Probe const probes[] = {invoke_probe, invoke_probe_8, invoke_probe_16};
    std::uint32_t const masks[] = {0, 7, 15};

    __try
    {
        for (std::uint32_t probe = 0; probe != 3; ++probe)
        {
            for (std::uint32_t size : kSizes)
            {
                probes[probe](size, &observation);
                std::uint32_t expected = size;
                if (masks[probe] != 0)
                {
                    expected +=
                        (observation.frame_low_bits - size) & masks[probe];
                }
                ++result->checks;
                if (observation.stack_delta != expected)
                    ++result->failures;
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        result->exception_code = GetExceptionCode();
    }
    return 0;
}

int main()
{
    WorkerResult result{};
    DWORD thread_id = 0;
    constexpr SIZE_T kReservedStack = 2u * 1024u * 1024u;
    HANDLE thread = CreateThread(
        nullptr,
        kReservedStack,
        run_probes,
        &result,
        STACK_SIZE_PARAM_IS_A_RESERVATION,
        &thread_id);
    if (thread == nullptr)
    {
        std::printf("CreateThread failed: %lu\n", GetLastError());
        return 2;
    }

    DWORD const wait_result = WaitForSingleObject(thread, INFINITE);
    DWORD thread_exit = 0;
    GetExitCodeThread(thread, &thread_exit);
    CloseHandle(thread);

    std::printf(
        "checks=%ld failures=%ld exception=0x%08lx thread_exit=%lu\n",
        result.checks,
        result.failures,
        result.exception_code,
        thread_exit);
    return wait_result == WAIT_OBJECT_0 && result.exception_code == 0 &&
                   result.failures == 0
               ? 0
               : 1;
}
