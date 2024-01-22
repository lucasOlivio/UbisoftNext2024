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
		// Write only fields
		Vec2 position;
		float angle;
		float scale;

		// Read only fields, parent system keeps updated
		Vec2 worldPosition;
		float worldAngle;
		float worldScale;
	};

	struct ParentComponent
	{
		Entity parentId;
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

	struct SoundComponent
	{
		std::string name;

		float audioDuration;   // In seconds
		float currentProgress; // In seconds
		bool isPlaying;
		bool isLoop;

		bool play; // To play audio just set this to true
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

		int maxAmmo;
		int currentAmmo;

		int score;
	};

	struct ItemComponent
	{
		bool refilHealth;
		bool refilAmmo;
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
