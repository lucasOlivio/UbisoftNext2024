#include "stdafx.h"

#include "PlayerControllerSystem.h"

#include "Engine/Core/InputProperties.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/Math.h"

#include <app.h>

const int PLAYER_MAX_HEALTH = 100;
const float PLAYER_FIRERATE = 1.0f; // Shots per second

const float PLAYER_ACCELERATION = 3000.0f;
const float PLAYER_DRAG = 15.0f;
const float PLAYER_MAX_SPEED = 5000.0f;

const float PLAYER_ROTATION_ACCELERATION = 30.0f;
const float PLAYER_MAX_ROTATION_SPEED = 50.0f;
const float PLAYER_ROTATION_DRAG = 15.0f;

namespace MyEngine
{
    void PlayerControllerSystem::Init()
    {
    }

    void PlayerControllerSystem::Start(Scene* pScene)
    {
        // Initializes player components
        for (Entity entityId : SceneView<RotationComponent, MovementComponent, PlayerComponent>(*pScene))
        {
            RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);
            PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(entityId);

            pRotation->acceleration = 0;
            pRotation->velocity = 0;
            pRotation->drag = PLAYER_ROTATION_DRAG;
            pRotation->maxSpeed = PLAYER_MAX_ROTATION_SPEED;

            pMovement->acceleration = Vec2(0.0f, 0.0f);
            pMovement->velocity = Vec2(0.0f, 0.0f);
            pMovement->drag = PLAYER_DRAG;
            pMovement->maxSpeed = PLAYER_MAX_SPEED;

            pPlayer->health = PLAYER_MAX_HEALTH;
            pPlayer->fireRate = PLAYER_FIRERATE;
            pPlayer->lastFire = PLAYER_FIRERATE;
        }

        return;
    }

    void PlayerControllerSystem::Update(Scene* pScene, float deltaTime)
    {
        // Handle inputs for player gameplay
        for (Entity entityId : SceneView<TransformComponent, RotationComponent, 
                                         MovementComponent, PlayerComponent,
                                         RigidBodyComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);
            RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);
            PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(entityId);

            if (App::IsKeyPressed(eKeyCodes::W))
                m_Accelerate(pTransform, pMovement, 1);
            else if (App::IsKeyPressed(eKeyCodes::S))
                m_Accelerate(pTransform, pMovement, -1);
            else
                pMovement->acceleration = Vec2(0.0f, 0.0f);

            if (App::IsKeyPressed(eKeyCodes::D))
                m_Rotate(pTransform, pRotation, pMovement, -1);
            else if (App::IsKeyPressed(eKeyCodes::A))
                m_Rotate(pTransform, pRotation, pMovement, 1);
            else
                pRotation->acceleration = 0.0f;

            m_ClipPlayerToWindow(pTransform, pRigidBody);
        }
    }

    void PlayerControllerSystem::Render(Scene* pScene)
    {
    }

    void PlayerControllerSystem::End(Scene* pScene)
    {
    }

    void PlayerControllerSystem::Shutdown()
    {
    }

    void PlayerControllerSystem::m_Accelerate(TransformComponent* pTransform, MovementComponent* pMovement, int direction)
    {
        Vec2 forward = TransformUtils::GetForwardVector(pTransform->angle);
        pMovement->acceleration = forward * (float)direction * PLAYER_ACCELERATION;
    }

    void PlayerControllerSystem::m_Rotate(TransformComponent* pTransform, RotationComponent* pRotation, 
                                          MovementComponent* pMovement, int direction)
    {
        // Only rotate when car is moving
        float movementSpeed = pMovement->velocity.Length();
        if (movementSpeed > 0)
        {
            Vec2 forward = TransformUtils::GetForwardVector(pTransform->angle);
            float movementDirection = pMovement->velocity.Dot(forward);

            pRotation->acceleration = Math::Sign<float>(movementDirection) * direction * PLAYER_ROTATION_ACCELERATION;
        }
        else
        {
            pRotation->acceleration = 0.0f;
        }
    }

    void PlayerControllerSystem::m_ClipPlayerToWindow(TransformComponent* pTransform, RigidBodyComponent* pRigidBody)
    {
        if (pTransform->position.x + pRigidBody->radius > APP_VIRTUAL_WIDTH)
        {
            pTransform->position.x = APP_VIRTUAL_WIDTH - pRigidBody->radius;
        }
        else if (pTransform->position.x - pRigidBody->radius < 0.0f)
        {
            pTransform->position.x = pRigidBody->radius;
        }

        if (pTransform->position.y + pRigidBody->radius > APP_VIRTUAL_HEIGHT)
        {
            pTransform->position.y = APP_VIRTUAL_HEIGHT - pRigidBody->radius;
        }
        else if (pTransform->position.y - pRigidBody->radius < 0.0f)
        {
            pTransform->position.y = pRigidBody->radius;
        }
    }
}
