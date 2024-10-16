﻿#include "VertexArray.h"

#include <GL/glew.h>

#include "../common/Log.h"

VertexArray::VertexArray()
{
    /*
      Creates a vartex array object

      A vao holds a reference of vertex buffer and verter pointer attribs together.
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

	const auto& elements = l.get();

    unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) 
	{
        /*
            At this moment we specify the layout of the data.
            In other words, what it is and what attributes or properties it has.
            First of all, we anable the layout for current index.
        */

        glEnableVertexAttribArray(i);

        /*
            For every the attribute index​ we set its attribute data for whatever a vertex buffer is
            currently bound to GL_ARRAY_BUFFER. 

            We make an assumption that the vertex buffer is already bound. We might do it here, but
            it looks a bit confusing.
        */

        const auto& layout = elements[i]; 

        logInfo("VertexArray::add() index = ", i, ", count = ", layout.count, ", data type = ",
            layout.dataType, ", normalize = ", layout.nomalize, ", stride = ", layout.stride,
            ", offset = ", offset);

        glVertexAttribPointer(i /* Index of the first vertex data element */,
            layout.count /* The number of elements we are using , a kind of 2d or 3d coordinates */,
            layout.dataType /* Type of the data buffer that we selected */,
            layout.nomalize /* Whether or not to normalize */,
            layout.stride /* Byte size between vertex elements, if it's 2 floats then it's 8 bytes */,
            (const void*) offset /* The offset of data in vertex buffer */);

        offset = layout.count * LayoutDefinition::getSizeOfType(layout.dataType);
	}

}
