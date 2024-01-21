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
        NarrowPhaseTestsComponent* pTests = PhysicsLocator::GetNarrowPhaseTests();

        // The first layer is the grouping of objects to test
        for (int group = 0; group < pTests->allyEntitiesToTest.size(); group++)
        {
            std::vector<Entity> allyGroup = pTests->allyEntitiesToTest[group];
            std::vector<Entity> enemyGroup = pTests->enemyEntitiesToTest[group];

            for (int i = 0; i < allyGroup.size(); i++)
            {
                Entity entityId = allyGroup[i];
                TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
                RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

                // Check allies against enemies only
                m_CheckSphereOverlaps(pScene, entityId, pTransform->position, pRigidBody->radius, i,
                                      allyGroup,
                                      enemyGroup);

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
								                Vec2 positionA,
                                                float radiusA,
                                                const int index,
                                                const std::vector<Entity>& allyEntities,
                                                const std::vector<Entity>& enemyEntities)
    {
        // Check entity A against all enemies
        for (int j = 0; j < enemyEntities.size(); j++)
        {
            Entity entityIdB = enemyEntities[j];
            bool isCollision = m_CheckSphereEntityOverlap(pScene, entityIdA,
                                                          positionA,
                                                          radiusA, 
                                                          entityIdB);
        }
    }

    bool CollisionSystem::m_CheckSphereEntityOverlap(Scene* pScene,
										             Entity entityIdA,
								                     Vec2 positionA,
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
                                                            positionA,
                                                            pRigidBodyB->radius,
                                                            pTransformB->position);

        if (!isCollision)
        {
            return false;
        }

        sCollisionData collData = sCollisionData();
        collData.pScene = pScene;
        collData.entityA = entityIdA;
        collData.entityB = entityIdB;
        collData.collisionNormalA = CollisionsUtils::SphereSphere_Normal(positionA,
                                                                         pTransformB->position);
        collData.collisionNormalB = -collData.collisionNormalA;
        collData.contactPoint = CollisionsUtils::SphereSphere_CollisionPoint(radiusA,
                                                                             positionA,
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
