#include "vertexbuffer_layout.h"

template <>
void VertexBufferLayout::push<float>(unsigned int count)
{
    elements.push_back({ GL_FLOAT, count, GL_FALSE });
    stride += VertexBufferElement::get_size_of_type(GL_FLOAT) * count;
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT) * count;
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE) * count;
}