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

		// Any static entities collisions
		std::set<Entity> vecStaticEntities;

		// Any non-static entities collisions
		std::set<Entity> vecNonStaticEntities;

		size_t Total()
		{
			return vecStaticEntities.size() + 
				   vecNonStaticEntities.size();
		}
	};
}
