#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class GameplayLocator
	{
	public:
		static ZombieSpawnComponent* GetZombieSpawn();

		static void SetZombieSpawn(ZombieSpawnComponent* pZombieSpawn);

		static void Clear();

	private:
		static ZombieSpawnComponent* m_pZombieSpawn;
	};
}
