#pragma once

#include "Engine/ECS/Base.h"

#include "Engine/Utils/Vector2.h"

#include <vector>

namespace MyEngine
{
	enum eBody
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

	struct sCollisionData
	{
		Entity entityA;
		Entity entityB;
		Vec2 contactPoint;
		Vec2 collisionNormalA;
		Vec2 collisionNormalB;
		Vec2 velocityAtCollisionA;
		Vec2 velocityAtCollisionB;
	};
}
