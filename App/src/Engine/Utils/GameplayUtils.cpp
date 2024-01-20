#include "stdafx.h"

#include "GameplayUtils.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/GraphicsUtils.h"

const std::string ZOMBIE_SPRITE = "zombie.png";

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
		pSprite->name = DEFAULT_SPRITE_PATH + "zombie.png";
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSprite, pTransform);

		MovementComponent* pMovement = pScene->AddComponent<MovementComponent>(zombieId);
		pMovement->acceleration = Vec2(0.0f, 0.0f);
		pMovement->velocity = FORWARD_VECTOR * speed;
		pMovement->maxSpeed = speed;

		FollowTargetComponent* pFollowTarget = pScene->AddComponent<FollowTargetComponent>(zombieId);
		pFollowTarget->entityToFollow = GetPlayerId(pScene);

        return zombieId;
    }

	Entity GameplayUtils::GetPlayerId(Scene* pScene)
	{
		SceneView<PlayerComponent>::Iterator it = SceneView<PlayerComponent>(*pScene).begin();

		return *it;
	}
}
