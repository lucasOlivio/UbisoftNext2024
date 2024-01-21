#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Scene.h"

#include "Engine/Events/GameStateEvent.h"
#include "Engine/Events/CollisionEvent.h"
#include "Engine/Events/iEventBus.h"

namespace MyEngine
{
	// App should inherit from this class to setup and run everything needed
	class Engine
	{
	public:
		Engine();
		~Engine();

		// Systems that will manipulate components and handle the scene in some way,
		// the system is added and initialized, if the scene is passed the system is also started
		void AddSystem(iSystem* pSystem, Scene* pScene);
		void RemoveSystem(std::string systemName, Scene* pScene);

		void Init();

		void Update(float deltaTime);

		void Render();

		void Shutdown();

		// Initializes systems with scene
		void StartSystems(Scene* pScene);

		// Finishes systems for scene
		void EndSystems(Scene* pScene);

		void ShutdownSystems();

		Scene* GetScene();

	protected:
		std::vector<iSystem*> m_systems;
		Scene* m_pScene;

		// Events
		iEventBus<eCollisionEvents, CollisionEnterEvent>* m_pEventBusCollision;

		iEventBus<eGameStateEvents, GameStartedEvent>* m_pEventBusGameStarted;
		iEventBus<eGameStateEvents, GameRunningEvent>* m_pEventBusGameRunning;
		iEventBus<eGameStateEvents, GameLevelUpEvent>* m_pEventBusGameLevelUp;
		iEventBus<eGameStateEvents, GameOverEvent>* m_pEventBusGameOver;
	};
}
