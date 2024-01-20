#include "stdafx.h"
#include "GameplayLocator.h"

namespace MyEngine
{
    ZombieSpawnComponent* GameplayLocator::m_pZombieSpawn = new ZombieSpawnComponent();

    ZombieSpawnComponent* GameplayLocator::GetZombieSpawn()
    {
        return m_pZombieSpawn;
    }

    void GameplayLocator::SetZombieSpawn(ZombieSpawnComponent* pZombieSpawn)
    {
        delete m_pZombieSpawn;
        m_pZombieSpawn = pZombieSpawn;
    }

    void GameplayLocator::Clear()
    {
        delete m_pZombieSpawn;
    }
}
