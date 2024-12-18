#pragma once

#include <vector>
#include <stdexcept>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:   return 4;
		case GL_UNSIGNED_BYTE:  return 1;
		}
		std::runtime_error;
		return 0;
	}

};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() : m_stride(0) {}



	//push() functions push values and data about those values into a layout for our vertex buffer
	//if no type is passed in, debug break.
	template<typename T>
	void push(unsigned int count)
	{
		__debugbreak();
	}
	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += VertexBufferElement::getTypeSize(GL_FLOAT) * count;
	}
	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::getTypeSize(GL_UNSIGNED_INT) * count;
	}
	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
	//amount of bits between vertexes in our vertex buffer.
	inline unsigned int getStride() const { return m_stride; }
};

