project "Odium Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Core/RaycastPCH.h"
	pchsource "Engine/Core/RaycastPCH.cpp"

	includedirs
	{
		"Engine",
	}

	files
	{
		"Engine/**.h",
		"Engine/**.cpp",
		"**.cpp",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		defines "DEBUG=1"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "RELEASE=1"
		optimize "on"