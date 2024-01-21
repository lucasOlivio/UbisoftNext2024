#pragma once

#include "Engine/ECS/Base.h"

#include "Engine/Utils/Vector2.h"

#include <vector>

namespace MyEngine
{
	/*
	The idea of the body is been static or dynamic so we don't need to recalculate the grid for the static,
	but since we have much more dynamics makes more sense to separate between things we should check (ALLIE) and things
	that we only need to check against (ENEMY).

	enum eBody
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};*/
	enum eBody
	{
		ALLY,
		ENEMY
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
