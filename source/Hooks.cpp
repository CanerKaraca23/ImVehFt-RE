#include "Hooks.h"
#include "Config.h"
#include "Log.h"
#include "VehicleData.h"
#include "SteeringWheel.h"
#include "Lights.h"
#include "Dummies.h"
#include "DirtDecals.h"
#include "CarColors.h"
#include "EML.h"

// Memory patch helpers
static void PatchBytes(uintptr_t address, const void* data, size_t size) {
    DWORD oldProtect;
    VirtualProtect(reinterpret_cast<LPVOID>(address), size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(reinterpret_cast<void*>(address), data, size);
    VirtualProtect(reinterpret_cast<LPVOID>(address), size, oldProtect, &oldProtect);
}

static void PatchNOP(uintptr_t address, size_t count) {
    DWORD oldProtect;
    VirtualProtect(reinterpret_cast<LPVOID>(address), count, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(reinterpret_cast<void*>(address), 0x90, count);
    VirtualProtect(reinterpret_cast<LPVOID>(address), count, oldProtect, &oldProtect);
}

static void PatchCall(uintptr_t address, void* targetFunc) {
    DWORD oldProtect;
    VirtualProtect(reinterpret_cast<LPVOID>(address), 5, PAGE_EXECUTE_READWRITE, &oldProtect);
    *reinterpret_cast<uint8_t*>(address) = 0xE8; // CALL
    *reinterpret_cast<uint32_t*>(address + 1) = reinterpret_cast<uintptr_t>(targetFunc) - (address + 5);
    VirtualProtect(reinterpret_cast<LPVOID>(address), 5, oldProtect, &oldProtect);
}

static void PatchJmp(uintptr_t address, void* targetFunc) {
    DWORD oldProtect;
    VirtualProtect(reinterpret_cast<LPVOID>(address), 5, PAGE_EXECUTE_READWRITE, &oldProtect);
    *reinterpret_cast<uint8_t*>(address) = 0xE9; // JMP
    *reinterpret_cast<uint32_t*>(address + 1) = reinterpret_cast<uintptr_t>(targetFunc) - (address + 5);
    VirtualProtect(reinterpret_cast<LPVOID>(address), 5, oldProtect, &oldProtect);
}

// -------------------------------------------------------------
// Trampoline & Callback Hooks
// -------------------------------------------------------------

// Graphics init hook at 0x5BD779 (inside CCustomCarEnvMapPipeline::CreateShaders)
static void __cdecl GraphicsInitHook() {
    reinterpret_cast<void(__cdecl*)()>(0x704630)();
    CHooks::OnGraphicsInit();
}

// PreRender hook at 0x6D6617 (replaces CVehicle::PreRender headlight flags call at 0x4C8C90)
// Calling convention: __cdecl with 1 argument (CVehicle* pVehicle), matching sub_100074D0
static void* __cdecl PreRenderHook(void* pVehicle) {
    if (!pVehicle)
        return pVehicle;

    // 1. Perform original 0x4C8C90 vehicle headlight flags assignment
    uint8_t flags = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(pVehicle) + 0x584);
    *reinterpret_cast<uint8_t*>(0xB4E3E9) = (flags & 1);
    *reinterpret_cast<uint8_t*>(0xB4E3E8) = ((flags >> 1) & 1);
    *reinterpret_cast<uint8_t*>(0xB4E3EB) = ((flags >> 2) & 1);
    *reinterpret_cast<uint8_t*>(0xB4E3EA) = ((flags >> 3) & 1);

    // 2. Perform IVF PreRender logic (sub_100074D0)
    return CHooks::OnVehiclePreRender(pVehicle);
}

// SetupModelNodes / lights process hook at 0x6D6494 (sub_100050E0)
// Calling convention: __thiscall with ecx = pVehicle
static void __declspec(naked) ProcessVehicleLights_Naked() {
    __asm {
        push ecx
        call CLights::ProcessVehicleLights
        add esp, 4
        ret
    }
}

// Dummies setup hook at 0x6D6A58 (sub_100042C0)
// Calling convention: __thiscall with ecx = pVehicle, [esp+4] = a2
static void __declspec(naked) DummiesSetup_Naked() {
    __asm {
        mov eax, [esp+4]
        push eax
        push ecx
        call CDummies::SetupModelNodes
        add esp, 8
        ret 4
    }
}

// Headlight corona hook at 0x6E0DF7 (sub_10003340)
static int __cdecl CoronaHook_Handler(
    int id, void* pVehicle, int a3, int a4, int a5, int a6, int a7,
    float radius, float range, int a10, int a11, int a12, int a13, int a14,
    float a15, int a16, float a17, int a18, float a19, int a20, int a21
) {
    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    float extraRadius = (pState && pState->bHeadlightsOn) ? 1.0f : 0.0f;
    float timeVal = *reinterpret_cast<float*>(0xC81300);
    float finalRadius = extraRadius + timeVal + radius;

    return reinterpret_cast<int(__cdecl*)(
        int, void*, int, int, int, int, int, float, float, int, int, int, int, int,
        float, int, float, int, float, int, int
    )>(0x6FC580)(
        id, pVehicle, a3, a4, a5, 128, a7, finalRadius, range, a10, a11, a12, a13, a14,
        a15, a16, a17, a18, a19, a20, a21
    );
}

// Weather change hook at 0x53BFCC (sub_10004B10)
static int16_t __cdecl WeatherChange_Handler() {
    int16_t curWeather = *reinterpret_cast<int16_t*>(0xC81320);
    static int16_t lastWeather = -1;

    g_nWeatherFogLightState = 0;
    if (lastWeather == -1) {
        lastWeather = curWeather;
        return curWeather;
    }

    if (lastWeather != curWeather) {
        if (curWeather == 8 || curWeather == 9 || curWeather == 16 || curWeather == 19) {
            if (lastWeather != 8 && lastWeather != 9 && lastWeather != 16 && lastWeather != 19) {
                g_nWeatherFogLightState = 1;
            }
        } else if (lastWeather == 8 || lastWeather == 9 || lastWeather == 16 || lastWeather == 19) {
            g_nWeatherFogLightState = 2;
        }
    }

    lastWeather = curWeather;
    return curWeather;
}

// BlowUpCar hook at 0x6AB350 (sub_10003030)
static void __declspec(naked) BlowUpCarHook_Naked() {
    __asm {
        pushad
        push esi
        call CVehicleData::ResetVehicle
        add esp, 4
        popad

        // Original instruction: movsx eax, word ptr [esi + 0x22]
        movsx eax, word ptr [esi + 0x22]
        lea edi, [eax - 0x197]
        mov edx, 0x6AB35A
        jmp edx
    }
}

// Driver enter hook at 0x6F3AED (sub_10003060)
static void __declspec(naked) DriverEnterHook_Naked() {
    __asm {
        pushad
        mov eax, esi
        cmp dword ptr [eax + 0x594], 0x0B
        je DoneEnter
        and byte ptr [eax + 0x428], 0xEF
DoneEnter:
        push esi
        call CHooks::OnDriverEnter
        add esp, 4
        popad
        ret
    }
}

// Driver exit hook at 0x6F3973 (sub_10003080)
static void __declspec(naked) DriverExitHook_Naked() {
    __asm {
        pushad
        mov eax, esi
        cmp dword ptr [eax + 0x594], 0x0B
        je DoneExit
        and byte ptr [eax + 0x4A8], 0xE7
        and byte ptr [eax + 0x428], 0xBF
DoneExit:
        push esi
        call CHooks::OnDriverExit
        add esp, 4
        popad
        ret
    }
}

// -------------------------------------------------------------
// Hook Handlers
// -------------------------------------------------------------

void CHooks::OnGraphicsInit() {
    static bool bGraphicsInitDone = false;
    if (bGraphicsInitDone)
        return;
    bGraphicsInitDone = true;

    CLog::Write("Graphics initialization triggered at 0x5BD779.");

    // 1. Initialise configuration from ImVehFt.ini
    CConfig::Read();

    // 2. Initialise vehicle data pools
    CVehicleData::Initialise();

    // 3. Apply all remaining in-game memory hooks and patches
    ApplyAllPatches();

    // 4. Initialise shaders, colors, and EML
    CDirtDecals::Initialise();
    CCarColors::Initialise();
    CEml::Initialise();

    CLog::Write("ImVehFt fully initialized and operational.");
}

void* CHooks::OnVehiclePreRender(void* pVehicle) {
    if (!pVehicle)
        return pVehicle;

    CSteeringWheel::UpdateBrakeCalipers(pVehicle);
    CSteeringWheel::UpdateSpoilers(pVehicle);
    CSteeringWheel::Update(pVehicle);
    CSteeringWheel::UpdateExtras(pVehicle);
    CEml::Process(pVehicle);
    CLights::RenderVehicleLights(pVehicle);
    return pVehicle;
}

void CHooks::OnProcessVehicleLights(void* pVehicle) {
    if (!pVehicle)
        return;

    CLights::ProcessVehicleLights(pVehicle);
}

void CHooks::OnVehicleBlowUp(void* pVehicle) {
    if (!pVehicle)
        return;

    CVehicleData::ResetVehicle(pVehicle);
}

void CHooks::OnDriverEnter(void* pVehicle) {
    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    if (pState) {
        pState->bLeftIndicator = 0;
        pState->bRightIndicator = 0;
    }
}

void CHooks::OnDriverExit(void* pVehicle) {
    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    if (pState) {
        pState->bLeftIndicator = 0;
        pState->bRightIndicator = 0;
    }
}

void CHooks::OnWeatherChange() {
    WeatherChange_Handler();
}

// -------------------------------------------------------------
// Installation
// -------------------------------------------------------------

void CHooks::InstallEarlyHooks() {
    CLog::Write("Installing early engine hooks...");

    // Hook CreateShaders in CCustomCarEnvMapPipeline at 0x5BD779
    PatchCall(0x5BD779, GraphicsInitHook);

    CLog::Write("Early engine hooks installed.");
}

void CHooks::ApplyAllPatches() {
    CLog::Write("Making ImVehFt memory patches...");

    // 1. Material texture swap callback hook at 0x4C8415 (sub_100076D0)
    void* pMaterialCallback = reinterpret_cast<void*>(CLights::MaterialCallback);
    PatchBytes(0x4C8415, &pMaterialCallback, 4);

    // 2. PreRender hook (steering wheel, brake calipers, spoilers, indicators, coronas)
    PatchCall(0x6D6617, PreRenderHook);

    // 3. SetupModelNodes hook (lights process, indicators timer)
    PatchCall(0x6D6494, ProcessVehicleLights_Naked);

    // 4. Weather change hook at 0x53BFCC (sub_10004B10)
    PatchCall(0x53BFCC, WeatherChange_Handler);

    // 5. Dummies setup hook (movsteer, hub_rf/lf/rr/lr, breakl, fogl, revl, movspoiler)
    PatchCall(0x6D6A58, DummiesSetup_Naked);

    // 6. Headlights corona hook at 0x6E0DF7 (sub_10003340)
    PatchCall(0x6E0DF7, CoronaHook_Handler);

    // 7. Car destruction / blow-up hook at 0x6AB350 (sub_10003030)
    PatchJmp(0x6AB350, BlowUpCarHook_Naked);
    PatchNOP(0x6AB355, 5); // 10 bytes total replaced

    // 8. Driver enter/exit hooks
    PatchCall(0x6F3AED, DriverEnterHook_Naked);
    PatchNOP(0x6F3AF2, 1);
    PatchCall(0x6F3973, DriverExitHook_Naked);
    PatchNOP(0x6F3978, 7);

    // 9. Disable default triangular headlight cones if requested
    if (CConfig::bDisableBeamShape) {
        PatchNOP(0x6A2ED3, 12);
        PatchNOP(0x6A2EEB, 12);
        PatchNOP(0x6BDE73, 18);
    }

    CLog::Write("Memory patches applied successfully.");
}
