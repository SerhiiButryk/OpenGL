#include "ShapesTest.h"

#include <public/XEngine.h>

static float g_color1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

static float g_centerX = 0;
static float g_centerY = 0;

static float g_width = 1.0f;
static float g_height = 1.0f;

static auto* data1 = new xengine::RenderData();
static auto* data2 = new xengine::RenderData();

static auto* director = new xengine::RenderDirector();
// Or
// static auto* director = new xengine::RenderDirectorDebug();

static glm::vec3 g_Position_Camera = { 0.0f, 0.0f, 0.0f };
static float g_RotSpeed = 30.0f;
static float g_MoveSpeed = 2.0f;
static float g_Rot = 0.0f;

static glm::vec3 g_Rect_Pos = { 0.0f, 0.0f, 0.0f };

static xengine::Camera* g_camera = new xengine::Camera(-1.6f, 1.6f, -0.9f, 0.9f);

namespace test {

    xengine::Rectangle createRectShape(glm::vec3 point);

    void ShapesTest::onCreate(Application *app) {

        using namespace xengine;

        g_centerX = app->getWidth() / 2;
        g_centerY = app->getHeight() / 2;

        // Set initial configs

        data1->configs.height = app->getHeight();
        data1->configs.width = app->getWidth();
        data1->configs.assetsPath = app->getResourcePath();
        data1->camera = g_camera;

        data2->configs.height = app->getHeight();
        data2->configs.width = app->getWidth();
        data2->configs.assetsPath = app->getResourcePath();
        data2->camera = g_camera;

        auto rect = createRectShape(g_Rect_Pos);

        ////////////////// first shape //////////////////

        director->begin(data1);

        director->setShader("Basic_2.shader");

        director->submit(rect);

        director->end();

        ////////////////// end //////////////////

        ////////////////// second shape //////////////////

        director->begin(data2);

        director->setShader("Basic_2.shader");

        Vertex vertex1 = { { -0.7f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f},
            -1.0f
        };

        Vertex vertex2 = { { 0.0f, 0.0f, 0.0f },
            { 1.0f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.0f},
            -1.0f
        };

        Vertex vertex3 = { { -0.2f, 0.5f, 0.0f },
            { 0.5f, 1.0f, 0.0f, 1.0f},
            {0.0f, 0.0f},
            -1.0f
        };

        director->submit(vertex1);
        director->submit(vertex2);
        director->submit(vertex3);

        director->end();

        ////////////////// end //////////////////

    }

    void ShapesTest::onDestroy() {

        // Release resources

        data1->releaseResources();
        delete data1;

        data2->releaseResources();
        delete data2;

        delete g_camera;

        delete director;
    }

    void ShapesTest::onRender() {

        using namespace xengine;

        ////////////////////////////////////
        // Frame rate time
        ////////////////////////////////////

        Timestamp times = m_app->getFrameDeltaTime();

        ////////////////////////////////////
        // Camera controls
        ////////////////////////////////////

        if (Input::IsKeyPressed(XE_KEY_A)) {
            g_Position_Camera.x -= g_MoveSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_D)) {
            g_Position_Camera.x += g_MoveSpeed * times;
        }

        if (Input::IsKeyPressed(XE_KEY_W)) {
            g_Position_Camera.y += g_MoveSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_S)) {
            g_Position_Camera.y -= g_MoveSpeed *times;
        }

        if (Input::IsKeyPressed(XE_KEY_E)) {
            g_Rot += g_RotSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_R)) {
            g_Rot -= g_RotSpeed * times;
        }

        ////////////////////////////////////
        // Camera controls END
        ////////////////////////////////////

        data1->camera->setPosition(g_Position_Camera);
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

        // 4. Render 2 shapes with different transform

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f)) * scale;

        data1->tansform = transform;

        director->setData(data1);
        director->render();

        glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
        glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.25f, 0.0f)) * scale2;

        data2->tansform = transform2;

        director->setData(data2);
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
