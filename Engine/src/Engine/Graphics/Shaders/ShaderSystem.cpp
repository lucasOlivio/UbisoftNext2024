#include "pch.h"

#include "ShaderSystem.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/Graphics/Shaders/ShaderManagerLocator.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
	void ShaderSystem::Init()
	{
		ConfigPathComponent* pConfigPath = CoreLocator::GetConfigPath();
		iShaderManager* pShaderManager = ShaderManagerLocator::Get();

		// Setup shaders
		pShaderManager->SetBasePath(pConfigPath->pathShaders);
		std::string shaderName = "Shader01"; // TODO: This should come from config?
		pShaderManager->AddShaderProgram(shaderName);
		pShaderManager->UseShaderProgram(shaderName);
	}

	void ShaderSystem::Start(Scene* pScene)
	{
	}

	void ShaderSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void ShaderSystem::Render(Scene* pScene)
	{
	}

	void ShaderSystem::End(Scene* pScene)
	{
	}

	void ShaderSystem::Shutdown()
	{
	}
}
