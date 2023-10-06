workspace "FAJT"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}";

includeDir = {}
includeDir["GLFW"] = "FAJT/vendor/GLFW/include"
includeDir["Glad"] = "FAJT/vendor/Glad/include"
includeDir["stb"]  = "FAJT/vendor/stb"

include "FAJT/vendor/GLFW"
include "FAJT/vendor/Glad"

project "FAJT"
    location "FAJT"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/res/**.*"
    }

    includedirs{
        "%{prj.name}/src",
        "%{includeDir.GLFW}",
        "%{includeDir.Glad}",
        "%{includeDir.stb}"
    }

    links{
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines{

        }

    filter "configurations:Debug"
        -- defines ""
        symbols "On"

    filter "configurations:Release"
        -- defines ""
        optimize "On"

    filter "configurations:Dist"
        -- defines ""
        optimize "On"