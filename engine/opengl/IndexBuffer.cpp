#include "IndexBuffer.h"

/* Glew provides OpenGL APIs */
#include <GL/glew.h>

namespace xengine {

	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1 /* Create 1 buffer */, &m_RenderId /* Name of the array where generated buffer is stored */);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1 , &m_RenderId);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER /* Buffer type */, m_RenderId /* Buffer name */);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER /* Buffer type */, 0);
	}

	void IndexBuffer::fill(uint32_t* arr, size_t size)
	{
		m_IndexCount = size;

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t) /* Buffer size in bytes */,
			arr /* Actually data */, GL_STATIC_DRAW /* A hint for GPU see docs for details */);
	}

}
