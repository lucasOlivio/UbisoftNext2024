#include "stdafx.h"

#include "GameplayUtils.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/GraphicsUtils.h"
#include "Engine/Utils/TransformUtils.h"

const std::string ZOMBIE_SPRITE = "zombie.png";
const std::string BULLET_SPRITE = "bullet.png";

namespace MyEngine
{
    Entity GameplayUtils::CreateZombie(Scene* pScene, Vec2 position, float speed)
    {
		Entity zombieId = pScene->CreateEntity();
		TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(zombieId);
		pTransform->position = position;
		pTransform->angle = 0;
		pTransform->scale = 1;

		SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(zombieId);
		pSprite->name = DEFAULT_SPRITE_PATH + ZOMBIE_SPRITE;
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSprite, pTransform);

		MovementComponent* pMovement = pScene->AddComponent<MovementComponent>(zombieId);
		pMovement->acceleration = Vec2(0.0f, 0.0f);
		pMovement->velocity = FORWARD_VECTOR * speed;
		pMovement->maxSpeed = speed; // To avoid movement system to keep reseting velocity

		FollowTargetComponent* pFollowTarget = pScene->AddComponent<FollowTargetComponent>(zombieId);
		pFollowTarget->entityToFollow = GetPlayerId(pScene);

        return zombieId;
    }

	Entity GameplayUtils::CreateProjectile(Scene* pScene, Vec2 position, Vec2 direction, float speed)
	{
		Entity projectileId = pScene->CreateEntity();
		TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(projectileId);
		pTransform->position = position;
		pTransform->angle = FORWARD_VECTOR.Angle(direction);
		pTransform->scale = 1;

		SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(projectileId);
		pSprite->name = DEFAULT_SPRITE_PATH + BULLET_SPRITE;
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSprite, pTransform);

		MovementComponent* pMovement = pScene->AddComponent<MovementComponent>(projectileId);
		pMovement->acceleration = Vec2(0.0f, 0.0f);
		pMovement->velocity = direction * speed;
		pMovement->maxSpeed = speed; // To avoid movement system to keep reseting velocity

		return projectileId;
	}

	Entity GameplayUtils::GetPlayerId(Scene* pScene)
	{
		SceneView<PlayerComponent>::Iterator it = SceneView<PlayerComponent>(*pScene).begin();

		return *it;
	}
}
