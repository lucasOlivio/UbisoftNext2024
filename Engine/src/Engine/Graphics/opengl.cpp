#include "pch.h"

namespace MyEngine
{
    void GLAPIENTRY MessageCallback(GLenum source,
                                    GLenum type,
                                    GLuint id,
                                    GLenum severity,
                                    GLsizei length,
                                    const GLchar* message,
                                    const void* userParam)
    {
        std::string error = "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n" +
            std::to_string(type) + "\n" +
            std::to_string(severity) + "\n" +
            message;

        LOG_ERROR(error);
    }
    void GlfwErrorCallback(int error, const char* description)
    {
        LOG_ERROR(description);
    }
}
