#pragma once

#include "GridAABB.h"

#include "Engine/Core/Types.h"
#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/Components.h"
#include "Engine/ECS/Base.h"

#include "Engine/Physics/PhysicsProperties.h"

#include "Engine/Utils/Vector2.h"

namespace MyEngine
{
	class GridBroadPhaseSystem : public iSystem
	{
	public:
		GridBroadPhaseSystem() = default;
		virtual ~GridBroadPhaseSystem() {};

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	protected:
		GridAABB* m_GetAABB(uint idxAABB);
		GridAABB* m_GetAABB(Vec2 point);

		GridAABB* m_GetOrCreateAABB(uint idxAABB);

		// Calculates all the aabbs that the shape intersects
		// and inserts into the respective Grid AABB
		void m_InsertSphere(Entity entityID, uint originIndex,
							Vec2 position, float radius, eBody bodyType,
							GridBroadphaseComponent* pGrid);

		// Insert entity in map and active map if not a static body
		void m_InsertEntity(Entity entityID, uint index, eBody bodyType);

		// Remove AABB from mapping if exists
		size_t m_RemoveAABB(uint idxAABB);

		void m_ClearAABBs();
	};
}
