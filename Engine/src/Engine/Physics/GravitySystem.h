#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	class GravitySystem : public iSystem
	{
	public:
		GravitySystem() = default;
		virtual ~GravitySystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
