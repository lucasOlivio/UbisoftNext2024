#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	class MaterialOffsetSystem : public iSystem
	{
	public:
		MaterialOffsetSystem() = default;
		virtual ~MaterialOffsetSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
