workspace "ImVehFt"
    configurations { "Debug", "Release" }
    platforms { "Win32" }
    architecture "x86"
    location "."

    defines {
        "WIN32",
        "_WINDOWS",
        "_CRT_SECURE_NO_WARNINGS",
        "_CRT_NONSTDC_NO_DEPRECATE"
    }

    characterset "MBCS"

    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Speed"

    filter {}

project "ImVehFt"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    targetname "ImVehFt"
    targetextension ".asi"
    targetdir "bin"
    objdir "bin/obj"
    staticruntime "On"

    files {
        "source/**.h",
        "source/**.cpp"
    }

    includedirs {
        "source",
        "dxsdk"
    }

    libdirs {
        "dxsdk"
    }

    links {
        "user32",
        "kernel32",
        "d3d9",
        "d3dx9"
    }
