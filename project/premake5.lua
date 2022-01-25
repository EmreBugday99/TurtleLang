workspace "TurtleLang"
	startproject "VirtualMachine"
	architecture "x64"

	outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	configurations
	{
		"Debug",
		"Release"
	}

include "vm/vm.lua"