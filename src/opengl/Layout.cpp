#include "Layout.h"

BufferLayout::BufferLayout()
{

}

void BufferLayout::add(const LayoutDefinition& element)
{
	elements.push_back(element);
}