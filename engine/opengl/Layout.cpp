#include "Layout.h"

BufferLayout::BufferLayout()
{

}

void BufferLayout::add(const LayoutDefinition& element)
{
	elements.push_back(element);
	// TODO: Improve this
	// The actual distance in bytes between positions
	// Element type + Count = Float + Count
	m_Stride += 4 * element.count;
}