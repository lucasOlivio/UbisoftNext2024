#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

namespace MyEngine
{
	class MovementSystem : public iSystem
	{
	public:
		MovementSystem() = default;
		virtual ~MovementSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
