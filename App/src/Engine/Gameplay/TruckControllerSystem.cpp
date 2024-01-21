#include "stdafx.h"

#include "TruckControllerSystem.h"

#include "Engine/Core/InputProperties.h"

#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/Math.h"

#include <app.h>

namespace MyEngine
{
    const float TRUCK_ACCELERATION = 100.0f;
    const float TRUCK_DRAG = 5.0f;
    const float TRUCK_MAX_SPEED = 300.0f;
    const float TRUCK_MAX_ACCELERATION = 1500.0f;

    const float TRUCK_ROTATION_ACCELERATION = 1.0f;
    const float TRUCK_ROTATION_DRAG = 5.0f;
    const float TRUCK_MAX_ROTATION_SPEED = 3.0f;
    const float TRUCK_MAX_ROTATION_ACCELERATION = 15.0f;

    void TruckControllerSystem::Init()
    {
    }

    void TruckControllerSystem::Start(Scene* pScene)
    {
        // Initializes player components
        for (Entity entityId : SceneView<TagComponent, RotationComponent, MovementComponent>(*pScene))
        {
            TagComponent* pTag = pScene->Get<TagComponent>(entityId);
            if (pTag->name != "Truck")
            {
                continue;
            }

            RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);

            pRotation->acceleration = 0;
            pRotation->velocity = 0;
            pRotation->drag = TRUCK_ROTATION_DRAG;
            pRotation->maxSpeed = TRUCK_MAX_ROTATION_SPEED;
            pRotation->maxAcceleration = TRUCK_MAX_ROTATION_ACCELERATION;

            pMovement->acceleration = Vec2(0.0f, 0.0f);
            pMovement->velocity = Vec2(0.0f, 0.0f);
            pMovement->drag = TRUCK_DRAG;
            pMovement->maxSpeed = TRUCK_MAX_SPEED;
            pMovement->maxAcceleration = TRUCK_MAX_ACCELERATION;
        }

        return;
    }

    void TruckControllerSystem::Update(Scene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;
        // Handle inputs for player gameplay
        for (Entity entityId : SceneView<TagComponent, TransformComponent, RotationComponent, MovementComponent>(*pScene))
        {
            TagComponent* pTag = pScene->Get<TagComponent>(entityId);
            if (pTag->name != "Truck")
            {
                continue;
            }

            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);

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

            TransformUtils::ClipToWindow(pTransform->position.x, pTransform->position.y);
        }
    }

    void TruckControllerSystem::Render(Scene* pScene)
    {
    }

    void TruckControllerSystem::End(Scene* pScene)
    {
    }

    void TruckControllerSystem::Shutdown()
    {
    }

    void TruckControllerSystem::m_Accelerate(TransformComponent* pTransform, MovementComponent* pMovement, int direction)
    {
        Vec2 forward = TransformUtils::GetForwardVector(pTransform->worldAngle);
        pMovement->acceleration = pMovement->acceleration + (forward * (float)direction * TRUCK_ACCELERATION);
    }

    void TruckControllerSystem::m_Rotate(TransformComponent* pTransform, RotationComponent* pRotation,
        MovementComponent* pMovement, int direction)
    {
        // Only rotate when car is moving
        float movementSpeed = pMovement->velocity.Length();
        if (movementSpeed > 0)
        {
            Vec2 forward = TransformUtils::GetForwardVector(pTransform->worldAngle);
            float movementDirection = pMovement->velocity.Dot(forward);
            int clockwise = Math::Sign<float>(movementDirection);

            pRotation->acceleration = pRotation->acceleration + (clockwise * (float)direction * TRUCK_ROTATION_ACCELERATION);
        }
        else
        {
            pRotation->acceleration = 0.0f;
        }
    }
}
