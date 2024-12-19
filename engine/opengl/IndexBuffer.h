#pragma once

#include <cstdint>
#include <cstddef>

namespace xengine {

	/*
		This class is a representation of index buffer in OpenGL.

		An index buffer is a buffer which holds indices of data from a vertex buffer.
		An index buffer allows to reuse data without duplication.
	*/

	class IndexBuffer
	{
	public:

		IndexBuffer();

		void bind() const;
		void unbind() const;

		void fill(uint32_t* arr, size_t size /* Buffer size in bytes */);

		inline uint32_t getRenderId() const;
		inline uint32_t getCount() const { return m_IndexCount; }

	private:
		uint32_t m_RenderId {};
		uint32_t m_IndexCount {};
	};

}

