#include "pch.h"

#include "GridBroadPhaseSystem.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Utils/GridUtils.h"
#include "Engine/Utils/TransformUtils.h"
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

			uint idxpos = GridUtils::LocatePoint(pTransform->worldPosition, pGrid->lengthPerBox);
			m_InsertEntity(entityId, idxpos, pRigidBody->bodyType);

			switch (pRigidBody->shapeType)
			{
			case eShape::AABB:
				m_InsertAABB(pScene, entityId, pRigidBody->bodyType);
				break;
			case eShape::SPHERE:
				m_InsertSphere(pScene, entityId, pRigidBody->bodyType);
				break;
			case eShape::MESH_OF_TRIANGLES:
				m_InsertMesh(pScene, entityId, pRigidBody->bodyType);
				break;
			default:
				break;
			}
		}
	}

	void GridBroadPhaseSystem::Update(Scene* pScene, float deltaTime)
	{
		StateComponent* pState = CoreLocator::GetState();
		if (pState->currState == eStates::SIMULATION_STOPPED)
		{
			return;
		}

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
		pNarrowTests->trianglesToTest.clear();

		// Update aabbs non static entities positions
		for (Entity entityId : SceneView<TransformComponent, RigidBodyComponent>(*pScene))
		{
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
			RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

			if (pRigidBody->bodyType == eBody::STATIC)
			{
				continue;
			}

			uint idxpos = GridUtils::LocatePoint(pTransform->worldPosition, pGrid->lengthPerBox);
			m_InsertEntity(entityId, idxpos, pRigidBody->bodyType);

			switch (pRigidBody->shapeType)
			{
			case eShape::AABB:
				m_InsertAABB(pScene, entityId, pRigidBody->bodyType);
				break;
			case eShape::SPHERE:
				m_InsertSphere(pScene, entityId, pRigidBody->bodyType);
				break;
			default:
				break;
			}
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
				std::vector<sTriangle*> vecTriangles = {};

				pNarrowTests->staticEntitiesToTest.push_back(vecStatics);
				pNarrowTests->nonStaticEntitiesToTest.push_back(vecNonStatics);
				pNarrowTests->trianglesToTest.push_back(vecTriangles);

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

			for (sTriangle* triangle : pAABB->vecTriangles)
			{
				pNarrowTests->trianglesToTest[i].push_back(triangle);
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

	GridAABB* GridBroadPhaseSystem::m_GetAABB(glm::vec3 point)
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
		pAABB->minXYZ = GridUtils::LocatePosition(idxAABB, pGrid->lengthPerBox);
		pAABB->maxXYZ = pAABB->minXYZ + pGrid->lengthPerBox;

		pGrid->mapAABBs[idxAABB] = pAABB;

		return pAABB;
	}

	void GridBroadPhaseSystem::m_InsertAABB(Scene* pScene, Entity entityId, eBody bodyType)
	{
		AABBColliderComponent* pAABB = pScene->Get<AABBColliderComponent>(entityId);
		if (!pAABB)
		{
			return;
		}
	}

	void GridBroadPhaseSystem::m_InsertSphere(Scene* pScene, Entity entityId, eBody bodyType)
	{
		SphereColliderComponent* pSphere = pScene->Get<SphereColliderComponent>(entityId);
		if (!pSphere)
		{
			return;
		}

		//// Check collisions in the neighboring cells

		//// Calculate the number of neighboring cells to check based on the sphere radius
		//int numNeighborsX = (int)(ceil(pSphere->radius / m_lengthPerBox.x));
		//int numNeighborsY = (int)(ceil(pSphere->radius / m_lengthPerBox.y));
		//int numNeighborsZ = (int)(ceil(pSphere->radius / m_lengthPerBox.z));

		//glm::vec3 posCell = GridUtils::LocatePosition(idxpos, m_lengthPerBox);
		//for (int i = -numNeighborsX; i <= numNeighborsX; ++i) 
		//{
		//	float radiusI = pSphere->radius / i;
		//	for (int j = -numNeighborsY; j <= numNeighborsY; ++j) 
		//	{
		//		float radiusJ = pSphere->radius / j;
		//		for (int k = -numNeighborsZ; k <= numNeighborsZ; ++k) 
		//		{
		//			float radiusK = pSphere->radius / k;

		//			// Proportional radius that would be in neighbor cell
		//			glm::vec3 currRadius = glm::vec3(radiusI, radiusJ, radiusK);
		//			glm::vec3 currPoint = pTransform->worldPosition + currRadius;

		//			uint currIdxpos = GridUtils::LocatePoint(currPoint, m_lengthPerBox);

		//			if (idxpos == currIdxpos)
		//			{
		//				// Still in the same grid
		//				continue;
		//			}

		//			// Different grid, insert entity in it too
		//			m_InsertEntity(entityId, currIdxpos, bodyType);
		//		}
		//	}
		//}
	}

	void GridBroadPhaseSystem::m_InsertMesh(Scene* pScene, Entity entityId, eBody bodyType)
	{
		MeshColliderComponent* pMeshCollider = pScene->Get<MeshColliderComponent>(entityId);
		sMesh* pMesh = pMeshCollider->pMesh;
		if (!pMeshCollider || !pMeshCollider->pMesh)
		{
			return;
		}

		// for every triangle in the mesh insert into aabb
		for (uint i = 0; i < pMesh->numberOfTriangles; i++)
		{
			m_InsertMeshTriangle(entityId, &(pMesh->pTriangles[i]));
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

	void GridBroadPhaseSystem::m_InsertMeshTriangle(Entity entityId, sTriangle* pTriangle)
	{
		GridBroadphaseComponent* pGrid = PhysicsLocator::GetGridBroadphase();
		pTriangle->calcNormal();

		// Locate each vertex
		uint idxV1 = GridUtils::LocatePoint(pTriangle->vertices[0], pGrid->lengthPerBox);
		uint idxV2 = GridUtils::LocatePoint(pTriangle->vertices[0], pGrid->lengthPerBox);
		uint idxV3 = GridUtils::LocatePoint(pTriangle->vertices[0], pGrid->lengthPerBox);

		// TODO: When a pTriangle edge passes 3 or more aabbs it should be in those aabbs too
		// Insert pTriangle into all AABBs that it intersects
		GridAABB* pAABB = m_GetOrCreateAABB(idxV1);
		pAABB->vecTriangles.insert(pTriangle);

		if (idxV2 != idxV1)
		{
			GridAABB* pAABB2 = m_GetOrCreateAABB(idxV2);
			pAABB->vecTriangles.insert(pTriangle);
		}

		if (idxV3 != idxV1 && idxV3 != idxV2)
		{
			GridAABB* pAABB3 = m_GetOrCreateAABB(idxV3);
			pAABB->vecTriangles.insert(pTriangle);
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
