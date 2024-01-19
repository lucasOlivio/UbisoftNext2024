#pragma once

#include "Event.hpp"
#include "Engine/ECS/Scene/Scene.h"

namespace MyEngine
{
	enum eSceneEvents
	{
		CHANGE
	};

	class SceneChangeEvent : public Event<eSceneEvents>
	{
	public:
		SceneChangeEvent() :
			Event<eSceneEvents>(eSceneEvents::CHANGE, "SceneChange") {};
		virtual ~SceneChangeEvent() {};

		std::string newSceneName;
		Scene* pNewScene;
	};
}
