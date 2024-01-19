#include "pch.h"

#include "CollisionsUtils.h"
#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/Math.h"
#include <glm/mat4x4.hpp>

namespace MyEngine
{
	bool CollisionsUtils::AABBAABB_Overlap(const glm::vec3& minA, const glm::vec3& maxA,
										   const glm::vec3& minB, const glm::vec3& maxB)
	{
		// Check if objects collide
		if (maxB[0] < minB[0])
		{
			return false;
		}

		if (minA[0] > maxB[0])
		{
			return false;
		}

		if (maxB[1] < minB[1])
		{
			return false;
		}

		if (minA[1] > maxB[1])
		{
			return false;
		}

		if (maxB[2] < minB[2])
		{
			return false;
		}

		if (minA[2] > maxB[2])
		{
			return false;
		}

		return true;
	}

	bool CollisionsUtils::AABBTriangle_Overlap(const glm::vec3& minA, const glm::vec3& maxA,
											   const glm::vec3& v1, 
											   const glm::vec3& v2, 
											   const glm::vec3& v3)
	{
		LOG_WARNING("CollisionsUtils::AABBTriangle_Overlap Not implemented yet");
		return false;
	}

	bool CollisionsUtils::SphereAABB_Overlap(const glm::vec3& centerA, const float& radiusA,
											 const glm::vec3& minB, const glm::vec3& maxB)
	{
		// Calculate the closest point on the AABB to the sphere center
		glm::vec3 closestPoint = glm::clamp(centerA, glm::vec3(minB), glm::vec3(maxB));

		// Calculate the distance between the sphere center and the closest point on the AABB
		glm::vec3 offset = centerA - closestPoint;
		float distance = glm::length(offset);

		// Check if the distance is less than the sphere radius
		if (distance > radiusA)
		{
			// Not hit
			return false;
		}
		return true;
	}

	bool CollisionsUtils::SphereSphere_Overlap(const float& radiusA,
											   const glm::vec3& centerA,
											   const float& radiusB,
											   const glm::vec3& centerB)
	{
		// Calculate squared distance between centers
		glm::vec3 d = centerA - centerB;
		float dist2 = glm::dot(d, d);
		// Spheres intersect if squared distance is less than squared sum of radii
		float radiusSum = radiusA + radiusB;
		if (dist2 > radiusSum * radiusSum)
		{
			// Not hit
			return false;
		}
		return true;
	}

	bool CollisionsUtils::SphereTriangle_Overlap(const float& radiusA,
												 const glm::vec3& centerA,
												 const glm::vec3& v1,
												 const glm::vec3& v2,
												 const glm::vec3& v3)
	{
		// Getting closest point in triangle
		glm::vec3 closestPoint = ClosestPtPointTriangle(centerA, v1, v2, v3);

		// Is this close enought to the sphere
		float distanceToThisTriangle = glm::distance(closestPoint, centerA);
		if (distanceToThisTriangle > radiusA)
		{
			return false;
		}

		return true;
	}

	glm::vec3 CollisionsUtils::AABBAABB_CollisionPoint(const glm::vec3& minA, const glm::vec3& maxA, 
													   const glm::vec3& minB, const glm::vec3& maxB)
	{
		// Get the intersection plane
		glm::vec3 intMin = glm::max(minA, maxA);
		glm::vec3 intMax = glm::min(minB, maxB);

		// Calculate the center of the intersection AABB as the collision point
		glm::vec3 collisionPoint = 0.5f * (intMin + intMax);
		return collisionPoint;
	}

	glm::vec3 CollisionsUtils::SphereAABB_CollisionPoint(const glm::vec3& min, const glm::vec3& max,
														 const glm::vec3& sphereCenter,
														 const float& radius)
	{
		// Calculate the closest point on the AABB to the sphere center
		glm::vec3 closestPoint = glm::clamp(sphereCenter, glm::vec3(min), glm::vec3(max));

		// Calculate the distance between the sphere center and the closest point on the AABB
		glm::vec3 offset = sphereCenter - closestPoint;
		float distance = glm::length(offset);

		glm::vec3 collisionPoint = sphereCenter + (offset / distance) * radius;
		return collisionPoint;
	}

	glm::vec3 CollisionsUtils::SphereSphere_CollisionPoint(const float& radiusA, 
														   const glm::vec3& centerA,
														   const glm::vec3& normal, 
														   const float& radiusB,
														   const glm::vec3& centerB)
	{
		// Weighted linear interpolation
		glm::vec3 collisionPoint = centerA + ((centerB - centerA) * radiusA / (radiusA + radiusB));

		return collisionPoint;
	}

	glm::vec3 CollisionsUtils::SphereSphere_Normal(glm::vec3 centerA, glm::vec3 centerB)
	{
		return glm::normalize(centerB - centerA);
	}

	glm::vec3 CollisionsUtils::AABB_Normal(glm::vec3 min, glm::vec3 max,
										   glm::vec3 collisionPoint)
	{
		glm::vec3 normal = glm::vec3(0.0f);

		// Determine the collision side by calculating the minimum overlap in each direction
		float xOverlap = glm::min(max.x, collisionPoint.x) - glm::max(min.x, collisionPoint.x);
		float yOverlap = glm::min(max.y, collisionPoint.y) - glm::max(min.y, collisionPoint.y);
		float zOverlap = glm::min(max.z, collisionPoint.z) - glm::max(min.z, collisionPoint.z);

		// Determine the normal direction based on the collision side
		if (xOverlap < yOverlap && xOverlap < zOverlap) {
			// Horizontal collision
			if (max.x < collisionPoint.x) {
				normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			}
			else {
				normal = glm::vec3(1.0f, 0.0f, 0.0f);
			}
		}
		else if (yOverlap < xOverlap && yOverlap < zOverlap) {
			// Vertical collision
			if (max.y < collisionPoint.y) {
				normal = glm::vec3(0.0f, -1.0f, 0.0f);
			}
			else {
				normal = glm::vec3(0.0f, 1.0f, 0.0f);
			}
		}
		else {
			// Depth collision (Z-axis)
			if (max.z < collisionPoint.z) {
				normal = glm::vec3(0.0f, 0.0f, -1.0f);
			}
			else {
				normal = glm::vec3(0.0f, 0.0f, 1.0f);
			}
		}

		return normal;
	}
}