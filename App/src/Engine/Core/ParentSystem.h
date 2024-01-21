#pragma once

#include "Engine/Core/iSystem.h"

namespace MyEngine
{
	// Keeps the world values from transform updated relative to parent
	class ParentSystem : public iSystem
	{
	public:
		ParentSystem() = default;
		virtual ~ParentSystem() { };

		virtual std::string SystemName() { return "ParentSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
