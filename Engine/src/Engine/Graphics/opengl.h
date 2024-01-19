#pragma once

#include "Engine/Utils/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MyEngine
{
    void GLAPIENTRY MessageCallback(GLenum source,
                                    GLenum type,
                                    GLuint id,
                                    GLenum severity,
                                    GLsizei length,
                                    const GLchar* message,
                                    const void* userParam);

    void GlfwErrorCallback(int error, const char* description);
}
