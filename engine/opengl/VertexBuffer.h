#pragma once

#include <cstdint>
#include <cstddef>

/*
	This class is a representation of vertex buffer in OpenGL.
	
	A vertex buffer is just a buffer with raw bytes which
	contains data related to positions or other things on the screen.
*/

namespace xengine {

class VertexBuffer
{
public:
	
	VertexBuffer();

	void bind() const;
	void unbind() const;

	void fill(float* arr, size_t size /* Buffer size in bytes */) const;

private:
	uint32_t m_RenderId {};
};

}