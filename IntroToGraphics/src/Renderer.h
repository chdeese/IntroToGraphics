#pragma once

#include <GL/glew.h>

void GLFWErrorCallback(int error, const char* description);
void GLDebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
    );
