#pragma once

#include "Engine/Core/types.h"
#include "Engine/ECS/Base.h"
#include "Engine/Core/Shapes.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <math.h>
#include <set>

namespace MyEngine
{
	// Contains all triangles index (for mesh colliders) and entities inside its area
	struct GridAABB : public sAABB
	{
		// Any static entities collisions
		std::set<Entity> vecStaticEntities;

		// Any non-static entities collisions
		std::set<Entity> vecNonStaticEntities;

		// Collision type: Mesh collider
		// Index to mesh triangles inside this AABB
		std::set<sTriangle*> vecTriangles;

		size_t Total()
		{
			return vecStaticEntities.size() + 
				   vecNonStaticEntities.size() + 
				   vecTriangles.size();
		}
	};
}
