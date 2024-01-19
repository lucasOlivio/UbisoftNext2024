project "Test_ComponentPool"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "src",

      -- TODO: Use a shortcut or macro to avoid this repetition
      -- Engine
      "../../Engine/src",
      "../../Engine/Extern/Glad/include",
      "../../Engine/Extern/glfw/include",
      "../../Engine/Extern/glm/include",
      "../../Engine/Extern/fmod/include",
      "../../Engine/Extern/assimp/include",
      "../../Engine/Extern/Lua5.4.6/include",
      "../../Engine/Extern/rapidjson/include",
      
      "../Extern/googletest/include"
   }

   links
   {
      "Engine"
   }

   targetdir ("../../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

       links
        {
            "../Extern/googletest/lib/Debug/gtest.lib"
        }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

       links
        {
            "../Extern/googletest/lib/Release/gtest.lib"
        }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"

       links
        {
            "../Extern/googletest/lib/Release/gtest.lib"
        }