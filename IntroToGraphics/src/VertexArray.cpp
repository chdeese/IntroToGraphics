#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Renderer.h"

//generates a new OpenGL vertex array
VertexArray::VertexArray()
{	
	glGenVertexArrays(1, &m_rendererID);
}
//delete our vertex array
VertexArray::~VertexArray()
{	
	glDeleteVertexArrays(1, &m_rendererID);
}
//adds a buffer to our vertex array
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	//loops through our layout elements
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		//enables and assigns vertex attributes to a pointer
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getTypeSize(element.type);
	}
}

//binds our vertex array to the renderer program
void VertexArray::bind() const
{
	glBindVertexArray(m_rendererID);
}
//sets our binded render program vertex array to null
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
