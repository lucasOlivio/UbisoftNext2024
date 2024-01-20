#include "stdafx.h"

#include "GridBroadPhaseSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Utils/GridUtils.h"
#include "Engine/Utils/CollisionsUtils.h"

namespace MyEngine
{
	typedef std::set< Entity >::iterator itEntities;
	typedef std::map< uint /*index*/, GridAABB* >::iterator itIdxAABB;
	typedef std::pair< uint /*index*/, GridAABB* > pairIdxAABB;

	void GridBroadPhaseSystem::Init()
	{
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

			m_InsertSphere(entityId, idxpos, pTransform, pRigidBody, pGrid);
		}
	}

	void GridBroadPhaseSystem::Update(Scene* pScene, float deltaTime)
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();
		NarrowPhaseTestsComponent* pNarrowTests = PhysicsLocator::GetNarrowPhaseTests();

		// Clear non static entities first
		for (itIdxAABB it = pGrid->mapAABBs.begin(); it != pGrid->mapAABBs.end(); ++it)
		{
			int key = it->first;
			GridAABB* pAABB = it->second;

			pAABB->vecNonStaticEntities.clear();
		}

		// Clear all test groups
		pNarrowTests->staticEntitiesToTest.clear();
		pNarrowTests->nonStaticEntitiesToTest.clear();

		// Update aabbs non static entities positions
		for (Entity entityId : SceneView<TransformComponent, RigidBodyComponent>(*pScene))
		{
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
			RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

			if (pRigidBody->bodyType == eBody::STATIC)
			{
				continue;
			}

			uint idxpos = GridUtils::LocatePoint(pTransform->position, pGrid->lengthPerBox);
			m_InsertEntity(entityId, idxpos, pRigidBody->bodyType);

			m_InsertSphere(entityId, idxpos, pTransform, pRigidBody, pGrid);
		}

		// Update testing groups for narrow phase
		int i = -1;
		for (itIdxAABB it = pGrid->mapAABBs.begin(); it != pGrid->mapAABBs.end();)
		{
			GridAABB* pAABB = it->second;

			// Only add to narrow phase testing groups if we have non static entity on aabb
			if (pAABB->vecNonStaticEntities.size() > 0)
			{
				std::vector<Entity> vecStatics = {};
				std::vector<Entity> vecNonStatics = {};

				pNarrowTests->staticEntitiesToTest.push_back(vecStatics);
				pNarrowTests->nonStaticEntitiesToTest.push_back(vecNonStatics);

				i++;
			}

			for (Entity entityId : pAABB->vecNonStaticEntities)
			{
				pNarrowTests->nonStaticEntitiesToTest[i].push_back(entityId);
			}

			for (Entity entityId : pAABB->vecStaticEntities)
			{
				pNarrowTests->staticEntitiesToTest[i].push_back(entityId);
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
											  TransformComponent* pTransform, 
											  RigidBodyComponent* pRigidBody,
											  GridBroadphaseComponent* pGrid)
	{
		// Check collisions in the neighboring cells
		for (int i = -1; i <= 1; ++i) 
		{
			float radiusI = pRigidBody->radius / i;
			for (int j = -1; j <= 1; ++j) 
			{
				float radiusJ = pRigidBody->radius / j;

				Vec2 currRadius = Vec2(radiusI, radiusJ);
				Vec2 currPoint = pTransform->position + currRadius;

				uint currIdxpos = GridUtils::LocatePoint(currPoint, pGrid->lengthPerBox);

				if (currIdxpos == originIndex)
				{
					// Same aabb
					continue;
				}

				m_InsertEntity(entityID, currIdxpos, pRigidBody->bodyType);
			}
		}
	}

	void GridBroadPhaseSystem::m_InsertEntity(Entity entityID, uint index, eBody bodyType)
	{
		GridAABB* pAABB = m_GetOrCreateAABB(index);
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();
		NarrowPhaseTestsComponent* pNarrowTests = PhysicsLocator::GetNarrowPhaseTests();

		if (bodyType == eBody::STATIC)
		{
			pAABB->vecStaticEntities.insert(entityID);
		}
		else
		{
			pAABB->vecNonStaticEntities.insert(entityID);
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
