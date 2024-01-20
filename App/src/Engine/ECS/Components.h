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
	};

	struct RotationComponent
	{
		float velocity;
		float acceleration;
	};

	struct SpriteComponent
	{
		std::string name;
		int cols;
		int rows;
		float speed;

		// Should this be here? Components should be only data, but makes easier for systems.
		CSimpleSprite* sprite;
	};

	struct RigidBodyComponent
	{
		eBody bodyType;

		float radius;
	};
}
