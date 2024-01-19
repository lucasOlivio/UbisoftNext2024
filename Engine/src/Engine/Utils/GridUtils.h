#pragma once

#include "Engine/Core/types.h"
#include <glm/vec3.hpp>

namespace MyEngine
{
	class GridUtils
	{
	public:
		// Calculate in which AABB index this points is
		static uint LocatePoint(glm::vec3 point, glm::vec3 extent);

		// Calculate the position where this index is located
		static glm::vec3 LocatePosition(uint theIndex, glm::vec3 extent);
	};
}
