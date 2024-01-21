#pragma once

#include "Engine/Core/iSystem.h"

namespace MyEngine
{
	// Should be the only one to change the transform component data
	class DrawGridSystem : public iSystem
	{
	public:
		DrawGridSystem() = default;
		virtual ~DrawGridSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
