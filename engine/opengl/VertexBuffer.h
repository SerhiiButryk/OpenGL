#pragma once

#include <cstdint>
#include <cstddef>

/*
	This class is a representation of vertex buffer object in OpenGL.
	
	A vertex buffer object is just a raw buffer with raw bytes that
	contains all data related to the vertices.
*/

namespace xengine {

	class VertexBuffer
	{
	public:

		VertexBuffer();
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		void fill(float* arr, size_t size /* Buffer size in bytes */, bool isDynamic = false);

		// Update a buffer dynamically
		void update(float* arr, size_t size /* Buffer size in bytes */) const;

		bool isDynamic() const {
			return m_IsDynamic;
		}

#ifdef UNIT_TESTS
		auto getRenderId() const { return m_RenderId; }
#endif

	private:
		uint32_t m_RenderId {};
		bool m_IsDynamic = false;
	};

}