#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	class CameraSystem : public iSystem
	{
	public:
		CameraSystem() = default;
		virtual ~CameraSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
