#include "VertexBuffer.h"
#include "GLFW/glfw3.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int count)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);

}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
