#pragma once

#include "Base.h"

#include "Engine/Physics/PhysicsProperties.h"

#include "Engine/Utils/Vector2.h"

// Sprite component
class CSimpleSprite;

namespace MyEngine
{
	struct TagComponent
	{
		std::string name;
	};

	struct TransformComponent
	{
		Vec2 position;
		float angle;
		float scale;
	};

	struct MovementComponent
	{
		Vec2 velocity;
		Vec2 acceleration;

		float drag;

		float maxSpeed;
		float maxAcceleration;
	};

	struct RotationComponent
	{
		float velocity;
		float acceleration;

		float drag;

		float maxSpeed;
		float maxAcceleration;
	};

	struct SpriteComponent
	{
		std::string name;
		int cols;
		int rows;
		float speed;
		bool isStatic; // Static sprites can share the same CSimpleSprite since they dont need to have different animations

		// Should this be here? Components should be only data, but makes easier for systems.
		CSimpleSprite* sprite;
	};

	struct RigidBodyComponent
	{
		eBody bodyType;

		float radius;
	};

	// Gameplay components
	struct PlayerComponent
	{
		int maxHealth;
		int health;
		
		float fireRate;
		float lastFire;

		int totalAmmo;
		int currentAmmo;

		int score;
	};

	struct PointComponent
	{
		int points;
	};

	struct FollowTargetComponent
	{
		Entity entityToFollow;
	};

	struct ProjectileComponent
	{
		int damage;
	};

	struct EnemyComponent
	{
		int damage;
	};
}
