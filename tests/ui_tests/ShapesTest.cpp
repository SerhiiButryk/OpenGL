#include "ShapesTest.h"

#include <common/Log.h>
#include <opengl/Renderer.h>
#include <opengl/shapes/Rectangle.h>
#include <ui/Widgets.h>

static xengine::Renderer renderer;

static float g_color1[] = { 0.0f, 1.0f, 0.0f, 1.0f };

static float g_centerX = 0;
static float g_centerY = 0;

static float g_width = 100.0f;
static float g_height = 100.0f;

static float x_coord = 0.0f;
static float y_coord = 0.0f;

namespace test {

    constexpr int SHAPE_COUNT = 1;
    constexpr int VERTEX_COUNT = 4 * SHAPE_COUNT;
    constexpr int INDEX_MAX_BUFFER_COUNT = 6 * SHAPE_COUNT;

    void configCommand(xengine::RenderCommand* command, Application *app) {

        command->setConfigs({ app->getWidth(), app->getHeight(), VERTEX_COUNT, INDEX_MAX_BUFFER_COUNT });
    }

    void configRenderer(xengine::RenderCommand* command, xengine::Renderer *renderer, Application *app) {

        renderer->begin(command);

        std::string resPath = app->getResourcePath();

        renderer->prepareShader(resPath + "/shader/Basic_2.shader");
        renderer->prepareMVPMatrix("u_MVP");
        renderer->prepareTexture(resPath + "/textures/test.png", "u_Texture");

        renderer->end();
    }

    xengine::Rectangle createShape(float width, float height, glm::vec3 point, float color[]) {

        using namespace xengine;

        Rectangle rect(point, width, height);

        rect.setTextureIndex(-1.0f);
        rect.setColor({ color[0], color[1], color[2], color[3] });
        rect.update();

        return rect;
    }

    void ShapesTest::onCreate(Application *app) {

        using namespace xengine;

        auto* renderCommand = new RenderCommand();

        // Initialize command
        configCommand(renderCommand, app);
        // Initialize render
        configRenderer(renderCommand, &renderer, app);

        /**
        * Prepare a shape
        */

        g_centerX = app->getWidth() / 2;
        g_centerY = app->getHeight() / 2;

        x_coord = g_centerX - g_width;
        y_coord = g_centerY - g_height;

        glm::vec3 point = {x_coord, y_coord, 0.0f};

        auto rect = createShape(g_width, g_height, point, g_color1);
        renderCommand->setShape(rect);
    }

    void ShapesTest::onDestroy() {

        renderer.clear();
    }

    void ShapesTest::onBeforeRender() {
    }

    void ShapesTest::onRender() {

        using namespace xengine;

        auto updateShape = [](const char* text) {

            glm::vec3 point = {x_coord, y_coord, 0.0f};

            auto rect = createShape(g_width, g_height, point, g_color1);
            renderer.getCurrentCommand()->setShape(rect);
        };

        addColorPicker("Select color", g_color1, updateShape);

        addInputField("Width", &g_width, updateShape);
        addInputField("Height", &g_height, updateShape);

        addInputField("X", &x_coord, updateShape);
        addInputField("Y", &y_coord, updateShape);

        renderer.executeCurrentCommand();
    }
}
