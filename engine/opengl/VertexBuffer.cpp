#include "VertexBuffer.h"

/* Glew provides OpenGL APIs */
#include <GL/glew.h>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1 /* Generate 1 buffer */, &m_RenderId /* Name of the array where generated buffer is stored */);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER /* Buffer type */, m_RenderId /* Buffer name */);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER /* Buffer type */, 0);
}

void VertexBuffer::fill(float* arr, size_t size) const
{
    /* Fill a vertex buffer with data */

    glBufferData(
        GL_ARRAY_BUFFER /* Buffer type */,
        size /* Buffer size */,
        arr, /* Actuall data */
        GL_STATIC_DRAW /* A hint for GPU see docs for details */
    );
}
