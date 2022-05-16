project "UI Demo"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"App/**.h",
		"App/**.cpp",
		"**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Raycaster Engine/Engine",
	}

	links 
	{
		"Raycaster Engine"
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