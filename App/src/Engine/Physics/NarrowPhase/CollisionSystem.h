#pragma once

#include "Engine/Core/iSystem.h"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	class CollisionSystem : public iSystem
	{
	public:
		CollisionSystem() = default;
		virtual ~CollisionSystem() { };

		virtual std::string SystemName() { return "CollisionSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		// Use the event bus to trigger a collision event with this event data
		void m_TriggerCollisionEnter(const sCollisionData& collData);

		// Returns false if the collision is duplicated
		bool m_RegisterFrameCollision(const sCollisionData& collData);

		// Sphere checks
		void m_CheckSphereCollision(Scene* pScene,
								   Entity entityIdActive,
								   Vec2 positionActive,
								   float radiusActive,
								   const int index,
								   const std::vector<Entity>& activeEntities,
								   const std::vector<Entity>& PassiveEntities);

		bool m_CheckSphereEntityOverlap(Scene* pScene,
										Entity entityIdActive,
								        Vec2 positionActive,
										float radiusActive,
										Entity entityIdPassive);
	};
}
