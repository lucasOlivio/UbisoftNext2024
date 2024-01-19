#include "pch.h"

#include "InputUtils.h"

namespace MyEngine
{
	void InputUtils::CaptureMouse(GLFWwindow* pWindow)
	{
		glfwSetInputMode(pWindow,
                         GLFW_CURSOR,
                         GLFW_CURSOR_DISABLED);
	}

	void InputUtils::ReleaseMouse(GLFWwindow* pWindow)
	{
		glfwSetInputMode(pWindow,
						 GLFW_CURSOR,
						 GLFW_CURSOR_NORMAL);
	}
}
