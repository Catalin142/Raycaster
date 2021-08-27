project "Odium Ascensiunea"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Odium/**.h",
		"Odium/**.cpp",
		"**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Odium Engine/Engine",
	}

	links 
	{
		"Odium Engine"
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