#pragma once

#include "pch.h"

namespace MyEngine
{
	enum eShape
	{
		UNKNOWN_OR_UNDEFINED,
		SPHERE,
		PLANE,
		TRIANGLE,
		AABB,
		CAPSULE,
		MESH_OF_TRIANGLES,
		OBB,
		AABB2D
	};

	struct sSphere
	{
		sSphere(float radius)
		{
			this->radius = radius;
		}
		sSphere()
		{
			this->radius = 0.0f;
		}

		float radius = 0.0f;
	};

	struct sPlane
	{
		sPlane(glm::vec3 normal)
		{
			this->normalToSurface = normal;
		}
		sPlane()
		{
			this->normalToSurface = glm::vec3(0.0f);
		}

		glm::vec3 normalToSurface;
	};

	struct sTriangle
	{
		static const unsigned int NUMBER_OF_VERTICES = 3;

		glm::vec3 normal = glm::vec3(0.0f);
		glm::vec3 vertices[NUMBER_OF_VERTICES];

		sTriangle()
		{
			this->vertices[0] = glm::vec3(0.0f);
			this->vertices[1] = glm::vec3(0.0f);
			this->vertices[2] = glm::vec3(0.0f);
		}
		sTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
		{
			this->vertices[0] = v0;
			this->vertices[1] = v1;
			this->vertices[2] = v2;
			this->calcNormal();
		}
		sTriangle(glm::vec3 vertices[NUMBER_OF_VERTICES])
		{
			this->vertices[0] = vertices[0];
			this->vertices[1] = vertices[1];
			this->vertices[2] = vertices[2];
			this->calcNormal();
		}

		void calcNormal(void)
		{
			glm::vec3 v0_1 = this->vertices[1] - this->vertices[0];
			glm::vec3 v0_2 = this->vertices[2] - this->vertices[1];
			this->normal = glm::normalize(glm::cross(v0_1, v0_2));
			return;
		}

		glm::vec3 getCentre(void)
		{
			return ((this->vertices[0] + this->vertices[1] + this->vertices[2]) / (float)NUMBER_OF_VERTICES);
		}
	};

	struct sAABB
	{
		sAABB(glm::vec3 minXYZ, glm::vec3 maxXYZ, glm::vec3 offset)
		{
			this->minXYZ = minXYZ + offset;
			this->maxXYZ = maxXYZ + offset;
		}
		sAABB()
		{
			this->minXYZ = glm::vec3(0.0f);
			this->maxXYZ = glm::vec3(0.0f);
		}

		glm::vec3 Center(void) 
		{
			return (minXYZ + maxXYZ) * 0.5f;
		}

		glm::vec3 Extent(void)
		{
			return maxXYZ - minXYZ;
		}

		glm::vec3 minXYZ = glm::vec3(0.0f);
		glm::vec3 maxXYZ = glm::vec3(0.0f);
	};

	struct sAABB2D
	{
		sAABB2D(glm::vec2 minXY, glm::vec2 maxXY, glm::vec2 offset)
		{
			this->minXY = minXY + offset;
			this->maxXY = maxXY + offset;
			this->offset = offset;
		}
		sAABB2D()
		{
			this->minXY = glm::vec2(0.0f);
			this->maxXY = glm::vec2(0.0f);
			this->offset = glm::vec2(0.0f);
		}

		glm::vec2 minXY = glm::vec2(0.0f);
		glm::vec2 maxXY = glm::vec2(0.0f);
		glm::vec2 offset = glm::vec2(0.0f);
	};

	struct sOBB {
		sOBB(glm::vec3 center, glm::mat4 matRotation, glm::vec3 maxXYZ)
		{
			this->center = glm::vec3(0.0f);
			this->maxXYZ = glm::vec3(0.0f);
		}

		sOBB()
		{
			this->center = glm::vec3(0.0f);
			this->maxXYZ = glm::vec3(0.0f);
		}

		glm::vec3 center;
		glm::vec3 maxXYZ;      // Positive halfwidth extents of OBB along each axis
	};

	struct sCapsule
	{
		sCapsule(float halfLength, float radius)
		{
			this->halfLength = halfLength;
			this->radius = radius;
		}
		sCapsule()
		{
			this->halfLength = 0;
			this->radius = 0;
		}

		float halfLength;
		float radius;
	};
}