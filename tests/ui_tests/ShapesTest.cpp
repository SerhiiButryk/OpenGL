#include "ShapesTest.h"

#include <public/XEngine.h>

static float g_color1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

static float g_centerX = 0;
static float g_centerY = 0;

static float g_width = 1.0f;
static float g_height = 1.0f;

static auto* data1 = new xengine::RenderData();

static auto* director = new xengine::RenderDirector();
// Or
// static auto* director = new xengine::RenderDirectorDebug();

static glm::vec3 g_Position = { 0.0f, 0.0f, 0.0f };
static float g_RotSpeed = 0.1f;
static float g_MoveSpeed = 0.01f;
static float g_Rot = 0.0f;

namespace test {

    xengine::Rectangle createRectShape(glm::vec3 point);

    void ShapesTest::onCreate(Application *app) {

        using namespace xengine;

        g_centerX = app->getWidth() / 2;
        g_centerY = app->getHeight() / 2;

        // 1. Create a data

        data1->configs.height = app->getHeight();
        data1->configs.width = app->getWidth();
        data1->configs.assetsPath = app->getResourcePath();

        // 2. Create a shape

        auto rect = createRectShape({0.0f, 0.0f, 0.0f});

        // 3. Prepare the director

        director->begin(data1);

        director->prepareShader("Basic_2.shader");

        // Draw rectangle

        director->submit(rect);

        // Draw triangle

        Vertex vertex1 = { { -0.7f, -0.7f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f},
            -1.0f
        };

        Vertex vertex2 = { { 0.2f, -0.7f, 0.0f },
            { 1.0f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.0f},
            -1.0f
        };

        Vertex vertex3 = { { -0.2f, -0.2f, 0.0f },
            { 0.5f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.0f},
            -1.0f
        };

        director->submit(vertex1);
        director->submit(vertex2);
        director->submit(vertex3);

        director->end();

    }

    void ShapesTest::onDestroy() {

        // 4. Release resources

        data1->releaseResources();
        delete data1;

        delete director;
    }

    void ShapesTest::onRender() {

        using namespace xengine;

        Timestamp times = m_app->getFrameDeltaTime();
        LOG_INFO("ShapesTest::onRender() time {}s {}m", times.getSeconds(), times.getMilliseconds());

        ////////////////////////////////////
        // Camera controls
        ////////////////////////////////////d

        if (Input::IsKeyPressed(XE_KEY_A)) {
            g_Position.x -= g_MoveSpeed;
        } else if (Input::IsKeyPressed(XE_KEY_D)) {
            g_Position.x += g_MoveSpeed;
        }

        if (Input::IsKeyPressed(XE_KEY_W)) {
            g_Position.y += g_MoveSpeed;
        } else if (Input::IsKeyPressed(XE_KEY_S)) {
            g_Position.y -= g_MoveSpeed;
        }

        if (Input::IsKeyPressed(XE_KEY_E)) {
            g_Rot += g_RotSpeed;
        } else if (Input::IsKeyPressed(XE_KEY_R)) {
            g_Rot -= g_RotSpeed;
        }

        ////////////////////////////////////
        // Camera controls END
        ////////////////////////////////////

        data1->camera->setPosition(g_Position);
        data1->camera->setRotation(g_Rot);

        auto updateShape = [](const char* text) {

            glm::vec3 point = {0.0f, 0.0f, 0.0f};

            auto rect = createRectShape(point);
            director->resetPointer();
            director->submit(rect);
        };

        addColorPicker("Select color", g_color1, updateShape);

        addInputField("Width", &g_width, updateShape);
        addInputField("Height", &g_height, updateShape);

        addInputField("X", &g_centerX, updateShape);
        addInputField("Y", &g_centerY, updateShape);

        // 4. Render

        director->render();
    }

    xengine::Rectangle createRectShape(glm::vec3 point) {

        using namespace xengine;

        Rectangle rect(point, g_width, g_height);

        rect.setTextureIndex(-1.0f);
        rect.setColor({ g_color1[0], g_color1[1], g_color1[2], g_color1[3] });
        rect.update();

        return rect;
    }
}
