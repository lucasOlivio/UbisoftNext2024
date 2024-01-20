#pragma once

#include "Engine/Utils/Vector2.h"

namespace MyEngine
{
	class CollisionsUtils
	{
	public:
		// Overlap checks
		static bool SphereSphere_Overlap(const float& radiusA,
									     const Vec2& centerA,
									     const float& radiusB,
									     const Vec2& centerB);

		// Collision point checks
		static Vec2 SphereSphere_CollisionPoint(const float& radiusA, 
													 const Vec2& centerA,
													 const Vec2& normal, 
													 const float& radiusB,
													 const Vec2& centerB);
		// Collision normal checks

		// Normal in relation to sphere A
		static Vec2 SphereSphere_Normal(Vec2 centerA, Vec2 centerB);
	};
}
