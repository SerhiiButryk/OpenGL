#pragma once

#include <vector>

#include <GL/glew.h>

/* Represent a layout specification of vertex buffer */

struct LayoutDefinition
{
	/* The number of elements we are using, a kind of 2d coordinates */
	int count;
	/* Type of the data buffer that we selected */
	int dataType;
	/* Normalize */
	unsigned int nomalize;
	/* Byte size between vertex elements, if it's 2 floats then it's 8 bytes */
	unsigned int stride;

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

	const std::vector<LayoutDefinition>& get() const;

private:
	std::vector<LayoutDefinition> elements;

};

inline const std::vector<LayoutDefinition>& BufferLayout::get() const
{
	return elements;
}

