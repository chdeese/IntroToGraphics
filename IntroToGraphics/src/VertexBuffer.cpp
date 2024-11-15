#include "VertexBuffer.h"
#include "Renderer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"


//generates and creates new arrays for an OpenGL array buffer (vertex buffer)
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
//Deletes buffers associated with the renderer we reference
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

//attaches our array buffer to the renderer
void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

//sets the renderer's referenced array buffer to null
void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
