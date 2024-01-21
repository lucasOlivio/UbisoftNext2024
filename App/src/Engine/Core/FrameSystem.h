#pragma once

#include "Engine/Core/iSystem.h"

namespace MyEngine
{
	// Keeps track of all related to frame number, fps etc
	class FrameSystem : public iSystem
	{
	public:
		FrameSystem() = default;
		virtual ~FrameSystem() { };

		virtual std::string SystemName() { return "FrameSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
