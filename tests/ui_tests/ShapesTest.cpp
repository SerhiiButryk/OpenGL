#include "ShapesTest.h"

#include <ComponentUIFactory.h>
#include <opengl/shapes/Color.h>
#include <public/XEngine.h>
#include <glm/gtc/type_ptr.hpp>
#include <opengl/shapes/Triangle.h>

/**
 * This is a test example of simple shapes:
 *
 * 1. Squad
 * 2. Circle
 * 3. Triangle
 */

static glm::vec3 g_Position_Camera = { 0.0f, 0.0f, 0.0f };

static float g_RotSpeed = 30.0f;
static float g_MoveSpeed = 2.0f;
static float g_Rot = 0.0f;

namespace test {

    ShapesComponentUI::ShapesComponentUI(Application* app) : TestCase(app) {
    }

    void ShapesComponentUI::onAttach() {
    }

    void ShapesComponentUI::onDetach() {
    }

    void ShapesComponentUI::onDraw() {

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

        // data1->camera->setPosition(g_Position_Camera);
        // data1->camera->setRotation(g_Rot);
        //
        // // 4. Render 3 shapes with different transforms
        //
        // glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        // glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.7f, 0.0f, 0.0f)) * scale;
        //
        // data1->tansform = transform;
        //
        // director->setData(data1.get());
        // director->render();
        //
        // glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
        // glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, -0.25f, 0.0f)) * scale2;
        //
        // data2->tansform = transform2;
        //
        // director->setData(data2.get());
        // director->render();
        //
        // glm::mat4 scale3 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        // glm::mat4 transform3 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * scale3;
        //
        // data3->tansform = transform3;
        //
        // director->setData(data3.get());


        if (m_director->hasRenderData())
            m_director->render();
    }

    void ShapesComponentUI::onDrawUI() {

        using namespace xengine;

        // auto updateShape = [](const char* text) {
        //
        //     glm::vec3 point = {0.0f, 0.0f, 0.0f};
        //
        //     auto rect = createRectShape(point);
        //     director->resetPointer();
        //     director->submit(rect);
        // };
        //
        // addColorPicker("Select color", g_color1, updateShape);
        //
        // addInputField("Width", &g_width, updateShape);
        // addInputField("Height", &g_height, updateShape);
        //
        // addInputField("X", &g_centerX, updateShape);
        // addInputField("Y", &g_centerY, updateShape);

        // ShapesTest* obj = this;

        addButton("Rectangle", [&, this](const char *text) {
            addShape(ShapesUIMode::RECTANGLE_SHAPE);
        });

        addButton("Triangle", [&, this](const char *text) {
            addShape(ShapesUIMode::TRIANGLE_SHAPE);
        });

        addButton("Circle", [&, this](const char *text) {
            addShape(ShapesUIMode::CIRCLE_SHAPE);
        });

        auto updateShapeColor = [&, this](const char *text) {

            glm::vec4 newColor = { m_color[0], m_color[1], m_color[2], 1.0f };
            glm::vec3 defaultPosition = { 0.0f, 0.0f, 0.0f };

            // Resubmit shape

            resetRenderData();

            auto shape = ComponentUIFactory::createRectShape(defaultPosition, newColor);

            submitShape(shape, "base.shader");
        };

        if (m_shapesUIModeCurrent == ShapesUIMode::RECTANGLE_SHAPE) {

            Shape* shape = m_data->getShapeById(m_shapeId);

            auto vec4 = shape->getColor();
            m_color = glm::value_ptr(vec4);

            addColorPicker("Color", m_color, updateShapeColor);
        }

        auto updateShapeColor2 = [&, this](const char *text) {

            // Resubmit shape

            resetRenderData();

            glm::vec4 color = { m_colorTriangle[0], m_colorTriangle[1], m_colorTriangle[2], 1.0f};

            auto shape = ComponentUIFactory::createTriangleShape(
                { -0.5f, -0.5f, 0.0f },
                { 0.5f, -0.5f, 0.0f },
                { 0.0f, 0.5f, 0.0f },
                color);

            submitShape(shape, "base.shader");

        };

        if (m_shapesUIModeCurrent == ShapesUIMode::TRIANGLE_SHAPE) {

            m_colorTriangle = glm::value_ptr(color);

            addColorPicker("Color", m_colorTriangle, updateShapeColor2);

        }
    }

    void ShapesComponentUI::addShape(ShapesUIMode mode) {

        m_shapesUIModeCurrent = mode;

        resetRenderData();

        glm::vec3 defaultPosition = { 0.0f, 0.0f, 0.0f };
        glm::vec4 defaultColor = { 0.0f, 0.0f, 0.0f, 1.0f };

        switch (mode) {

            case ShapesUIMode::RECTANGLE_SHAPE:
                {
                    auto shape = ComponentUIFactory::createRectShape(defaultPosition, defaultColor);

                    submitShape(shape, "base.shader");
                }

                break;

            case ShapesUIMode::CIRCLE_SHAPE:

                {
                    auto shape = ComponentUIFactory::createRectShape(defaultPosition, defaultColor);

                    submitShape(shape, "circle.shader");
                }

                break;

            case ShapesUIMode::TRIANGLE_SHAPE:

                {

                    glm::vec4 color = { 1.0f, 0.0f, 0.0f, 1.0f};

                    auto shape = ComponentUIFactory::createTriangleShape(
                        { -0.5f, -0.5f, 0.0f },
                        { 0.5f, -0.5f, 0.0f },
                        { 0.0f, 0.5f, 0.0f },
                        color);

                    submitShape(shape, "base.shader");
                }

                break;
        }

    }

    void ShapesComponentUI::submitShape(xengine::Shape* shape, const char* shaderName) {

        m_shapeId = shape->getID();

        ComponentUIFactory::submitShape(shape, m_director.get(), m_data.get(), shaderName);

    }

    void ShapesComponentUI::resetRenderData() {

        using namespace xengine;

        // Release previously allocated resource and clear states
        m_data->releaseResources();

        m_data->configs.height = m_app->getHeight();
        m_data->configs.width = m_app->getWidth();
        m_data->configs.assetsPath = m_app->getResourcePath();
        m_data->camera = m_camera.get();
    }

}
