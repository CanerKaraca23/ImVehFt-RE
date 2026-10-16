@echo off
setlocal enabledelayedexpansion

echo ========================================================
echo  Building ImVehFt.asi for GTA San Andreas
echo  Toolchain: Visual Studio 2026 / C++26 / x86 (32-bit)
echo ========================================================

:: Initialize 32-bit MSVC environment
if exist "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars32.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars32.bat"
) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
) else (
    echo [!] ERROR: Could not find vcvars32.bat!
    exit /b 1
)

:: Output directory
set OUTDIR=bin
if not exist "%OUTDIR%" mkdir "%OUTDIR%"

echo.
echo [*] Compiling C++ source files...

cl /nologo /O2 /MT /EHsc /std:c++latest /utf-8 /permissive- ^
   /Isource ^
   /Idxsdk ^
   source\dllmain.cpp ^
   source\Log.cpp ^
   source\Config.cpp ^
   source\VehicleData.cpp ^
   source\Dummies.cpp ^
   source\SteeringWheel.cpp ^
   source\Lights.cpp ^
   source\CustomPlates.cpp ^
   source\CarColors.cpp ^
   source\EML.cpp ^
   source\DirtDecals.cpp ^
   source\Hooks.cpp ^
   /link /DLL /OUT:"%OUTDIR%\ImVehFt.asi" ^
   /LIBPATH:dxsdk ^
   user32.lib kernel32.lib d3d9.lib d3dx9.lib

if %ERRORLEVEL% equ 0 (
    echo.
    echo ========================================================
    echo  BUILD SUCCESS! 
    echo  Output file created: %OUTDIR%\ImVehFt.asi
    echo ========================================================
) else (
    echo.
    echo [!] BUILD FAILED. Check errors above.
    exit /b %ERRORLEVEL%
)
