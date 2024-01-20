#pragma once

#include "Engine/Core/types.h"

#include "Engine/Utils/Vector2.h"

namespace MyEngine
{
	class GridUtils
	{
	public:
		// Calculate in which AABB index this points is
		static uint LocatePoint(Vec2 point, Vec2 extent);

		// Calculate the position where this index is located
		static Vec2 LocatePosition(uint theIndex, Vec2 extent);
	};
}
