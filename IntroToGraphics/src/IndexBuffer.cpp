#include "IndexBuffer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Renderer.h"

//generates a new buffer and assigns 
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{
    //breaks if unsigned int size changes
    if (sizeof(unsigned int) != sizeof(GLuint))
        __debugbreak();

    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}
//deletes the OpenGL index buffer
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

//attaches an element array buffer to the renderer program
void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

//detaches our element array
void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
