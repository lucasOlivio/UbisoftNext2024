-- premake5.lua
workspace "UbisoftNext"
   architecture "x64"
   configurations { "Debug", "Release" }
   system "windows"
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "App/Build-App.lua"