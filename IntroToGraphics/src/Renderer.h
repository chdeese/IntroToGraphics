#pragma once

#include <GL/glew.h>

class VertexArray;
class IndexBuffer;
class Shader;

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

class Renderer
{
public:
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void clear() const;
};
