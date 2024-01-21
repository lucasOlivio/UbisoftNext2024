#include "stdafx.h"

#include "GridBroadPhaseSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Utils/GridUtils.h"
#include "Engine/Utils/CollisionsUtils.h"
#include "Engine/Utils/Vector2.h"

namespace MyEngine
{
	const Vec2 BOX_LENGTH = Vec2(50.0f, 50.0f);

	typedef std::set< Entity >::iterator itEntities;
	typedef std::map< uint /*index*/, GridAABB* >::iterator itIdxAABB;
	typedef std::pair< uint /*index*/, GridAABB* > pairIdxAABB;

	void GridBroadPhaseSystem::Init()
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();
		pGrid->lengthPerBox = BOX_LENGTH;
	}

	void GridBroadPhaseSystem::Start(Scene* pScene)
	{
		// Creating AABBs grid
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();

		for (Entity entityId : SceneView<TransformComponent, RigidBodyComponent>(*pScene))
		{
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
			RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

			uint idxpos = GridUtils::LocatePoint(pTransform->position, pGrid->lengthPerBox);
			m_InsertEntity(entityId, idxpos, pRigidBody->bodyType);

			m_InsertSphere(entityId, idxpos, pTransform->position, 
						   pRigidBody->radius, pRigidBody->bodyType, pGrid);
		}
	}

	void GridBroadPhaseSystem::Update(Scene* pScene, float deltaTime)
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();
		NarrowPhaseTestsComponent* pNarrowTests = PhysicsLocator::GetNarrowPhaseTests();

		// Clear all aabbs first
		for (itIdxAABB it = pGrid->mapAABBs.begin(); it != pGrid->mapAABBs.end(); ++it)
		{
			int key = it->first;
			GridAABB* pAABB = it->second;

			pAABB->vecPassiveEntities.clear();
			pAABB->vecActiveEntities.clear();
		}

		// Clear all test groups
		pNarrowTests->passiveEntitiesToTest.clear();
		pNarrowTests->activeEntitiesToTest.clear();

		// Update aabbs entities positions
		for (Entity entityId : SceneView<TransformComponent, RigidBodyComponent>(*pScene))
		{
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
			RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

			uint idxpos = GridUtils::LocatePoint(pTransform->position, pGrid->lengthPerBox);
			m_InsertEntity(entityId, idxpos, pRigidBody->bodyType);

			m_InsertSphere(entityId, idxpos, pTransform->position, 
						   pRigidBody->radius, pRigidBody->bodyType, pGrid);
		}

		// Update testing groups for narrow phase
		int i = -1;
		for (itIdxAABB it = pGrid->mapAABBs.begin(); it != pGrid->mapAABBs.end();)
		{
			GridAABB* pAABB = it->second;

			// Only add to narrow phase testing groups if we have ally entity on aabb
			if (pAABB->vecActiveEntities.size() > 0)
			{
				std::vector<Entity> vecEnemies = {};
				std::vector<Entity> vecActive = {};

				pNarrowTests->passiveEntitiesToTest.push_back(vecEnemies);
				pNarrowTests->activeEntitiesToTest.push_back(vecActive);

				i++;

				for (Entity entityId : pAABB->vecActiveEntities)
				{
					pNarrowTests->activeEntitiesToTest[i].push_back(entityId);
				}

				for (Entity entityId : pAABB->vecPassiveEntities)
				{
					pNarrowTests->passiveEntitiesToTest[i].push_back(entityId);
				}
			}

			// Check if aabb is empty to remove from mapping
			if (pAABB->Total() == 0)
			{
				delete pAABB;
				it = pGrid->mapAABBs.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void GridBroadPhaseSystem::Render(Scene* pScene)
	{
	}

	void GridBroadPhaseSystem::End(Scene* pScene)
	{
		m_ClearAABBs();
	}

	void GridBroadPhaseSystem::Shutdown()
	{
	}

	GridAABB* GridBroadPhaseSystem::m_GetAABB(uint idxAABB)
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();

		itIdxAABB itAABB = pGrid->mapAABBs.find(idxAABB);
		if (itAABB == pGrid->mapAABBs.end())
		{
			return nullptr;
		}

		return itAABB->second;
	}

	GridAABB* GridBroadPhaseSystem::m_GetAABB(Vec2 point)
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();

		uint idxAABB = GridUtils::LocatePoint(point, pGrid->lengthPerBox);

		return m_GetAABB(idxAABB);
	}

	GridAABB* GridBroadPhaseSystem::m_GetOrCreateAABB(uint idxAABB)
	{
		GridAABB* pAABB = m_GetAABB(idxAABB);
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();

		if (pAABB)
		{
			return pAABB;
		}

		pAABB = new GridAABB();
		pAABB->minXY = GridUtils::LocatePosition(idxAABB, pGrid->lengthPerBox);
		pAABB->maxXY = pAABB->minXY + pGrid->lengthPerBox;

		pGrid->mapAABBs[idxAABB] = pAABB;

		return pAABB;
	}

	void GridBroadPhaseSystem::m_InsertSphere(Entity entityID, uint originIndex,
											  Vec2 position, float radius, eBody bodyType,
											  GridBroadphaseComponent* pGrid)
	{
		// Check collisions in the neighboring cells
		for (int i = -1; i <= 1; ++i) 
		{
			float radiusI = radius * i;
			for (int j = -1; j <= 1; ++j) 
			{
				if (j == 0 && i == 0)
				{
					// Same aabb
					continue;
				}

				float radiusJ = radius * j;

				Vec2 currRadius = Vec2(radiusI, radiusJ);
				Vec2 currPoint = position + currRadius;

				uint currIdxpos = GridUtils::LocatePoint(currPoint, pGrid->lengthPerBox);

				if (currIdxpos == originIndex)
				{
					// Same aabb
					continue;
				}

				m_InsertEntity(entityID, currIdxpos, bodyType);
			}
		}
	}

	void GridBroadPhaseSystem::m_InsertEntity(Entity entityID, uint index, eBody bodyType)
	{
		GridAABB* pAABB = m_GetOrCreateAABB(index);

		if (bodyType == eBody::PASSIVE)
		{
			pAABB->vecPassiveEntities.insert(entityID);
		}
		else
		{
			pAABB->vecActiveEntities.insert(entityID);
		}

		return;
	}

	void GridBroadPhaseSystem::m_ClearAABBs()
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();

		for (pairIdxAABB pairAABB : pGrid->mapAABBs)
		{
			delete pairAABB.second;
		}

		pGrid->mapAABBs.clear();
	}

	size_t GridBroadPhaseSystem::m_RemoveAABB(uint idxAABB)
	{
		GridAABB* pAABB = m_GetAABB(idxAABB);
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();

		if (!pAABB)
		{
			return 0;
		}

		size_t left = pGrid->mapAABBs.erase(idxAABB);
		delete pAABB;

		return left;
	}
}
