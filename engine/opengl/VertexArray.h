#pragma once

#include "VertexBuffer.h"
#include "Layout.h"

namespace xengine {

/*
	This class represents Vertex Array Object in OpenGL.
	Basically VAO binds or holds together Vertex Buffer and its layout definition.
*/

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void add(const VertexBuffer& vb, const BufferLayout& l);

private:
	uint32_t m_RenderId {};

};

}
