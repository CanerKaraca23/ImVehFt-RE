#pragma once
#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>

class CDirtDecals {
private:
    static IDirect3DPixelShader9* m_pPixelShader;
    static ID3DXConstantTable* m_pConstantTable;
    static bool m_bInitialised;

public:
    static bool Initialise(IDirect3DDevice9* pDevice = nullptr);
    static void Shutdown();
    static void OnResetDevice();
    static void OnLostDevice();
    static void Apply(IDirect3DDevice9* pDevice, void* pVehicle);
    static void Restore(IDirect3DDevice9* pDevice);
};
