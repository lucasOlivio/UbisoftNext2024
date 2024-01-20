project "APINext"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"
    
    files
    {
        "**.h",
        "**.cpp"
    }

    includedirs
    {
        "../glut"
    }
    
   libdirs { "../glut/lib/x64" }

   links
   {
      "freeglut.lib"
   }
    
    targetdir ("../../../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../../../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")
 
    filter "system:windows"
        systemversion "latest"
        defines { }
 
    filter "configurations:Debug"
        defines { "_DEBUG" }
        runtime "Debug"
        symbols "On"
 
    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"
        symbols "On"
