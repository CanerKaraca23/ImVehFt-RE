#include "DirtDecals.h"
#include "Log.h"

IDirect3DPixelShader9* CDirtDecals::m_pPixelShader = nullptr;
ID3DXConstantTable* CDirtDecals::m_pConstantTable = nullptr;
bool CDirtDecals::m_bInitialised = false;

bool CDirtDecals::Initialise(IDirect3DDevice9* pDevice) {
    if (m_bInitialised)
        return true;

    if (!pDevice) {
        pDevice = *reinterpret_cast<IDirect3DDevice9**>(0xC97C28);
    }

    if (!pDevice)
        return false;

    char shaderPath[MAX_PATH];
    snprintf(shaderPath, sizeof(shaderPath), "%sImVehFt\\effect\\dirt_layer.fx", CLog::GetPluginDir());
    if (GetFileAttributesA(shaderPath) == INVALID_FILE_ATTRIBUTES) {
        snprintf(shaderPath, sizeof(shaderPath), "%seffect\\dirt_layer.fx", CLog::GetPluginDir());
    }

    ID3DXBuffer* pShaderBuffer = nullptr;
    ID3DXBuffer* pErrorBuffer = nullptr;

    HRESULT hr = D3DXCompileShaderFromFileA(
        shaderPath,
        nullptr,
        nullptr,
        "main",
        "ps_2_0",
        D3DXSHADER_OPTIMIZATION_LEVEL3,
        &pShaderBuffer,
        &pErrorBuffer,
        &m_pConstantTable
    );

    if (pErrorBuffer) {
        const char* szError = reinterpret_cast<const char*>(pErrorBuffer->GetBufferPointer());
        CLog::Write("Shader compile warning/error: %s", szError);
        pErrorBuffer->Release();
    }

    if (FAILED(hr) || !pShaderBuffer) {
        CLog::Write("Failed to compile %s (hr = 0x%08X)", shaderPath, hr);
        return false;
    }

    hr = pDevice->CreatePixelShader(
        reinterpret_cast<const DWORD*>(pShaderBuffer->GetBufferPointer()),
        &m_pPixelShader
    );
    pShaderBuffer->Release();

    if (FAILED(hr)) {
        CLog::Write("CreatePixelShader failed (hr = 0x%08X)", hr);
        return false;
    }

    m_bInitialised = true;
    CLog::Write("Dirt decal pixel shader compiled and initialized successfully.");
    return true;
}

void CDirtDecals::Shutdown() {
    if (m_pPixelShader) {
        m_pPixelShader->Release();
        m_pPixelShader = nullptr;
    }
    if (m_pConstantTable) {
        m_pConstantTable->Release();
        m_pConstantTable = nullptr;
    }
    m_bInitialised = false;
}

void CDirtDecals::OnResetDevice() {
    // Shaders created in D3DPOOL_MANAGED or default remain valid across reset
}

void CDirtDecals::OnLostDevice() {
}

void CDirtDecals::Apply(IDirect3DDevice9* pDevice, void* pVehicle) {
    if (!m_bInitialised || !m_pPixelShader || !pDevice || !pVehicle)
        return;

    // In GTA SA CVehicle, dirt level is at offset 1196 (0x4AC)
    float fDirtLevel = *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(pVehicle) + 1196);
    float fDirtNormalized = fDirtLevel / 15.0f;
    if (fDirtNormalized > 1.0f) fDirtNormalized = 1.0f;
    if (fDirtNormalized < 0.0f) fDirtNormalized = 0.0f;

    pDevice->SetPixelShader(m_pPixelShader);
    if (m_pConstantTable) {
        m_pConstantTable->SetFloat(pDevice, "fDirtLevel", fDirtNormalized);
    }
}

void CDirtDecals::Restore(IDirect3DDevice9* pDevice) {
    if (pDevice) {
        pDevice->SetPixelShader(nullptr);
    }
}
