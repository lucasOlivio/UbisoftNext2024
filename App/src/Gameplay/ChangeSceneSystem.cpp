#include "pch.h"

#include "ChangeSceneSystem.h"

#include "Engine/ECS/Scene/SceneManagerLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/InputEvent.h"
#include "Engine/Events/EventBusLocator.hpp"

namespace MyEngine
{
	void ChangeSceneSystem::Init()
	{
		// Subscribe to keyboard event
		iEventBus<eInputEvents, KeyboardEvent>* pEventBus = EventBusLocator<eInputEvents, KeyboardEvent>::Get();

		pEventBus->Subscribe(eInputEvents::KEYBOARD, InputTriggered);
	}

	void ChangeSceneSystem::Start(Scene* pScene)
	{
	}

	void ChangeSceneSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void ChangeSceneSystem::Render(Scene* pScene)
	{
	}

	void ChangeSceneSystem::End(Scene* pScene)
	{
	}

	void ChangeSceneSystem::Shutdown()
	{
	}

	void ChangeSceneSystem::InputTriggered(const KeyboardEvent& event)
	{
		if (event.keyData.key != eKeyCodes::ENTER && event.keyData.key != eKeyCodes::KP_ENTER)
		{
			return;
		}

		if (event.keyData.action != eInputActions::KEY_PRESS)
		{
			return;
		}

		iSceneManager* pSceneManager = SceneManagerLocator::Get();

		std::string nextScene = "scene02.json";
		if (nextScene == pSceneManager->GetCurrentSceneName())
		{
			nextScene = "scene01.json";
		}

		pSceneManager->ChangeScene(nextScene, true);
	}
}
