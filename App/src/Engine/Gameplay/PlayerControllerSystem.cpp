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
    const int PLAYER_MAX_HEALTH = 100;
    const float PLAYER_FIRERATE = 0.1f;
    const int PLAYER_TOTAL_BULLETS = 100;

    const float BULLET_SPEED = 600.0f;
    const int BULLET_DAMAGE = 10;

    void PlayerControllerSystem::Init()
    {
    }

    void PlayerControllerSystem::Start(Scene* pScene)
    {
        // Initializes player components
        for (Entity entityId : SceneView<PlayerComponent>(*pScene))
        {
            PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(entityId);

            pPlayer->maxHealth = PLAYER_MAX_HEALTH;
            pPlayer->health = PLAYER_MAX_HEALTH;
            pPlayer->fireRate = PLAYER_FIRERATE;
            pPlayer->lastFire = PLAYER_FIRERATE;
            pPlayer->currentAmmo = PLAYER_TOTAL_BULLETS;
            pPlayer->maxAmmo = PLAYER_TOTAL_BULLETS;
        }

        return;
    }

    void PlayerControllerSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;
        // Handle inputs for player gameplay
        for (Entity entityId : SceneView<TransformComponent, ParentComponent, 
                                         PlayerComponent, RigidBodyComponent,
                                         SoundComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            ParentComponent* pParent = pScene->Get<ParentComponent>(entityId);
            RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);
            PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(entityId);
            SoundComponent* pSound = pScene->Get<SoundComponent>(entityId);

            if (App::IsKeyPressed(eKeyCodes::SPACE))
            {
                m_Shoot(pScene, pTransform, pRigidBody, pPlayer, pSound);
            }

            pPlayer->lastFire += deltaTime;

            // Follow mouse
            TransformComponent* pTransformTruck = pScene->Get<TransformComponent>(pParent->parentId);
            Vec2 mousePos = Vec2();
            App::GetMousePos(mousePos.x, mousePos.y);
            Vec2 direction = mousePos - pTransform->worldPosition;

            // Update facing direction
            float angle = FORWARD_VECTOR.Angle(direction);
            pTransform->angle = angle - pTransformTruck->angle;
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

    void PlayerControllerSystem::m_Shoot(Scene* pScene, TransformComponent* pTransform, 
                                         RigidBodyComponent* pRigidBody, PlayerComponent* pPlayer,
                                         SoundComponent* pSound)
    {
        if (pPlayer->lastFire < pPlayer->fireRate || pPlayer->currentAmmo == 0)
        {
            return;
        }

        Vec2 playerDirection = TransformUtils::GetForwardVector(pTransform->worldAngle);

        // Create projectile in front of player
        GameplayUtils::CreateProjectile(pScene, 
                                        pTransform->worldPosition + (playerDirection * pRigidBody->radius) + 1.0f, 
                                        playerDirection, BULLET_SPEED, BULLET_DAMAGE);

        pPlayer->lastFire = 0.0f;
        pPlayer->currentAmmo--;
        pSound->play = true;
    }
}
