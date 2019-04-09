#pragma once

#include "vertexbuffer.h"
#include "vertexbuffer_layout.h"

class VertexArray
{
private:
	unsigned int renderer_id;
public:
	VertexArray();
	~VertexArray();

	void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
};