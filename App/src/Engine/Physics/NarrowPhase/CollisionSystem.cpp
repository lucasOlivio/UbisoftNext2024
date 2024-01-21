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
        for (int group = 0; group < pTests->activeEntitiesToTest.size(); group++)
        {
            std::vector<Entity> allyGroup = pTests->activeEntitiesToTest[group];
            std::vector<Entity> enemyGroup = pTests->passiveEntitiesToTest[group];

            for (int i = 0; i < allyGroup.size(); i++)
            {
                Entity entityId = allyGroup[i];
                TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
                RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

                // Check allies against enemies only
                m_CheckSphereCollision(pScene, entityId, pTransform->position, pRigidBody->radius, i,
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

    bool CollisionSystem::m_RegisterFrameCollision(const sCollisionData& collData)
    {
        FrameCollisionComponent* pFrameColl = PhysicsLocator::GetFrameCollision();
        FrameCounterComponent* pFrames = CoreLocator::GetFrameCounter();

        // Module to make sure we stay in FRAME_RATE size
        int currFrame = pFrames->frameCount % FRAME_RATE;
        bool isNewCollision = pFrameColl->collisions[currFrame].insert(collData).second;
        
        return isNewCollision;
    }

    void CollisionSystem::m_CheckSphereCollision(Scene* pScene,
								                Entity entityIdActive,
								                Vec2 positionActive,
                                                float radiusActive,
                                                const int index,
                                                const std::vector<Entity>& activeEntities,
                                                const std::vector<Entity>& passiveEntities)
    {
        // Check entity A against all enemies
        for (int j = 0; j < passiveEntities.size(); j++)
        {
            Entity entityIdPassive = passiveEntities[j];
            bool isCollision = m_CheckSphereEntityOverlap(pScene, entityIdActive,
                                                          positionActive,
                                                          radiusActive, 
                                                          entityIdPassive);
            
            if (!isCollision)
            {
                continue;
            }

            sCollisionData collData = sCollisionData();
            collData.pScene = pScene;
            collData.entityActive = entityIdActive;
            collData.entityPassive = entityIdPassive;

            bool isNewCollision = m_RegisterFrameCollision(collData);
            if (!isNewCollision)
            {
                continue;
            }

            m_TriggerCollisionEnter(collData);
        }
    }

    bool CollisionSystem::m_CheckSphereEntityOverlap(Scene* pScene,
										             Entity entityIdActive,
								                     Vec2 positionActive,
										             float radiusActive,
										             Entity entityIdPassive)
    {
        TransformComponent* pTransformPassive = pScene->Get<TransformComponent>(entityIdPassive);
        RigidBodyComponent* pRigidBodyPassive = pScene->Get<RigidBodyComponent>(entityIdPassive);

        // Get the right collider to test against
        bool isCollision = false;
        isCollision = CollisionsUtils::SphereSphere_Overlap(radiusActive,
                                                            positionActive,
                                                            pRigidBodyPassive->radius,
                                                            pTransformPassive->position);

        return isCollision;
    }
}
