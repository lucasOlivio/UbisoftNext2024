#pragma once

#include "Engine/ECS/Scene/Scene.h"
#include "Engine/ECS/System/iSystem.h"
#include "Engine/ECS/Scene/iSceneManager.h"

#include "Engine/Events/WindowEvents.h"
#include "Engine/Events/CollisionEvent.h"
#include "Engine/Events/InputEvent.h"
#include "Engine/Events/StateChangeEvent.h"
#include "Engine/Events/SceneEvent.h"
#include "Engine/Events/iEventBus.h"

#include "Engine/Graphics/VAO/iVAOManager.h"
#include "Engine/Graphics/Shaders/iShaderManager.h"
#include "Engine/Graphics/Materials/iMaterialManager.h"
#include "Engine/Graphics/Textures/iTextureManager.h"

namespace MyEngine
{
	// App should inherit from this class to setup and run everything needed
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		// Systems that will manipulate components and handle the scene in some way,
		// the system is added and initialized, if the scene is passed the system is also started
		virtual void AddSystem(iSystem* pSystem, Scene* pScene = nullptr);
		virtual void RemoveSystem(iSystem* pSystem, Scene* pScene = nullptr);

		virtual void Init();

		// Run engine starting simulation state as running or stopped
		virtual void Run(std::string initialSceneName, bool startSimulation = true);

		virtual void Update(float deltaTime);

		virtual void Render();

		virtual void Shutdown();

		virtual void LoadConfigurations();

		// Initializes systems with scene
		virtual void StartSystems(Scene* pScene);

		// Finishes systems for scene
		virtual void EndSystems(Scene* pScene);

		virtual void ShutdownSystems();

		virtual void OnSceneChange(const SceneChangeEvent& event);

		// Any major clears needed to be done at end of frame (Ex: scene deleting, entity delete)
		virtual void ClearFrame();

	protected:
		std::vector<iSystem*> m_systems;
		Scene* m_pCurrentScene = nullptr;

		// Events
		iEventBus<eWindowEvents, WindowCloseEvent>* m_pEventBusWindow;
		iEventBus<eCollisionEvents, CollisionEnterEvent>* m_pEventBusCollision;
		iEventBus<eInputEvents, KeyboardEvent>* m_pEventBusKeyboard;
		iEventBus<eInputEvents, MouseEvent>* m_pEventBusMouse;
		iEventBus<eStateChangeEvents, StoppedStateEvent>* m_pEventBusStoppedState;
		iEventBus<eStateChangeEvents, RunningStateEvent>* m_pEventBusRunningState;
		iEventBus<eSceneEvents, SceneChangeEvent>* m_pEventBusSceneChange;

		// Resources managers
		iVAOManager* m_pVAOManager;
		iShaderManager* m_pShaderManager;
		iMaterialManager* m_pMaterialManager;
		iTextureManager* m_pTextureManager;
		iSceneManager* m_pSceneManager;

		float m_lastTime = 0.0f;
		std::vector<float> m_frameTimes;

		float m_GetDeltaTime();

		// Operations to execute before rendering
		virtual void m_BeginFrame();

		// Operations to execute after rendering
		virtual void m_EndFrame();
	};
}
