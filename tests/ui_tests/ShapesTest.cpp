#include "ShapesTest.h"

#include <public/XEngine.h>

static xengine::RenderDirectorBase* director;

static float g_color1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

static float g_centerX = 0;
static float g_centerY = 0;

static float g_width = 100.0f;
static float g_height = 100.0f;

static float x_coord = 0.0f;
static float y_coord = 0.0f;

namespace test {

    xengine::Rectangle createRectShape(glm::vec3 point) {

        using namespace xengine;

        Rectangle rect(point, g_width, g_height);

        rect.setTextureIndex(-1.0f);
        rect.setColor({ g_color1[0], g_color1[1], g_color1[2], g_color1[3] });
        rect.update();

        return rect;
    }

    void ShapesTest::onCreate(Application *app) {

        using namespace xengine;

        // 1. Create a data

        auto* renderData = new RenderData();

        renderData->configs.height = app->getHeight();
        renderData->configs.width = app->getWidth();
        renderData->configs.assetsPath = app->getResourcePath();

        // 2. Create a shape

        g_centerX = app->getWidth() / 2;
        g_centerY = app->getHeight() / 2;

        glm::vec3 point = { g_centerX, g_centerY, 0.0f};

        auto rect = createRectShape(point);

        // 3. Prepare the director

        director = new RenderDirector();
        // Or
        // director = new RenderDirectorDebug();
        director->setData(renderData);

        director->addShape(rect);

        director->begin();

        director->prepareShader("Basic_2.shader");
        director->prepareMVPMatrix("u_MVP");
        director->prepareTexture("test.png", "u_Texture");
    }

    void ShapesTest::onDestroy() {

        // 4. Release resources

        director->end();

        delete director;
    }

    void ShapesTest::onBeforeRender() {
    }

    void ShapesTest::onRender() {

        using namespace xengine;

        auto updateShape = [](const char* text) {

            glm::vec3 point = {x_coord, y_coord, 0.0f};

            auto rect = createRectShape(point);
            director->addShape(rect);
        };

        addColorPicker("Select color", g_color1, updateShape);

        addInputField("Width", &g_width, updateShape);
        addInputField("Height", &g_height, updateShape);

        addInputField("X", &x_coord, updateShape);
        addInputField("Y", &y_coord, updateShape);

        // 4. Render

        director->render();
    }
}
