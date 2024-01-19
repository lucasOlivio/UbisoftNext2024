#include "pch.h"

#include "ChangeStateSystem.h"

#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/InputEvent.h"
#include "Engine/Events/EventBusLocator.hpp"

namespace MyEngine
{
	void ChangeStateSystem::Init()
	{
		// Subscribe to keyboard event
		iEventBus<eInputEvents, KeyboardEvent>* pEventBus = EventBusLocator<eInputEvents, KeyboardEvent>::Get();

		pEventBus->Subscribe(eInputEvents::KEYBOARD, InputTriggered);
	}

	void ChangeStateSystem::Start(Scene* pScene)
	{
	}

	void ChangeStateSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void ChangeStateSystem::Render(Scene* pScene)
	{
	}

	void ChangeStateSystem::End(Scene* pScene)
	{
	}

	void ChangeStateSystem::Shutdown()
	{
	}

	void ChangeStateSystem::InputTriggered(const KeyboardEvent& event)
	{
		if (event.keyData.key != eKeyCodes::SPACE)
		{
			return;
		}

		if (event.keyData.action != eInputActions::KEY_PRESS)
		{
			return;
		}

		StateComponent* pState = CoreLocator::GetState();

		if (pState->currState == eStates::SIMULATION_STOPPED)
		{
			pState->currState = eStates::SIMULATION_RUNNING;
		}
		else if (pState->currState == eStates::SIMULATION_RUNNING)
		{
			pState->currState = eStates::SIMULATION_STOPPED;
		}
	}
}
