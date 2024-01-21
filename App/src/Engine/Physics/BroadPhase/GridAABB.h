#pragma once

#include "Engine/Core/Types.h"

#include "Engine/ECS/Base.h"

#include "Engine/Utils/Vector2.h"

#include <set>

namespace MyEngine
{
	// Contains all entities that are inside its area
	struct GridAABB
	{
		Vec2 minXY;
		Vec2 maxXY;

		// Entities to check
		std::set<Entity> vecActiveEntities;

		// Entities to be checked against
		std::set<Entity> vecPassiveEntities;

		size_t Total()
		{
			return vecActiveEntities.size() +
				   vecPassiveEntities.size();
		}
	};
}
