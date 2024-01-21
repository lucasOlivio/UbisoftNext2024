#include "stdafx.h"
#include "GameplayLocator.h"

namespace MyEngine
{
    ZombieSpawnComponent* GameplayLocator::m_pZombieSpawn = new ZombieSpawnComponent();
    GameStateComponent* GameplayLocator::m_pGameState = new GameStateComponent();

    ZombieSpawnComponent* GameplayLocator::GetZombieSpawn()
    {
        return m_pZombieSpawn;
    }

    GameStateComponent* GameplayLocator::GetGameState()
    {
        return m_pGameState;
    }

    void GameplayLocator::SetZombieSpawn(ZombieSpawnComponent* pZombieSpawn)
    {
        delete m_pZombieSpawn;
        m_pZombieSpawn = pZombieSpawn;
    }

    void GameplayLocator::SetGameState(GameStateComponent* pGameState)
    {
        delete m_pGameState;
        m_pGameState = pGameState;
    }

    void GameplayLocator::Clear()
    {
        delete m_pZombieSpawn;
        delete m_pGameState;
    }
}
