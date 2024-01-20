#include "stdafx.h"

#include "CollisionsUtils.h"

namespace MyEngine
{
	bool CollisionsUtils::SphereSphere_Overlap(const float& radiusA,
											   const Vec2& centerA,
		const float& radiusB,
		const Vec2& centerB)
	{
		// Calculate squared distance between centers
		Vec2 d = centerA - centerB;
		float dist2 = d.Dot(d);
		// Spheres intersect if squared distance is less than squared sum of radii
		float radiusSum = radiusA + radiusB;
		if (dist2 > radiusSum * radiusSum)
		{
			// Not hit
			return false;
		}
		return true;
	}

	Vec2 CollisionsUtils::SphereSphere_CollisionPoint(const float& radiusA,
		const Vec2& centerA,
		const Vec2& normal,
		const float& radiusB,
		const Vec2& centerB)
	{
		// Weighted linear interpolation
		Vec2 collisionPoint = centerA + ((centerB - centerA) * radiusA / (radiusA + radiusB));

		return collisionPoint;
	}

	Vec2 CollisionsUtils::SphereSphere_Normal(Vec2 centerA, Vec2 centerB)
	{
		Vec2 distance = centerB - centerA;
		return distance.Normalize();
	}
}