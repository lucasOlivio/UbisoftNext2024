#pragma once

#include "Engine/ECS/System/iSystem.h"

#include "Engine/Events/SceneEvent.h"

namespace MyEngine
{
	// Deals with guizmo drawing and modes
	class GuizmoSystem : public iSystem
	{
	public:
		GuizmoSystem() = default;
		virtual ~GuizmoSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
