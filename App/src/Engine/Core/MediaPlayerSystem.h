#pragma once

#include "Engine/Core/iSystem.h"

namespace MyEngine
{
	// Plays sounds and keep tracks of their progress
	class MediaPlayerSystem : public iSystem
	{
	public:
		MediaPlayerSystem() = default;
		virtual ~MediaPlayerSystem() { };

		virtual std::string SystemName() { return "MediaPlayerSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
