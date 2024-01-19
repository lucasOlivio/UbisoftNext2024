#include "pch.h"

#include "StateSystem.h"

#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/StateChangeEvent.h"
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
		StateComponent* pState = CoreLocator::GetState();

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
		// Stop simulations
		StateComponent* pState = CoreLocator::GetState();
		pState->currState = pState->prevState = eStates::SIMULATION_STOPPED;
		m_TriggerStateChange(pState->currState);
	}

	void StateSystem::Shutdown()
	{
	}

	void StateSystem::m_TriggerStateChange(const eStates& newState)
	{
		if (newState == eStates::SIMULATION_STOPPED)
		{
			iEventBus<eStateChangeEvents, StoppedStateEvent>* pEventBus = EventBusLocator<eStateChangeEvents, StoppedStateEvent>::Get();

			StoppedStateEvent keyEvent = StoppedStateEvent();
			pEventBus->Publish(keyEvent);
			
			return;
		}
		else if (newState == eStates::SIMULATION_RUNNING)
		{
			iEventBus<eStateChangeEvents, RunningStateEvent>* pEventBus = EventBusLocator<eStateChangeEvents, RunningStateEvent>::Get();

			RunningStateEvent keyEvent = RunningStateEvent();
			pEventBus->Publish(keyEvent);

			return;
		}
	}
}
