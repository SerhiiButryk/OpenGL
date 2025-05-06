#pragma once

#include "VertexBuffer.h"
#include "Layout.h"

namespace xengine {

	/*
	This class represents Vertex Array Object in OpenGL.
	Basically VAO binds or holds together Vertex Buffer Object and its layout description.
	Layout is its Vertex Buffer Object attributes.

	VAO is responsible for holding state and information which describes the data.
	In a nutshell it answers the question of what is the data.

	Full OpenGL pipeline now looks like this:

	A vertex array object stores the following:

	- Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
	- Vertex attribute configurations via glVertexAttribPointer.
	- Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.

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
