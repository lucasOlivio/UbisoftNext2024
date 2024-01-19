#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	class MaterialHeightMapOffsetSystem : public iSystem
	{
	public:
		MaterialHeightMapOffsetSystem() = default;
		virtual ~MaterialHeightMapOffsetSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
