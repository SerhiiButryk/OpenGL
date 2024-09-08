#pragma once

#include <cstdint>

/*
	This class is a representation of index buffer in OpenGL.
	
	A index buffer is a buffer which holds indices of data from a vertex buffer.
	A index buffer allows to reuse data without dublicating it.
*/

class IndexBuffer
{
public:
	
	IndexBuffer();

	void bind() const;
	void unbind() const;

	void fill(uint32_t* arr, size_t size /* Buffer size in bytes */) const;

	uint32_t getRenderId() const;

private:
	uint32_t m_RenderId;
};

