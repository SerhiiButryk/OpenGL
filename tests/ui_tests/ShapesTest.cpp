#include "ShapesTest.h"

#include <common/Log.h>
#include <opengl/Renderer.h>
#include <opengl/shapes/Rectangle.h>

xengine::Rectangle rect({0.0f, 0.0f}, 100.0f, 100.0f);

xengine::RenderCommand renderCommand;
xengine::Renderer renderer;

namespace test {

    void ShapesTest::onCreate(Application *app) {

        /**
         *  Create a render command
         */

        renderCommand.setConfigs({app->getWidth(), app->getHeight(), 4});

        renderCommand.begin(&renderer);

        std::string resPath = app->getResourcePath();

        renderCommand.prepareShader(resPath + "/shader/Basic_2.shader");
        renderCommand.prepareMVPMatrix("u_MVP");
        renderCommand.prepareTexture(resPath + "/textures/test.png", "u_Texture");

        renderCommand.end();
    }

    void ShapesTest::onDestroy() {
        renderCommand.clear();
    }

    void ShapesTest::onBeforeRender() {
    }

    void ShapesTest::onRender() {

        using namespace xengine;

        /**
         *  Set data and execute command
         */

        Rectangle::VertexData buffer = rect.getBuffer();

        std::array<Vertex, 4> newBuffer = {};
        std::copy(buffer.begin(), buffer.end(), newBuffer.begin());

        renderCommand.configs.newBuffer = (float*) newBuffer.data();

        renderer.execute(renderCommand);
    }
}
