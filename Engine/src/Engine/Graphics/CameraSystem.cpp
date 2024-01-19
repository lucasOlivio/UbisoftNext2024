#include "pch.h"

#include "CameraSystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
    void CameraSystem::Init()
    {
    }

    void CameraSystem::Start(Scene* pScene)
    {
    }

    void CameraSystem::Update(Scene* pScene, float deltaTime)
    {
        // Updating camera view
        CameraComponent* pCamera = GraphicsLocator::GetCamera();
        iShaderProgram* pShader = ShaderManager::GetActiveShader();

        glm::mat4 matView = pCamera->ViewMat();
        pShader->SetUniformMatrix4f("matView", matView);
    }

    void CameraSystem::Render(Scene* pScene)
    {
    }

    void CameraSystem::End(Scene* pScene)
    {
    }

    void CameraSystem::Shutdown()
    {
    }
}
