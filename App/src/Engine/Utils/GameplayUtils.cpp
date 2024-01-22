#include "stdafx.h"

#include "GameplayUtils.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/SceneView.hpp"

#include "Engine/Utils/GraphicsUtils.h"
#include "Engine/Utils/TransformUtils.h"

#include <app.h>

const std::string BACKGROUND_SPRITE = "background.jpg";
const std::string PLAYER_SPRITE = "player_chaingun.png";
const std::string TRUCK_SPRITE = "Mini_truck.png";
const std::string ZOMBIE_SPRITE = "zombie.png";
const std::string BULLET_SPRITE = "bullet.png";

const std::string GUNSHOT_SOUND = "gunshot.wav";
const float GUNSHOT_DURATION = 0.2f;

const float PLAYER_RADIUS = 25.0f;
const float ZOMBIE_RADIUS = 25.0f;
const float BULLET_RADIUS = 10.0f;

const int ZOMBIE_POINTS = 1;
const int ZOMBIE_DAMAGE = 1;

namespace MyEngine
{
	Entity GameplayUtils::CreateBackground(Scene* pScene, Vec2 position)
	{
		Entity backgroundId = pScene->CreateEntity();
		TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(backgroundId);
		pTransform->position = position;
		pTransform->angle = 0;
		pTransform->scale = 1;

		SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(backgroundId);
		pSprite->name = DEFAULT_SPRITE_PATH + BACKGROUND_SPRITE;
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSprite, pTransform);

		return backgroundId;
	}

	Entity GameplayUtils::CreatePlayer(Scene* pScene, Vec2 position)
	{
		// Truck
		Entity truckId = pScene->CreateEntity();
		TagComponent* pTagTruck = pScene->AddComponent<TagComponent>(truckId);
		pTagTruck->name = "Truck";

		TransformComponent* pTransformTruck = pScene->AddComponent<TransformComponent>(truckId);
		pTransformTruck->position = position;
		pTransformTruck->angle = 0.0f;
		pTransformTruck->scale = 1;

		SpriteComponent* pSpriteTruck = pScene->AddComponent<SpriteComponent>(truckId);
		pSpriteTruck->name = DEFAULT_SPRITE_PATH + TRUCK_SPRITE;
		pSpriteTruck->cols = 1;
		pSpriteTruck->rows = 1;
		pSpriteTruck->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSpriteTruck, pTransformTruck);

		RotationComponent* pRotationTruck = pScene->AddComponent<RotationComponent>(truckId);
		pRotationTruck->acceleration = 0.0f;
		pRotationTruck->velocity = 0.0f;

		MovementComponent* pMovementTruck = pScene->AddComponent<MovementComponent>(truckId);
		pMovementTruck->acceleration = Vec2(0.0f, 0.0f);
		pMovementTruck->velocity = Vec2(0.0f, 0.0f);

		// Player
		Entity playerId = pScene->CreateEntity();
		TagComponent* pTag = pScene->AddComponent<TagComponent>(playerId);
		pTag->name = "Player";

		ParentComponent* pParent = pScene->AddComponent<ParentComponent>(playerId);
		pParent->parentId = truckId;

		TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(playerId);
		pTransform->position = Vec2(0.0f, 0.0f);
		pTransform->angle = 0.0f;
		pTransform->scale = 1;

		SoundComponent* pSound = pScene->AddComponent<SoundComponent>(playerId);
		pSound->name = DEFAULT_AUDIO_PATH + GUNSHOT_SOUND;
		pSound->audioDuration = GUNSHOT_DURATION;
		pSound->isLoop = false;
		pSound->play = false;

		// Play once to load first time and avoid freeze on game
		App::PlaySoundW(pSound->name.c_str(), pSound->isLoop);

		PlayerComponent* pPlayer = pScene->AddComponent<PlayerComponent>(playerId);

		RigidBodyComponent* pRigidBody = pScene->AddComponent<RigidBodyComponent>(playerId);
		pRigidBody->bodyType = eBody::ACTIVE;
		pRigidBody->radius = PLAYER_RADIUS;

		SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(playerId);
		pSprite->name = DEFAULT_SPRITE_PATH + PLAYER_SPRITE;
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->speed = 1.0f;

		GraphicsUtils::SetupSprite(pSprite, pTransform);

		return playerId;
	}

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
