#include "stdafx.h"

#include "StateSystem.h"

#include "Engine/ECS/SingletonComponents/GameplayLocator.h"

#include "Engine/Events/GameStateEvent.h"
#include "Engine/Events/EventBusLocator.hpp"

namespace MyEngine
{
	void StateSystem::Init()
	{
	}

	void StateSystem::Start(Scene* pScene)
	{
	}

	void StateSystem::Update(Scene* pScene, float deltaTime)
	{
		GameStateComponent* pState = GameplayLocator::GetGameState();
		if (pState->currState == pState->prevState)
		{
			return;
		}

		m_TriggerStateChange(pState->currState);
		pState->prevState = pState->currState;
	}

	void StateSystem::Render(Scene* pScene)
	{
	}

	void StateSystem::End(Scene* pScene)
	{
	}

	void StateSystem::Shutdown()
	{
	}

	void StateSystem::m_TriggerStateChange(const eGameStates& newState)
	{
		if (newState == eGameStates::STARTED)
		{
			iEventBus<eGameStateEvents, GameStartedEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameStartedEvent>::Get();

			GameStartedEvent stateEvent = GameStartedEvent();
			pEventBus->Publish(stateEvent);

			return;
		}
		else if (newState == eGameStates::RUNNING)
		{
			iEventBus<eGameStateEvents, GameRunningEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameRunningEvent>::Get();

			GameRunningEvent stateEvent = GameRunningEvent();
			pEventBus->Publish(stateEvent);

			return;
		}
		else if (newState == eGameStates::LEVELUP)
		{
			iEventBus<eGameStateEvents, GameLevelUpEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameLevelUpEvent>::Get();

			GameLevelUpEvent stateEvent = GameLevelUpEvent();
			pEventBus->Publish(stateEvent);

			return;
		}
		else if (newState == eGameStates::GAMEOVER)
		{
			iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

			GameOverEvent stateEvent = GameOverEvent();
			pEventBus->Publish(stateEvent);

			return;
		}
	}
}
