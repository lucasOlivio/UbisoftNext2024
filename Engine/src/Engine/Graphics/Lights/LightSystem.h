#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/ECS/Components.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
	class LightSystem : public iSystem
	{
	public:
		LightSystem() = default;
		virtual ~LightSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene) {};

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		// Setup the UL locations and all light configurations
		void m_SetupLight(TransformComponent* pTransform, LightComponent* pLight, int lightIndex);

		void m_UpdatePositionUL(TransformComponent* pTransform, 
								LightComponent* pLight, 
								iShaderProgram* pShader);
		void m_UpdateDirectionUL(LightComponent* pLight, iShaderProgram* pShader);
		void m_UpdateDiffuseUL(LightComponent* pLight, iShaderProgram* pShader);
		void m_UpdateSpecularUL(LightComponent* pLight, iShaderProgram* pShader);
		void m_UpdateAttenUL(LightComponent* pLight, iShaderProgram* pShader);
		void m_UpdateParamsUL(LightComponent* pLight, iShaderProgram* pShader);
		void m_UpdateStatusUL(LightComponent* pLight, iShaderProgram* pShader);
	};
}
