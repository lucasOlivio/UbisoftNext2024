#pragma once

#include "Engine/Core/Shapes.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace MyEngine
{
	struct sVertex
	{
		float x, y, z, w;
		float r, g, b, a;
		float nx, ny, nz, nw;
		float u, v;
	};

	struct sMesh
	{
		~sMesh()
		{
			delete[] pIndices;
			delete[] pTriangles;
			delete[] pVertices;
		}

		glm::vec3 GetExtent()
		{
			return glm::vec3(
				maxX - minX,
				maxY - minY,
				maxZ - minZ
			);
		}

		std::string name;

		unsigned int VAO_ID;

		unsigned int vertexBufferID;
		unsigned int vertexBuffer_Start_Index;
		unsigned int numberOfVertices;

		unsigned int indexBufferID;
		unsigned int indexBuffer_Start_Index;
		unsigned int numberOfIndices;
		unsigned int numberOfTriangles;

		// The index buffer (CPU side)
		unsigned int* pIndices;
		sVertex* pVertices;
		sTriangle* pTriangles;

		// Mesh info
		float maxX, maxY, maxZ;
		float minX, minY, minZ;
	};
}
