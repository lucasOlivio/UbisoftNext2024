project "ImGuizmo"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"
    
    files
    {
        "include/**.h",
        "include/**.hpp",
        "src/**.c",
        "src/**.cpp"
    }

    includedirs
    {
        "include",
        "src",
        "../glfw/include",
        "%{wks.location}/Engine/Extern/imgui/include"
    }

    links
    {
       "ImGui"
    }
    
    targetdir ("../../../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../../../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")
 
    filter "system:windows"
        systemversion "latest"
        defines { }
 
    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
 
    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"
 
    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
