#pragma once

#include "Engine/Core/Types.h"

#include "Engine/ECS/Base.h"

#include "Engine/Utils/Vector2.h"

#include <set>

namespace MyEngine
{
	// Contains all triangles index (for mesh colliders) and entities inside its area
	struct GridAABB
	{
		Vec2 minXY;
		Vec2 maxXY;

		// Entities to check
		std::set<Entity> vecAllyEntities;

		// Entities to be checked against
		std::set<Entity> vecEnemyEntities;

		size_t Total()
		{
			return vecAllyEntities.size() +
				   vecEnemyEntities.size();
		}
	};
}
