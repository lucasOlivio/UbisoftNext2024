#include "stdafx.h"

#include "GameplayUtils.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/GraphicsUtils.h"
#include "Engine/Utils/TransformUtils.h"

const std::string ZOMBIE_SPRITE = "zombie.png";
const std::string BULLET_SPRITE = "bullet.png";

const float ZOMBIE_RADIUS = 25.0f;
const float BULLET_RADIUS = 10.0f;

const int ZOMBIE_POINTS = 1;
const int ZOMBIE_DAMAGE = 1;

namespace MyEngine
{
    Entity GameplayUtils::CreateZombie(Scene* pScene, Vec2 position, float speed)
    {
		Entity zombieId = pScene->CreateEntity();
		TagComponent* pTag = pScene->AddComponent<TagComponent>(zombieId);
		pTag->name = "Zombie";

		TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(zombieId);
		pTransform->position = position;
		pTransform->angle = 0;
		pTransform->scale = 1;

		MovementComponent* pMovement = pScene->AddComponent<MovementComponent>(zombieId);
		pMovement->acceleration = Vec2(0.0f, 0.0f);
		pMovement->velocity = FORWARD_VECTOR * speed;
		pMovement->maxSpeed = speed;

		FollowTargetComponent* pFollowTarget = pScene->AddComponent<FollowTargetComponent>(zombieId);
		pFollowTarget->entityToFollow = GetPlayerId(pScene);

		RigidBodyComponent* pRigidBody = pScene->AddComponent<RigidBodyComponent>(zombieId);
		pRigidBody->bodyType = eBody::PASSIVE;
		pRigidBody->radius = ZOMBIE_RADIUS;

		PointComponent* pPoint = pScene->AddComponent< PointComponent>(zombieId);
		pPoint->points = ZOMBIE_POINTS;

		EnemyComponent* pEnemy = pScene->AddComponent< EnemyComponent>(zombieId);
		pEnemy->damage = ZOMBIE_DAMAGE;

		SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(zombieId);
		pSprite->name = DEFAULT_SPRITE_PATH + ZOMBIE_SPRITE;
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSprite, pTransform);

        return zombieId;
    }

	Entity GameplayUtils::CreateProjectile(Scene* pScene, Vec2 position, Vec2 direction, float speed, int damage)
	{
		Entity projectileId = pScene->CreateEntity();
		TagComponent* pTag = pScene->AddComponent<TagComponent>(projectileId);
		pTag->name = "Projectile";

		TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(projectileId);
		pTransform->position = position;
		pTransform->angle = FORWARD_VECTOR.Angle(direction);
		pTransform->scale = 1;

		MovementComponent* pMovement = pScene->AddComponent<MovementComponent>(projectileId);
		pMovement->acceleration = Vec2(0.0f, 0.0f);
		pMovement->velocity = direction * speed;
		pMovement->maxSpeed = speed;

		ProjectileComponent* pProjectile = pScene->AddComponent<ProjectileComponent>(projectileId);
		pProjectile->damage = damage;

		RigidBodyComponent* pRigidBody = pScene->AddComponent<RigidBodyComponent>(projectileId);
		pRigidBody->bodyType = eBody::ACTIVE;
		pRigidBody->radius = BULLET_RADIUS;

		SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(projectileId);
		pSprite->name = DEFAULT_SPRITE_PATH + BULLET_SPRITE;
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSprite, pTransform);

		return projectileId;
	}

	Entity GameplayUtils::GetPlayerId(Scene* pScene)
	{
		SceneView<PlayerComponent>::Iterator it = SceneView<PlayerComponent>(*pScene).begin();

		return *it;
	}
}
