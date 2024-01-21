#include "stdafx.h"

#include "PlayerControllerSystem.h"

#include "Engine/Core/InputProperties.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/GameplayUtils.h"
#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/Math.h"

#include <app.h>

namespace MyEngine
{
    const int PLAYER_MAX_HEALTH = 200;
    const float PLAYER_FIRERATE = 0.1f;
    const int PLAYER_TOTAL_BULLETS = 200;

    const float PLAYER_ACCELERATION = 100.0f;
    const float PLAYER_DRAG = 5.0f;
    const float PLAYER_MAX_SPEED = 300.0f;
    const float PLAYER_MAX_ACCELERATION = 1500.0f;

    const float PLAYER_ROTATION_ACCELERATION = 1.0f;
    const float PLAYER_ROTATION_DRAG = 5.0f;
    const float PLAYER_MAX_ROTATION_SPEED = 3.0f;
    const float PLAYER_MAX_ROTATION_ACCELERATION = 15.0f;

    const float BULLET_SPEED = 600.0f;
    const int BULLET_DAMAGE = 10;

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
            pRotation->maxAcceleration = PLAYER_MAX_ROTATION_ACCELERATION;

            pMovement->acceleration = Vec2(0.0f, 0.0f);
            pMovement->velocity = Vec2(0.0f, 0.0f);
            pMovement->drag = PLAYER_DRAG;
            pMovement->maxSpeed = PLAYER_MAX_SPEED;
            pMovement->maxAcceleration = PLAYER_MAX_ACCELERATION;

            pPlayer->maxHealth = PLAYER_MAX_HEALTH;
            pPlayer->health = PLAYER_MAX_HEALTH;
            pPlayer->fireRate = PLAYER_FIRERATE;
            pPlayer->lastFire = PLAYER_FIRERATE;
            pPlayer->currentAmmo = PLAYER_TOTAL_BULLETS;
            pPlayer->totalAmmo = PLAYER_TOTAL_BULLETS;
        }

        return;
    }

    void PlayerControllerSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;
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

            if (App::IsKeyPressed(eKeyCodes::SPACE))
                m_Shoot(pScene, pTransform, pRigidBody, pPlayer);

            TransformUtils::ClipToWindow(pTransform->position.x, pTransform->position.y);;
            pPlayer->lastFire += deltaTime;
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
        pMovement->acceleration = pMovement->acceleration + (forward * (float)direction * PLAYER_ACCELERATION);
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
            int clockwise = Math::Sign<float>(movementDirection);

            pRotation->acceleration = pRotation->acceleration + (clockwise * (float)direction * PLAYER_ROTATION_ACCELERATION);
        }
        else
        {
            pRotation->acceleration = 0.0f;
        }
    }

    void PlayerControllerSystem::m_Shoot(Scene* pScene, TransformComponent* pTransform, 
                                         RigidBodyComponent* pRigidBody, PlayerComponent* pPlayer)
    {
        if (pPlayer->lastFire < pPlayer->fireRate || pPlayer->currentAmmo == 0)
        {
            return;
        }

        Vec2 playerDirection = TransformUtils::GetForwardVector(pTransform->angle);

        // Create projectile in front of player
        GameplayUtils::CreateProjectile(pScene, 
                                        pTransform->position + (playerDirection * pRigidBody->radius) + 1.0f, 
                                        playerDirection, BULLET_SPEED, BULLET_DAMAGE);

        pPlayer->lastFire = 0.0f;
        pPlayer->currentAmmo--;
    }
}
