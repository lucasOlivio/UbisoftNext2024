-- premake5.lua
workspace "CustomEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
   include "Engine/Extern/Glad/Build-Glad.lua"
   include "Engine/Extern/imgui/Build-ImGui.lua"
   include "Engine/Extern/ImGuizmo/Build-ImGuizmo.lua"
group ""

group "Tests"
	include "Tests/TEST_Example/Build-Test.lua"
	include "Tests/TEST_BiMap/Build-Test_BiMap.lua"
	include "Tests/TEST_ComponentPool/Build-Test_ComponentPool.lua"
	include "Tests/TEST_EntityManager/Build-Test_EntityManager.lua"
	include "Tests/TEST_EventBus/Build-Test_EventBus.lua"
	include "Tests/TEST_Scene/Build-Test_Scene.lua"
	include "Tests/TEST_SceneSerializer/Build-Test_SceneSerializer.lua"
group ""

include "Engine/Build-Engine.lua"
include "App/Build-App.lua"
include "Editor/Build-Editor.lua"