
project "imgui"
    language "C++"
    cppdialect "C++20"
    kind "StaticLib"
    architecture "x86_64"
    files {"**.cpp", "**.hpp", "**.c", "**.h"}

    -- targetdir "%{wks.location}/%{cfg.buildcfg}"
	-- objdir "%{wks.location}/Intermediates/%{cfg.buildcfg}"
    -- location "../Build/"

    externalincludedirs { "../Vendor/include"}
    links {"glfw3"}
    libdirs {"../Vendor/lib"}
    
    filter { "configurations:Debug" }
        runtime "Debug"
		symbols "On"
        -- defines { "CORAL_EXAMPLE_DEBUG" }
	filter {}

    filter { "configurations:Release" }
        runtime "Release"
        -- defines { "CORAL_EXAMPLE_RELEASE" }s
	filter {}
