#pragma once

#include <glm/vec3.hpp>

namespace MyEngine
{
	class CollisionsUtils
	{
	public:
		// Overlap checks
		static bool AABBAABB_Overlap(const glm::vec3& minA, const glm::vec3& maxA, 
									 const glm::vec3& minB, const glm::vec3& maxB);

		static bool AABBTriangle_Overlap(const glm::vec3& minA, const glm::vec3& maxA,
										 const glm::vec3& v1, 
										 const glm::vec3& v2, 
										 const glm::vec3& v3);

		static bool SphereAABB_Overlap(const glm::vec3& centerA, const float& radiusA,
									   const glm::vec3& minB, const glm::vec3& maxB);

		static bool SphereSphere_Overlap(const float& radiusA,
									     const glm::vec3& centerA,
									     const float& radiusB,
									     const glm::vec3& centerB);

		static bool SphereTriangle_Overlap(const float& radiusA,
									       const glm::vec3& centerA,
										   const glm::vec3& v1, 
										   const glm::vec3& v2, 
										   const glm::vec3& v3);

		// Collision point checks
		static glm::vec3 AABBAABB_CollisionPoint(const glm::vec3& minA, const glm::vec3& maxA, 
												 const glm::vec3& minB, const glm::vec3& maxB);

		static glm::vec3 SphereAABB_CollisionPoint(const glm::vec3& min, const glm::vec3& max,
												   const glm::vec3& sphereCenter,
												   const float& radius);

		static glm::vec3 SphereSphere_CollisionPoint(const float& radiusA, 
													 const glm::vec3& centerA,
													 const glm::vec3& normal, 
													 const float& radiusB,
													 const glm::vec3& centerB);
		// Collision normal checks

		// Normal in relation to sphere A
		static glm::vec3 SphereSphere_Normal(glm::vec3 centerA, glm::vec3 centerB);

		// Normal in relation to AABB
		static glm::vec3 AABB_Normal(glm::vec3 min, glm::vec3 max,
									 glm::vec3 collisionPoint);
	};
}
