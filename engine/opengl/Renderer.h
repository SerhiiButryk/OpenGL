#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer 
{
public:
    void clean(float red, float green, float blue, float alpha) const;
    void draw(const VertexArray& va, const IndexBuffer& id, const Shader& shader) const;
};
