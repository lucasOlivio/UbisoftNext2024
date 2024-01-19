#pragma once

#include <GLFW/glfw3.h>

namespace MyEngine
{
	class InputUtils
	{
	public:
		static void CaptureMouse(GLFWwindow* pWindow);

		static void ReleaseMouse(GLFWwindow* pWindow);
	};
}
