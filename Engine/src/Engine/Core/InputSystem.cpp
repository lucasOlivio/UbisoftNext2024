#include "pch.h"

#include "InputSystem.h"

#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/InputEvent.h"
#include "Engine/Events/EventBusLocator.hpp"

namespace MyEngine
{
	void InputSystem::Init()
	{
		// TODO: Remove this coupling, this creates the need to the input system 
		// be registered after the window system
		WindowComponent* pWindow = GraphicsLocator::GetWindow();
		if (!pWindow->pGLFWWindow)
		{
			LOG_WARNING("GLFW Window not initialized, no input callbacks configured.");
			return;
		}

		glfwSetKeyCallback(pWindow->pGLFWWindow, InputSystem::KeyCallback);
		glfwSetMouseButtonCallback(pWindow->pGLFWWindow, InputSystem::MouseButtonCallback);
		glfwSetCursorPosCallback(pWindow->pGLFWWindow, InputSystem::MousePositionCallback);

		return;
	}

	void InputSystem::Start(Scene* pScene)
	{
	}

	void InputSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void InputSystem::Render(Scene* pScene)
	{
	}

	void InputSystem::End(Scene* pScene)
	{
	}

	void InputSystem::Shutdown()
	{
	}

	void InputSystem::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// Update input component to keep track of pressed keys
		KeyInputComponent* pKeyInput = CoreLocator::GetKeyInput();

		sKeyData keyData = sKeyData();
		keyData.key = (eKeyCodes)key;
		keyData.action = (eInputActions)action;
		keyData.mod = (eKeyMods)mods;
		
		if (keyData.action == eInputActions::KEY_RELEASE)
		{
			pKeyInput->key[key] = false;
		}
		else
		{
			pKeyInput->key[key] = true;
		}

		// Push keyboard event
		m_TriggerKeyEvent(keyData);

		return;
	}

	void InputSystem::MouseButtonCallback(GLFWwindow* window, int mouse, int action, int mods)
	{
		// Update input component to keep track of pressed mouse buttons
		MouseInputComponent* pMouseInput = CoreLocator::GetMouseInput();

		sMouseData mouseData = sMouseData();
		mouseData.button = (eMouseCodes)mouse;
		mouseData.action = (eInputActions)action;
		mouseData.mod = (eKeyMods)mods;

		if (mouseData.action == eInputActions::KEY_RELEASE)
		{
			pMouseInput->button[mouse] = false;
		}
		else
		{
			pMouseInput->button[mouse] = true;
		}

		// Push mouseboard event
		m_TriggerMouseEvent(mouseData);

		return;
	}

	void InputSystem::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		// Update input component to keep track of mouse position
		MouseInputComponent* pMouseInput = CoreLocator::GetMouseInput();

		pMouseInput->lastPosX = pMouseInput->posX;
		pMouseInput->lastPosY = pMouseInput->posY;

		pMouseInput->posX = (float)xpos;
		pMouseInput->posY = (float)ypos;

		return;
	}

	void InputSystem::m_TriggerKeyEvent(const sKeyData& collData)
	{
		iEventBus<eInputEvents, KeyboardEvent>* pEventBus = EventBusLocator<eInputEvents, KeyboardEvent>::Get();

		KeyboardEvent keyEvent = KeyboardEvent();
		keyEvent.keyData = collData;
		pEventBus->Publish(keyEvent);

		return;
	}

	void InputSystem::m_TriggerMouseEvent(const sMouseData& collData)
	{
		iEventBus<eInputEvents, MouseEvent>* pEventBus = EventBusLocator<eInputEvents, MouseEvent>::Get();

		MouseEvent mouseEvent = MouseEvent();
		mouseEvent.mouseData = collData;
		pEventBus->Publish(mouseEvent);

		return;
	}
}
