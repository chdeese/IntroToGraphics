#include "Renderer.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>
#include <GLFW/glfw3.h>

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

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();

    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
