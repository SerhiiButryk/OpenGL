#include "Renderer.h"

void Renderer::clean(float red, float green, float blue, float alpha) const {

    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {

    /* Bind everything before making a draw call */

    shader.bind();
    va.bind();
    ib.bind();

    /* Send a draw command */

    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);

}
