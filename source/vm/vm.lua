project "VirtualMachine"
	kind "ConsoleApp"
	language "C"
	staticruntime "on"
	systemversion "latest"

	targetdir ("../binaries/" .. outputdirectory .. "/%{prj.name}")
	objdir ("../intermediate/" .. outputdirectory .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.c",
	}

	-- Defines without any filter
	defines {}

	filter "configurations:Debug"
		defines {"TURTLE_DEBUG"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        defines {"TURTLE_RELEASE"}
		runtime "Release"
		optimize "on"

	filter "system:windows"
		cdialect "C11"
		defines {"TURTLE_OS_WINDOWS"}

	filter "system:linux"
		cdialect "gnu11"
		defines {"TURTLE_OS_LINUX"}
