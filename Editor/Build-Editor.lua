project "Editor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files 
   { 
        "src/**.h", 
        "src/**.hpp", 
        "src/**.cpp" ,
        -- For now the editor keeps coupled with the app and serves just for building the scenes etc
        -- the gameplay logic and all will be taken from the app directly
	    "%{wks.location}/App/src/Core/**.h",
	    "%{wks.location}/App/src/Core/**.hpp",
	    "%{wks.location}/App/src/Core/**.cpp",
	    "%{wks.location}/App/src/Gameplay/**.h",
	    "%{wks.location}/App/src/Gameplay/**.hpp",
	    "%{wks.location}/App/src/Gameplay/**.cpp",
   }

   includedirs
   {
      "src",

      -- TODO: Use a shortcut or macro to avoid this repetition
      -- App
	  "%{wks.location}/App/src",
      -- Engine
	  "%{wks.location}/Engine/src",
      "%{wks.location}/Engine/Extern/Glad/include",
      "%{wks.location}/Engine/Extern/imgui/include",
      "%{wks.location}/Engine/Extern/ImGuizmo/include",
      "%{wks.location}/Engine/Extern/glfw/include",
      "%{wks.location}/Engine/Extern/glm/include",
      "%{wks.location}/Engine/Extern/fmod/include",
      "%{wks.location}/Engine/Extern/assimp/include",
      "%{wks.location}/Engine/Extern/Lua5.4.6/include",
      "%{wks.location}/Engine/Extern/rapidjson/include",
   }

   links
   {
      "Engine"
   }

   postbuildcommands
   {
       "{COPY} ../Engine/Extern/fmod/lib/*.dll %{cfg.buildtarget.directory}"
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

       postbuildcommands
       {
           "xcopy ..\\App\\assets\\ %{cfg.buildtarget.directory}\\assets\\ /S /E /I /Y"
       }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

       postbuildcommands
       {
           "{COPY} ../Engine/Extern/assimp/lib/Debug/*.dll %{cfg.buildtarget.directory}"
       }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

       postbuildcommands
       {
           "{COPY} ../Engine/Extern/assimp/lib/Release/*.dll %{cfg.buildtarget.directory}"
       }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"

       postbuildcommands
       {
           "{COPY} ../Engine/Extern/assimp/lib/Release/*.dll %{cfg.buildtarget.directory}"
       }
