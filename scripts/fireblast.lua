workspace "Fireblast"
	location "..\\"
	architecture "x86_64"
	startproject "Sandbox2D"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "../vendor/glfw/include"
IncludeDir["Glad"] = "../vendor/glad/include"
IncludeDir["glm"] = "../vendor/glm"
IncludeDir["spdlog"] = "../vendor/spdlog/include"
IncludeDir["stb"] = "../vendor/stb"


group "Dependencies"
	include "glfw.lua"
	include "glad.lua"

group ""

project "Fireblast"
	location "..\\"
	kind "StaticLib"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fbpch.h"
	pchsource "../src/fbpch.cpp"

	files 
	{
		"../src/**.h",	
		"../src/**.cpp",
		"../vendor/stb/**.h",
		"../vendor/stb/**.cpp",
		"../vendor/glm/glm/**.hpp",
		"../vendor/glm/glm/**.inl",
	}

	includedirs 
	{
		"../src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}"
	}

	links 
	{
		"opengl32.lib",
		"glfw",
		"glad"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "FB_DISTRIBUTION"
		runtime "Release"
		optimize "on"

project "Sandbox2D"
	location "..\\Sandbox2D"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"../%{prj.name}/**.h",
		"../%{prj.name}/**.cpp"
	}

	includedirs
	{
		"../src",
		"../vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.spdlog}"
	}

	links
	{
		"Fireblast"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "FB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FB_DIST"
		runtime "Release"
		optimize "on"