#include "pch.h"

#include "FlyingCameraSystem.h"

#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

#include "Engine/Core/InputProperties.h"

#include "Engine/Utils/InputUtils.h"
#include "Engine/Utils/TransformUtils.h"

#define DEFAULT_MOUSE_SENSITIVITY 0.001f
#define DEFAULT_CAMERA_SPEED 150.0f

namespace MyEngine
{
    void FlyingCameraSystem::Init()
    {
    }

    void FlyingCameraSystem::Start(Scene* pScene)
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        pMouse->sensitivity = DEFAULT_MOUSE_SENSITIVITY;
    }

    void FlyingCameraSystem::Update(Scene* pScene, float deltaTime)
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();

        if (pMouse->button[eMouseCodes::MOUSE_BUTTON_1])
        {
            m_InitiateMouseCapture();

            // Update camera transform
            m_UpdateCameraRotation();
            m_UpdateCameraPosition(deltaTime);
        }
        else
        {
            m_StopMouseCapture();
        }
    }

    void FlyingCameraSystem::Render(Scene* pScene)
    {
    }

    void FlyingCameraSystem::End(Scene* pScene)
    {
    }

    void FlyingCameraSystem::Shutdown()
    {
    }

    void FlyingCameraSystem::m_InitiateMouseCapture()
    {
        // Set initial mouse position to consider mouse on center of window
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        if (pMouse->mouseCaptured)
        {
            return;
        }

        WindowComponent* pWindow = GraphicsLocator::GetWindow();

        pMouse->lastPosX = pMouse->posX;
        pMouse->lastPosY = pMouse->posY;

        InputUtils::CaptureMouse(pWindow->pGLFWWindow);
        pMouse->mouseCaptured = true;

        return;
    }

    void FlyingCameraSystem::m_StopMouseCapture()
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        if (!pMouse->mouseCaptured)
        {
            return;
        }
        WindowComponent* pWindow = GraphicsLocator::GetWindow();

        InputUtils::ReleaseMouse(pWindow->pGLFWWindow);
        pMouse->mouseCaptured = false;

        return;
    }

    void FlyingCameraSystem::m_UpdateCameraRotation()
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        CameraComponent* pCamera = GraphicsLocator::GetCamera();

        float xoffset = (pMouse->posX - pMouse->lastPosX) * pMouse->sensitivity;
        float yoffset = (pMouse->posY - pMouse->lastPosY) * pMouse->sensitivity;

        glm::vec3 cameraRight = glm::normalize(TransformUtils::GetRightVector(pCamera->orientation));

        // Create quaternions for pitch and yaw
        glm::quat pitchQuat = glm::angleAxis(-yoffset, cameraRight);
        glm::quat yawQuat = glm::angleAxis(-xoffset, glm::vec3(0.0f, 1.0f, 0.0f));

        // Combine pitch and yaw quaternions
        glm::quat orientationChange = yawQuat * pitchQuat;

        // Apply the combined quaternion to the camera's orientation
        pCamera->orientation = glm::normalize(orientationChange * pCamera->orientation);

        pMouse->lastPosX = pMouse->posX;
        pMouse->lastPosY = pMouse->posY;
    }

    void FlyingCameraSystem::m_UpdateCameraPosition(float deltaTime)
    {
        CameraComponent* pCamera = GraphicsLocator::GetCamera();
        KeyInputComponent* pKey = CoreLocator::GetKeyInput();

        glm::vec3 cameraPosition = pCamera->position;
        glm::vec3 cameraRotation = TransformUtils::GetQuatAsDegrees(pCamera->orientation);

        glm::vec3 cameraFront = glm::normalize(TransformUtils::GetForwardVector(pCamera->orientation));
        glm::vec3 cameraSides = glm::normalize(glm::cross(cameraFront, glm::vec3(UP_VECTOR)));
        glm::vec3 cameraUp = glm::normalize(TransformUtils::GetUpVector(pCamera->orientation));

        glm::vec3 moveOffset = glm::vec3(0.0f);

        // Handle key presses for movement
        if (pKey->key[eKeyCodes::W]) 
        {
            moveOffset = DEFAULT_CAMERA_SPEED * cameraFront * (float)deltaTime;
        }
        if (pKey->key[eKeyCodes::S]) 
        {
            moveOffset = -(DEFAULT_CAMERA_SPEED * cameraFront * (float)deltaTime);
        }
        if (pKey->key[eKeyCodes::A])
        {
            moveOffset = -(DEFAULT_CAMERA_SPEED * cameraSides * (float)deltaTime);
        }
        if (pKey->key[eKeyCodes::D])
        {
            moveOffset = DEFAULT_CAMERA_SPEED * cameraSides * (float)deltaTime;
        }
        if (pKey->key[eKeyCodes::Q])
        {
            moveOffset = -(DEFAULT_CAMERA_SPEED * cameraUp * (float)deltaTime);
        }
        if (pKey->key[eKeyCodes::E])
        {
            moveOffset = DEFAULT_CAMERA_SPEED * cameraUp * (float)deltaTime;
        }

        cameraPosition += moveOffset;

        pCamera->position = cameraPosition;
    }
}
