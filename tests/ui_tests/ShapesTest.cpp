#include "ShapesTest.h"

#include <public/XEngine.h>

static float g_color1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

static float g_centerX = 0;
static float g_centerY = 0;

static float g_width = 1.0f;
static float g_height = 1.0f;

static auto data1 = std::make_unique<xengine::RenderData>();
static auto data2 = std::make_unique<xengine::RenderData>();
static auto data3 = std::make_unique<xengine::RenderData>();

static auto director = std::make_unique<xengine::RenderDirector>();
// Or
// static auto* director = new xengine::RenderDirectorDebug();

static glm::vec3 g_Position_Camera = { 0.0f, 0.0f, 0.0f };
static float g_RotSpeed = 30.0f;
static float g_MoveSpeed = 2.0f;
static float g_Rot = 0.0f;

static glm::vec3 g_Rect_Pos = { 0.0f, 0.0f, 0.0f };

static auto g_camera = std::make_unique<xengine::Camera>(-1.6f, 1.6f, -0.9f, 0.9f);

namespace test {

    xengine::Rectangle createRectShape(glm::vec3 point);

    void ShapesTest::onAttach() {

        using namespace xengine;

        g_centerX = m_app->getWidth() / 2;
        g_centerY = m_app->getHeight() / 2;

        // Set initial configs

        data1->configs.height = m_app->getHeight();
        data1->configs.width = m_app->getWidth();
        data1->configs.assetsPath = m_app->getResourcePath();
        data1->camera = g_camera.get();

        data2->configs.height = m_app->getHeight();
        data2->configs.width = m_app->getWidth();
        data2->configs.assetsPath = m_app->getResourcePath();
        data2->camera = g_camera.get();

        data3->configs.height = m_app->getHeight();
        data3->configs.width = m_app->getWidth();
        data3->configs.assetsPath = m_app->getResourcePath();
        data3->camera = g_camera.get();

        auto rect = createRectShape(g_Rect_Pos);

        ////////////////// Circle shape //////////////////

        director->begin(data1.get());

        director->setShader("circle.shader");

        director->submit(rect);

        director->end();

        ////////////////////////////////////////////////////

        ////////////////// Triangle shape //////////////////

        director->begin(data2.get());

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

        ////////////////////////////////////////////////////

        ////////////////// Circle shape //////////////////

        director->begin(data3.get());

        director->setShader("Basic_2.shader");

        director->submit(rect);

        director->end();

        ////////////////////////////////////////////////////

    }

    void ShapesTest::onDetach() {
        // Release resources
        data1->releaseResources();
        data2->releaseResources();
        data3->releaseResources();
    }

    void ShapesTest::onDraw() {

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
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.7f, 0.0f, 0.0f)) * scale;

        data1->tansform = transform;

        director->setData(data1.get());
        director->render();

        glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
        glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, -0.25f, 0.0f)) * scale2;

        data2->tansform = transform2;

        director->setData(data2.get());
        director->render();

        glm::mat4 scale3 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        glm::mat4 transform3 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * scale3;

        data3->tansform = transform3;

        director->setData(data3.get());
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
