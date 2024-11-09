#pragma once

#include <vector>

#include <GL/glew.h>

/*
 * Represent a layout specification of vertex buffer.
 * Basically layout is some information about the data in vertex buffer
 */

struct LayoutDefinition
{
	/* The number of elements we are using, a kind of 2d or 3d coordinates */
	int count;
	/* Type of the data buffer that we selected */
	int dataType;
	/* Normalize */
	unsigned int nomalize;

	/* Maps the type to size */
	static int getSizeOfType(unsigned int type) {
		
		switch (type)
		{
		case GL_FLOAT: return 4;

		default:
			break;
		}

		return 0;
	}
};

/* This class holds an array of layout specification in OpenGL */

class BufferLayout
{
public:

	BufferLayout();

	void add(const LayoutDefinition& element);

	inline const std::vector<LayoutDefinition>& get() const;
	inline const uint32_t getStride() const { return m_Stride; }

private:
	std::vector<LayoutDefinition> elements;
	uint32_t m_Stride {};

};

inline const std::vector<LayoutDefinition>& BufferLayout::get() const
{
	return elements;
}

