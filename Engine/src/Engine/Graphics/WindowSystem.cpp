#include "pch.h"

#include "WindowSystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
    void WindowSystem::Init()
    {
        glfwSetErrorCallback(GlfwErrorCallback);
        if (!glfwInit())
        {
            LOG_ERROR("Error initializing GLFW!\n");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        // Set width and height from maximized window
        WindowComponent* pWindow = GraphicsLocator::GetWindow();

        pWindow->pGLFWWindow = glfwCreateWindow(pWindow->width,
                                                pWindow->height,
                                                pWindow->name.c_str(), NULL, NULL);
        if (!pWindow->pGLFWWindow)
        {
            LOG_ERROR("Error creating window '" + pWindow->name + "'!\n");
            glfwTerminate();
            return;
        }

        // Update width and height for maximized window
        glfwGetFramebufferSize(pWindow->pGLFWWindow, &(pWindow->width), &(pWindow->height));

        glfwMakeContextCurrent(pWindow->pGLFWWindow);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1);

        // While drawing a pixel, see if the pixel that's already there is closer or not?
        glEnable(GL_DEPTH_TEST);
        // Activate transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // set to not draw "back facing" triangles
        glCullFace(GL_BACK);
    }

    void WindowSystem::Start(Scene* pScene)
    {
    }

    void WindowSystem::Update(Scene* pScene, float deltaTime)
    {
        WindowComponent* pWindow = GraphicsLocator::GetWindow();
        iShaderProgram* pShader = ShaderManager::GetActiveShader();

        // Update window size
        glfwGetFramebufferSize(pWindow->pGLFWWindow, &(pWindow->width), &(pWindow->height));
        glViewport(0, 0, pWindow->width, pWindow->height);

        // Updating window projection uniform
        glm::mat4 matProjection = pWindow->ProjectionMat();
        pShader->SetUniformMatrix4f("matProjection", matProjection);

        // Update window title
        glfwSetWindowTitle(pWindow->pGLFWWindow, pWindow->name.c_str());
    }

    void WindowSystem::Render(Scene* pScene)
    {
    }

    void WindowSystem::End(Scene* pScene)
    {
    }

    void WindowSystem::Shutdown()
    {
        WindowComponent* pWindow = GraphicsLocator::GetWindow();
        if (pWindow->pGLFWWindow) {
            glfwDestroyWindow(pWindow->pGLFWWindow);
        }
        glfwTerminate();
    }
}
