# ImVehFt-RE (Improved Vehicle Features - Reverse Engineered)

[![Build ImVehFt-RE](https://github.com/CanerKaraca23/ImVehFt-RE/actions/workflows/build.yml/badge.svg)](https://github.com/CanerKaraca23/ImVehFt-RE/actions/workflows/build.yml)
![Language](https://img.shields.io/badge/Language-C%2B%2B26-00599C?logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-GTA%20San%20Andreas%201.0%20US%20(x86)-brightgreen)
![Build Tool](https://img.shields.io/badge/Build%20Tool-Premake5%20%7C%20VS2026%20(%2Eslnx)-purple)

A 100% faithful, 1:1 exact reverse engineered and modernized native **C++26** source code implementation of **Improved Vehicle Features (ImVehFt / IVF 2.1.1)** by **DK22Pac** for **Grand Theft Auto: San Andreas (1.0 US)**.

---

## Overview

Improved Vehicle Features (ImVehFt) is one of the most iconic modifications in GTA modding history, bringing realistic vehicle lighting, active aerodynamics, animated steering wheels, brake calipers, and custom emergency light systems into the GTA 3D engine.

**ImVehFt-RE** reconstructs the original closed-source plugin from disassembly and binary decompilation into clean, readable, modular C++26 code. Every memory patch, RenderWare frame callback, matrix transformation, and damage manager check has been verified against `gta_sa.exe` and the original `ImVehFt.asi` binary to ensure bit-level compatibility and rock-solid in-game stability without crashes.

---

## Features

- **Direction Indicators & Hazards:**
  - Left / Right turn signals and full hazard mode.
  - Direction indicator blinking timer and path-node based AI traffic decision logic.
- **Brake & Reverse Lights:**
  - Real-time brake pedal inspection (`CVehicle::m_fBreakPedal`).
  - Transmission gear inspection (`CAutomobile::GetGear`) with forward/reverse velocity checks.
- **Fog Lights:**
  - Keyboard toggle and dynamic ambient weather sync (heavy rain, fog, storms).
- **Steering Wheel Animation:**
  - Real-time steering angle mapping to `movsteer` dummy nodes with configurable multiplier parameters (`movsteer_X.X`).
- **Independent Brake Calipers:**
  - Full RenderWare matrix tracking and alignment for front, middle, and rear calipers (`hub_rf`, `hub_lf`, `hub_rm`, `hub_lm`, `hub_rb`, `hub_lb`).
- **Active Aerodynamics / Spoilers:**
  - Dynamic `movspoiler` deployment and retraction based on speed thresholds (deploy at >= 125 km/h) with damage manager door/boot validation.
- **Extra Component Damage Tracking:**
  - Extra parts (`extra1`..`extra5`) visibility toggling synchronized with vehicle panel and door damage status.
- **Custom Lighting & Lens Flares:**
  - Accurate 3D directional vector and dot product projection to the active camera source (`TheCamera.m_aCams[nActiveCam].m_vecSource`).
  - High-performance corona rendering and ground shadow projections.
- **DirectX 9 Shader Pipeline:**
  - Self-contained dirt decal pixel shader compilation (`dirt_layer.fx`).

---

## Default Controls

| Key | Action |
|:---:|:---|
| <kbd>Z</kbd> | Toggle Left Turn Signal |
| <kbd>C</kbd> | Toggle Right Turn Signal |
| <kbd>X</kbd> | Toggle Hazard Lights |
| <kbd>Shift</kbd> | Turn Signals Off |
| <kbd>G</kbd> | Toggle Headlights (Plays click sound ID 37) |
| <kbd>J</kbd> | Toggle Fog Lights |

*All key bindings and timings are configurable via `ImVehFt/ImVehFt.ini`.*

---

## Project Structure

```
ImVehFt-RE/
├── .github/
│   └── workflows/
│       └── build.yml       # GitHub Actions CI workflow
├── dxsdk/                  # Self-contained DirectX 9 SDK headers & libraries
├── source/                 # Core C++26 implementation
│   ├── CarColors.cpp / .h  # Custom vehicle color palette loader (.ivfc)
│   ├── common.h            # IVF structures (tIvfLight, tIvfSpoiler, etc.)
│   ├── Config.cpp / .h     # INI parser and control key bindings
│   ├── CustomPlates.cpp/.h # Dynamic license plate rendering
│   ├── DirtDecals.cpp / .h # DirectX 9 pixel shader dirt pipeline
│   ├── dllmain.cpp         # ASI entry point and hook installation
│   ├── Dummies.cpp / .h    # Clump frame tree traversal & dummy attachment
│   ├── EML.cpp / .h        # Emergency Light strobe parser (.eml)
│   ├── Hooks.cpp / .h      # Memory patches & GTA engine trampolines
│   ├── Lights.cpp / .h     # Lights processing, AI decisions & coronas
│   ├── Log.cpp / .h        # Diagnostic logging system
│   ├── SteeringWheel.cpp/.h# Steering wheel, calipers & active spoilers
│   └── VehicleData.cpp / .h# Extended per-vehicle state & pool indexer
├── build.bat               # Fast local command-line build script
├── premake5.lua            # Premake 5 build configuration
├── ImVehFt.slnx            # Visual Studio 2026 Solution XML
└── ImVehFt.vcxproj         # Visual Studio 2026 Project
```

---

## Building from Source

### Prerequisites

- **Visual Studio 2026** (or **Visual Studio 2022**) with **Desktop development with C++** (x86 / 32-bit MSVC toolset).
- **Premake 5** (optional, if regenerating project files).

### Build with Visual Studio

1. Double-click `ImVehFt.slnx` to open the solution in Visual Studio 2026.
2. Select **Release** configuration and **Win32** (x86) platform.
3. Build the solution (<kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>B</kbd>).
4. The compiled `.asi` binary is generated at `bin/ImVehFt.asi`.

### Build with Premake 5

```cmd
premake5 vs2026
```

### Build with Command Line (`build.bat`)

```cmd
build.bat
```

---

## Installation

1. Copy `ImVehFt.asi` into your GTA San Andreas root directory or `modloader/<AnyFolder>/`.
2. Ensure you have the original `ImVehFt` asset folder (`ImVehFt/` containing `ImVehFt.ini`, `effect/`, `eml/`, `grunge/`, `plates/`, `shadows/`, `tyres/`).

---

## License & Acknowledgments

- **DK22Pac**: Original creator of Improved Vehicle Features.
- **Caner Karaca**: Reverse engineering, disassembly analysis, C++26 reconstruction, and modernization.
- This project is provided for research, preservation, and modding enhancement purposes.
