#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	// Register collision events in the singleton component
	// and resets the vector every frame update
	class RegisterCollisionSystem : public iSystem
	{
	public:
		RegisterCollisionSystem() = default;
		virtual ~RegisterCollisionSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void RegisterCollision(const CollisionEnterEvent& event);
	};
}
