#include "ShapesTest.h"

#include <common/Log.h>
#include <opengl/Renderer.h>
#include <opengl/shapes/Rectangle.h>

xengine::Renderer renderer;

xengine::Vertex* data = nullptr;
xengine::Vertex* beginPointer = data;

namespace test {

    void ShapesTest::onCreate(Application *app) {

        using namespace xengine;

        constexpr int SHAPE_COUNT = 5;
        constexpr int VERTEX_COUNT = 4 * SHAPE_COUNT;
        constexpr int INDEX_MAX_BUFFER_COUNT = 6 * SHAPE_COUNT;

        /**
         *  Create a render command
         */

        auto* renderCommand = new RenderCommand();

        renderCommand->setConfigs({ app->getWidth(), app->getHeight(), VERTEX_COUNT, INDEX_MAX_BUFFER_COUNT });

        renderer.begin(renderCommand);

        std::string resPath = app->getResourcePath();

        renderer.prepareShader(resPath + "/shader/Basic_2.shader");
        renderer.prepareMVPMatrix("u_MVP");
        renderer.prepareTexture(resPath + "/textures/test.png", "u_Texture");

        renderer.end();

        /**
        * Prepare a shape
        */

        data = new Vertex[VERTEX_COUNT];
        beginPointer = data;

        glm::vec3 point = {0.0f, 0.0f, 0.0f};

        for (int i = 0; i < SHAPE_COUNT; i++) {

            Rectangle rect(point, 100.0f, 100.0f);
            auto* rectBuffer = rect.getBuffer();

            for (int i = 0; i < Rectangle::VERTEX_COUNT; i++) {
                beginPointer->position = rectBuffer->position;
                beginPointer->color = rectBuffer->color;
                beginPointer->texCoord = rectBuffer->texCoord;
                beginPointer->texIndex = rectBuffer->texIndex;

                beginPointer++;
                rectBuffer++;
            }

            // Next location
            point = { point.x + 100.0f, point.y, point.z };

        }

        renderCommand->configs.drawBuffer = (float*) data;

    }

    void ShapesTest::onDestroy() {

        renderer.clear();

        delete [] data;
    }

    void ShapesTest::onBeforeRender() {
    }

    void ShapesTest::onRender() {

        using namespace xengine;

        renderer.executeCurrentCommand();
    }
}
