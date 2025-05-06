#include "VertexBuffer.h"

/* Glew provides OpenGL APIs */
#include <GL/glew.h>

namespace xengine {

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

    void VertexBuffer::createAndInitialize(float* arr, size_t size, bool isDynamic)
    {
        // Bind our buffer
        bind();

        m_IsDynamic =  isDynamic;

        /* Fill a vertex buffer with data */

        const int hint = isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;

        // Creates and initializes a buffer object's data store on GPU
        glBufferData(
            GL_ARRAY_BUFFER /* Buffer type */,
            size /* Buffer size */,
            arr, /* Actually data */
            hint /* A hint for GPU */
        );
    }

    void VertexBuffer::update(float* arr, size_t size /* Buffer size in bytes */) const {

        // Bind our buffer
        bind();

        glBufferSubData(GL_ARRAY_BUFFER,
            0 /* Offset of memory which we want to start at */,
            size /* Size which we want to access*/,
            arr /* Data which we want to write*/);
    }

    void VertexBuffer::deleteBuffer() {

        // Bind our buffer
        bind();

        // Delete buffer on GPU so memory can be reused
        glDeleteBuffers(1 , &m_RenderId);
    }
}
