#pragma once

#include "Engine/Core/iSystem.h"

namespace MyEngine
{
	// Should be the only one to change the transform component data
	class ConsoleSystem : public iSystem
	{
	public:
		ConsoleSystem() = default;
		virtual ~ConsoleSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
