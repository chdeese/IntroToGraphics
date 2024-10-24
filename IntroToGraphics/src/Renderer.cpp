#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <iostream>

void GLFWErrorCallback(int error, const char* description)
{
    std::cerr << description << "\n";
}

void GLDebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
)
{
    std::cout << "[OpenGL] " << message << "\n";

    if (severity > GL_DEBUG_SEVERITY_MEDIUM)
        __debugbreak();
}
