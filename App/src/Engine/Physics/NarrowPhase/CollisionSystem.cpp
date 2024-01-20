#include "stdafx.h"

#include "CollisionSystem.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/EventBusLocator.hpp"
#include "Engine/Events/CollisionEvent.h"

#include "Engine/Utils/CollisionsUtils.h"

namespace MyEngine
{
    void CollisionSystem::Init()
    {
    }

    void CollisionSystem::Start(Scene* pScene)
    {
    }

    void CollisionSystem::Update(Scene* pScene, float deltaTime)
    {
        StateComponent* pState = CoreLocator::GetState();
        if (pState->currState == eStates::SIMULATION_STOPPED)
        {
            return;
        }

        NarrowPhaseTestsComponent* pTests = PhysicsLocator::GetNarrowPhaseTests();

        // The first layer is the grouping of objects to test
        for (int group = 0; group < pTests->nonStaticEntitiesToTest.size(); group++)
        {
            std::vector<Entity> nonStaticGroup = pTests->nonStaticEntitiesToTest[group];
            std::vector<Entity> staticGroup = pTests->staticEntitiesToTest[group];

            for (int i = 0; i < nonStaticGroup.size(); i++)
            {
                Entity entityId = nonStaticGroup[i];
                TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
                RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

                m_CheckSphereOverlaps(pScene, entityId, pTransform, pRigidBody->radius, i,
                                      nonStaticGroup,
                                      staticGroup);

            }
        }
    }

    void CollisionSystem::Render(Scene* pScene)
    {
    }

    void CollisionSystem::End(Scene* pScene)
    {
    }

    void CollisionSystem::Shutdown()
    {
    }

    void CollisionSystem::m_TriggerCollisionEnter(const sCollisionData& collData)
    {
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        CollisionEnterEvent collEvent = CollisionEnterEvent();
        collEvent.collisionData = collData;
        pEventBus->Publish(collEvent);
    }

    void CollisionSystem::m_CheckSphereOverlaps(Scene* pScene,
								                Entity entityIdA,
                                                TransformComponent* pTransformA,
                                                float radiusA,
                                                const int index,
                                                const std::vector<Entity>& nonStaticEntities,
                                                const std::vector<Entity>& staticEntities)
    {
        // Start from one entity ahead so we dont test repeated
        for (int j = index + 1; j < nonStaticEntities.size(); j++)
        {
            Entity entityIdB = nonStaticEntities[j];
            bool isCollision = m_CheckSphereEntityOverlap(pScene, entityIdA,
                                                          pTransformA,
                                                          radiusA, 
                                                          entityIdB);
        }

        for (int j = 0; j < staticEntities.size(); j++)
        {
            Entity entityIdB = nonStaticEntities[j];
            bool isCollision = m_CheckSphereEntityOverlap(pScene, entityIdA,
                                                          pTransformA,
                                                          radiusA, 
                                                          entityIdB);
        }
    }

    bool CollisionSystem::m_CheckSphereEntityOverlap(Scene* pScene,
										             Entity entityIdA,
										             TransformComponent* pTransformA,
										             float radiusA,
										             Entity entityIdB)
    {
        TransformComponent* pTransformB = pScene->Get<TransformComponent>(entityIdB);
        RigidBodyComponent* pRigidBodyB = pScene->Get<RigidBodyComponent>(entityIdB);

        MovementComponent* pMovementA = pScene->Get<MovementComponent>(entityIdA);
        MovementComponent* pMovementB = pScene->Get<MovementComponent>(entityIdB);

        // Get the right collider to test against
        bool isCollision = false;
        isCollision = CollisionsUtils::SphereSphere_Overlap(radiusA,
                                                            pTransformA->position,
                                                            pRigidBodyB->radius,
                                                            pTransformB->position);

        if (!isCollision)
        {
            return false;
        }

        sCollisionData collData = sCollisionData();
        collData.entityA = entityIdA;
        collData.entityB = entityIdB;
        collData.collisionNormalA = CollisionsUtils::SphereSphere_Normal(pTransformA->position,
                                                                         pTransformB->position);
        collData.collisionNormalB = -collData.collisionNormalA;
        collData.contactPoint = CollisionsUtils::SphereSphere_CollisionPoint(radiusA,
                                                                             pTransformA->position,
                                                                             collData.collisionNormalA,
                                                                             pRigidBodyB->radius,
                                                                             pTransformB->position);
        collData.velocityAtCollisionA = pMovementA->velocity;

        if (pMovementB)
        {
            collData.velocityAtCollisionB = pMovementB->velocity;
        }

        m_TriggerCollisionEnter(collData);

        return true;
    }
}
