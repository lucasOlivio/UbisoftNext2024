#pragma once

#include <glm/mat4x4.hpp>

namespace MyEngine
{
	class GraphicsUtils
	{
	public:
		// Sets all needed uniforms and draw model using VAO and opengl
		static void DrawModel(glm::mat4 matModel,
							  bool isWireFrame,
							  bool doNotLight,
							  bool useColorTexture,
							  int VAO_ID,
							  int numberOfIndices,
							  bool useDebugColor = false,
							  glm::vec4 debugColor = glm::vec4(0));
		static void DrawDebugModel(glm::mat4 matModel,
							  int VAO_ID,
							  int numberOfIndices,
							  glm::vec4 debugColor);
	};
}
