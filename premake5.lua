workspace "Raycaster"
	architecture "x86"
	configurations { "Debug", "Release" }
	startproject "Raycaster Demo"
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Raycaster Engine"
include "Raycaster Demo"
include "UI Demo"
