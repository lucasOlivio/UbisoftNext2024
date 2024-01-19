#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	class CollisionSystem : public iSystem
	{
	public:
		CollisionSystem() = default;
		virtual ~CollisionSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		// Use the event bus to trigger a collision event with this event data
		void m_TriggerCollisionEnter(const sCollisionData& collData);

		// Sphere checks
		void m_CheckSphereOverlaps(Scene* pScene,
								   Entity entityIdA,
								   TransformComponent* pTransformA,
								   SphereColliderComponent* pSphereA,
								   const int index,
								   const std::vector<Entity>& nonStaticEntities,
								   const std::vector<Entity>& staticEntities,
								   const std::vector<sTriangle*>& triangles);

		bool m_CheckSphereEntityOverlap(Scene* pScene,
										Entity entityIdA,
										TransformComponent* pTransformA,
										SphereColliderComponent* pSphereA,
										Entity entityIdB);
		
		// AABB checks
		void m_CheckAABBOverlaps(Scene* pScene,
								 Entity entityIdA,
								 TransformComponent* pTransformA,
								 AABBColliderComponent* pAABBA,
								 const int index,
								 const std::vector<Entity>& nonStaticEntities,
								 const std::vector<Entity>& staticEntities,
								 const std::vector<sTriangle*>& triangles);

		bool m_CheckAABBEntityOverlap(Scene* pScene,
									  Entity entityIdA,
									  TransformComponent* pTransformA,
									  AABBColliderComponent* pAABBA,
									  Entity entityIdB);
	};
}
