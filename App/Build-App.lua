project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   linkoptions {"/SUBSYSTEM:WINDOWS"}

    defines 
    { 
        "_CRT_SECURE_NO_WARNINGS",
        "_CONSOLE" 
    }

   files { 
        "src/**.h", "src/**.hpp", "src/**.cpp" ,
        "Extern/**.h",
        "Extern/**.cpp"
    }

   pchheader "stdafx.h"
   pchsource "src/stdafx.cpp"

   includedirs
   {
      "src",
      "Extern/glut",
      "Extern/App"
   }

   libdirs { "Extern/glut/lib/x64" }

   links
   {
      "freeglut.lib"
   }

   postbuildcommands
   {
       "xcopy assets\\ %{cfg.buildtarget.directory}\\assets\\ /S /E /I /Y",
       "xcopy Extern\\glut\\bin\\x64\\*.dll %{cfg.buildtarget.directory} /Y"
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")
   

   filter "system:Windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "_DEBUG" }
       runtime "Debug"
       symbols "On"
       
       links
       {
           "dxguid.lib",
           "dsound.lib"
       }

   filter "configurations:Release"
       defines { "NDEBUG" }
       runtime "Release"
       optimize "On"
       symbols "On"
       
       links
       {
           "dxguid.lib","dsound.lib","kernel32.lib","user32.lib","gdi32.lib","winspool.lib","comdlg32.lib","advapi32.lib","shell32.lib","ole32.lib","oleaut32.lib","uuid.lib","odbc32.lib","odbccp32.lib"
       }
