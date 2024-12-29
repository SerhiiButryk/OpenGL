#include "ShapesTest.h"

#include <common/Log.h>
#include <opengl/Renderer.h>
#include <opengl/shapes/Rectangle.h>

xengine::Rectangle rect({0.0f, 0.0f}, 100.0f, 100.0f);

xengine::RenderCommand renderCommand;

namespace test {

    void ShapesTest::onCreate(Application *app) {

        renderCommand.begin();

        std::string resPath = app->getResourcePath();
        renderCommand.prepareShader(resPath + "/shader/Basic_2.shader", app->getWidth(), app->getHeight());

        renderCommand.prepareTexture(resPath + "/textures/test.png");

        renderCommand.end();
    }

    void ShapesTest::onDestroy() {
        renderCommand.clear();
    }

    void ShapesTest::onBeforeRender() {
    }

    void ShapesTest::onRender() {

        using namespace xengine;

        Rectangle::VertexData buffer = rect.getBuffer();

        std::array<Vertex, 4> newBuffer = {};
        std::copy(buffer.begin(), buffer.end(), newBuffer.begin());

        renderCommand.execute((float*) newBuffer.data());
    }
}
