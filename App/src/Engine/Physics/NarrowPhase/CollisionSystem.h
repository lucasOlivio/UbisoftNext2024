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
								   float radiusA,
								   const int index,
								   const std::vector<Entity>& nonStaticEntities,
								   const std::vector<Entity>& staticEntities);

		bool m_CheckSphereEntityOverlap(Scene* pScene,
										Entity entityIdA,
										TransformComponent* pTransformA,
										float radiusA,
										Entity entityIdB);
	};
}
