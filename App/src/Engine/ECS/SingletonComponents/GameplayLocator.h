#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class GameplayLocator
	{
	public:
		static ZombieSpawnComponent* GetZombieSpawn();
		static GameStateComponent* GetGameState();

		static void SetZombieSpawn(ZombieSpawnComponent* pZombieSpawn);
		static void SetGameState(GameStateComponent* pGameState);

		static void Clear();

	private:
		static ZombieSpawnComponent* m_pZombieSpawn;
		static GameStateComponent* m_pGameState;
	};
}
