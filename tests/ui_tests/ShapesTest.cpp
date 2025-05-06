#include "ShapesTest.h"

#include <ComponentUIFactory.h>
#include <public/XEngine.h>

/**
 * This is a test example of simple shapes:
 *
 * 1. Squad
 * 2. Circle
 * 3. Triangle
 */

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
        // Camera
        ////////////////////////////////////

        float rotSpeed = 30.0f;
        float moveSpeed = 2.0f;

        float rot = 0.0f;
        glm::vec3 positionCamera = { 0.0f, 0.0f, 0.0f };
        if (m_renderer->hasRenderData()) {
            positionCamera = m_renderer->getCamera()->getPosition();
            rot = m_renderer->getCamera()->getRotation();
        }

        if (Input::IsKeyPressed(XE_KEY_A)) {
            positionCamera.x -= moveSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_D)) {
            positionCamera.x += moveSpeed * times;
        }

        if (Input::IsKeyPressed(XE_KEY_W)) {
            positionCamera.y += moveSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_S)) {
            positionCamera.y -= moveSpeed *times;
        }

        if (Input::IsKeyPressed(XE_KEY_E)) {
            rot += rotSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_R)) {
            rot -= rotSpeed * times;
        }

        if (m_renderer->hasRenderData()) {
            m_renderer->updateCamera(positionCamera, rot);
            m_renderer->render();
        }
    }

    void ShapesComponentUI::onDrawUI() {

        using namespace xengine;

        addButton("Rectangle", [&, this](const char *text) {
            addShape(ShapesUIMode::RECTANGLE_SHAPE);
        });

        addButton("Triangle", [&, this](const char *text) {
            addShape(ShapesUIMode::TRIANGLE_SHAPE);
        });

        addButton("Circle", [&, this](const char *text) {
            addShape(ShapesUIMode::CIRCLE_SHAPE);
        });

        auto updateRectangle = [&, this](const char *text) {

            auto shape = (Rectangle*) m_data->getShapeById(m_shapeId);

            glm::vec4 newColor = { m_color[0], m_color[1], m_color[2], 1.0f };
            glm::vec3 defaultPosition = { 0.0f, 0.0f, 0.0f };

            float texutureIndex = -1.0f;

            if (strcmp(text, "change_texture") == 0) {
                texutureIndex = shape->getTextureIndex() * -1.0f;
            }

            // Resubmit shape

            resetRenderData();

            auto newshape = ComponentUIFactory::createRectShape(defaultPosition, newColor, texutureIndex);

            submitShape(newshape, "base.shader");
        };

        if (m_shapesUIModeCurrent == ShapesUIMode::RECTANGLE_SHAPE) {

            Shape* shape = m_data->getShapeById(m_shapeId);

            auto vec4 = shape->getColor();
            m_color = glm::value_ptr(vec4);

            addColorPicker("Color", m_color, updateRectangle);

            auto rect = (Rectangle*) shape;

            addText("Width: %.1f", rect->getWidth());
            addText("Height: %.1f", rect->getHeight());
            addText("Center (X,Y,Z): (%.1f, %.1f, %.1f)", rect->getCoord().x, rect->getCoord().y, rect->getCoord().z);

            static bool enableTexture = false;

            addSpace();
            if (addCheckBox("Set texture", enableTexture)) {
                updateRectangle("change_texture");
            }

        }

        auto updateTriangle = [&, this](const char *text) {

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

            addColorPicker("Color", m_colorTriangle, updateTriangle);

            auto triangle = (Triangle*) m_data->getShapeById(m_shapeId);

            auto arrPtr = triangle->getBuffer();
            addText("P 1 (X,Y,Z): (%.1f, %.1f, %.1f)", arrPtr->position.x, arrPtr->position.y, arrPtr->position.z);

            arrPtr++; // Next element
            addText("P 2 (X,Y,Z): (%.1f, %.1f, %.1f)", arrPtr->position.x, arrPtr->position.y, arrPtr->position.z);

            arrPtr++; // Next element
            addText("P 3 (X,Y,Z): (%.1f, %.1f, %.1f)", arrPtr->position.x, arrPtr->position.y, arrPtr->position.z);
        }

        if (m_shapesUIModeCurrent == ShapesUIMode::CIRCLE_SHAPE) {

            Shape* shape = m_data->getShapeById(m_shapeId);

            auto rect = (Rectangle*) shape;

            addText("Width: %.1f", rect->getWidth());
            addText("Height: %.1f", rect->getHeight());
            addText("Center (X,Y,Z): (%.1f, %.1f, %.1f)", rect->getCoord().x, rect->getCoord().y, rect->getCoord().z);
        }

        if (m_shapesUIModeCurrent != ShapesUIMode::INIT) {
            addSpace();
            addText("Camera controls:");
            addText("Left, right, up, down - A, D, W, S");
            addText("Rotation - R");
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

        ComponentUIFactory::submitShape(shape, m_renderer.get(), m_data.get(), shaderName);

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
