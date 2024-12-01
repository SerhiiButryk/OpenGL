#include "VertexArray.h"

#include <GL/glew.h>

#include "../common/Log.h"

namespace xengine {

    VertexArray::VertexArray()
    {
        /*
          Creates a vertex array object

          A vao holds a reference of vertex buffer and vertex pointer attribs together.
          By changing it we can change vertex buffer and therefore draw a different shape.
        */
        glGenVertexArrays(1 /* The number of vertex array object names */, &m_RenderId /* Buffer id */);
    }

    VertexArray::~VertexArray()
    {
        // TODO: Check if we need to delete it
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(m_RenderId /* Buffer id */);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::add(const VertexBuffer& vb, const BufferLayout& l)
    {
        vb.bind();

	    const auto& elements = l.get();

        unsigned int offset = 0;

	    for (unsigned int i = 0; i < elements.size(); i++)
	    {
            /*
                At this moment we specify the layout of the data.
                In other words, what it is and what attributes or properties it has.
                First of all, we enable the layout for current index.
            */

            glEnableVertexAttribArray(i);

            /*
                For every attribute index we set its attribute data for whatever a vertex buffer is
                currently bound to GL_ARRAY_BUFFER.

                We make an assumption that the vertex buffer is already bound. We might do it here, but
                it looks a bit confusing.
            */

            const auto& layout = elements[i];

	        auto stride = l.getStride();

	        logInfo("VertexArray::add() index = '{}', count = '{}' data type = '{}'"
                ", normalize = '{}', stride = '{}', offset = '{}'", i, layout.count,
                layout.dataType, layout.nomalize, stride, offset);

            glVertexAttribPointer(i /* Index of the first vertex data element */,
                layout.count /* The number of elements we are using , a kind of 2d or 3d coordinates */,
                layout.dataType /* Type of the data buffer that we selected */,
                layout.nomalize /* Whether to normalize */,
                stride /* Byte size between vertex elements, if it's 2 floats then it's 8 bytes */,
                reinterpret_cast<const void *>(offset /* The offset of data in vertex buffer */));

            offset += layout.count * LayoutDefinition::getSizeOfType(layout.dataType);
	    }

    }

}
