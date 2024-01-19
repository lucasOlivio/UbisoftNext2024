#include "pch.h"

#include "GraphicsUtils.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
	void GraphicsUtils::DrawModel(glm::mat4 matModel,
								  bool isWireFrame,
								  bool doNotLight,
								  bool useColorTexture,
								  int VAO_ID,
								  int numberOfIndices,
								  bool useDebugColor,
								  glm::vec4 debugColor)
	{
		iShaderProgram* pShader = ShaderManager::GetActiveShader();

		// Update model matrix on shader
		pShader->SetUniformMatrix4f("matModel", matModel);

		// Also calculate and pass the "inverse transpose" for the model matrix
		glm::mat4 matModelIT = glm::inverse(glm::transpose(matModel));
		pShader->SetUniformMatrix4f("matModel_IT", matModelIT);

		pShader->IsWireframe(isWireFrame);
		pShader->SetUniformFloat("doNotLight", doNotLight);
		pShader->SetUniformFloat("bUseColorTexture", useColorTexture);

		// Debug variables
		pShader->SetUniformFloat("bUseDebugColour", useDebugColor);
		pShader->SetUniformVec4("debugColourRGBA", debugColor);

		glBindVertexArray(VAO_ID); //  enable VAO (and everything else)
		glDrawElements(GL_TRIANGLES,
			numberOfIndices,
			GL_UNSIGNED_INT,
			0);
		glBindVertexArray(0); 			  // disable VAO (and everything else)
	}

	void GraphicsUtils::DrawDebugModel(glm::mat4 matModel, 
									   int VAO_ID, int numberOfIndices,
									   glm::vec4 debugColor)
	{
		return DrawModel(matModel, true, true, false,
						 VAO_ID, numberOfIndices,
						 true, debugColor);
	}
}
