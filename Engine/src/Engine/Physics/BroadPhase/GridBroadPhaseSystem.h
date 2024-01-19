#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/ECS/Components.h"
#include "Engine/Core/Shapes.hpp"
#include "Engine/Physics/PhysicsProperties.h"
#include "GridAABB.h"
#include <map>

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
		GridAABB* m_GetAABB(glm::vec3 point);

		GridAABB* m_GetOrCreateAABB(uint idxAABB);

		// Calculates all the aabbs that the shape intersects
		// and inserts into the respective Grid AABB
		void m_InsertAABB(Scene* pScene, Entity entityId, eBody bodyType);
		void m_InsertSphere(Scene* pScene, Entity entityId, eBody bodyType);
		void m_InsertMeshTriangle(Entity entityId, sTriangle* pTriangle);
		void m_InsertMesh(Scene* pScene, Entity entityId, eBody bodyType);

		// Insert entity in map and active map if not a static body
		void m_InsertEntity(Entity entityID, uint index, eBody bodyType);

		// Remove AABB from mapping if exists
		size_t m_RemoveAABB(uint idxAABB);

		void m_ClearAABBs();
	};
}
