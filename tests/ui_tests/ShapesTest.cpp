#include "ShapesTest.h"

#include <ComponentUIFactory.h>
#include <public/XEngine.h>

/**
 * This is an example to demonstrate how to work with shapes:
 *
 * 1. Regtangle
 * 2. Circle
 * 3. Triangle
 */

namespace test {

    ShapesComponentUI::ShapesComponentUI(Application *app) : TestCase(app) {
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

        float rot = m_camera->getRotation();
        glm::vec3 positionCamera = m_camera->getPosition();

        if (Input::IsKeyPressed(XE_KEY_A)) {
            positionCamera.x -= moveSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_D)) {
            positionCamera.x += moveSpeed * times;
        }

        if (Input::IsKeyPressed(XE_KEY_W)) {
            positionCamera.y += moveSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_S)) {
            positionCamera.y -= moveSpeed * times;
        }

        if (Input::IsKeyPressed(XE_KEY_E)) {
            rot += rotSpeed * times;
        } else if (Input::IsKeyPressed(XE_KEY_R)) {
            rot -= rotSpeed * times;
        }

        m_camera->setPosition(positionCamera);
        m_camera->setRotation(rot);

        m_renderer->render();
    }

    void ShapesComponentUI::onDrawUI() {
        using namespace xengine;

        addSpace();
        addButton("Clear draw buffer", [&, this](const char *text) {
            m_renderer->releaseObjects();
        }, false);

        addSpace();
        addText("--- Camera controls ---");
        addText("Left, right, up, down: A, D, W, S");
        addText("Rotation: R");

        addText("--- Shapes settings ---");

        addColorPicker("Set color", glm::value_ptr(m_color), [&, this](const char *text) {
        });

        addInputField("Center X:", "centerx1", &center.x, [&, this](const char *text) {
        }, false, 50.0f);
        addInputField("Y:", "centery1", &center.y, [&, this](const char *text) {
        }, true, 50.0f);
        addInputField("Z:", "centerz1", &center.z, [&, this](const char *text) {
        }, true, 50.0f);

        addInputField("Texture index:", "texindex", &textIndex, [&, this](const char *text) {
        }, false, 50.0f);

        addText("--- Rectangle ---");

        addInputField("Width:", "Width", &widthAndHeight.x, [&, this](const char *text) {
        }, false, 50.0f);
        addInputField("Height:", "Height", &widthAndHeight.y, [&, this](const char *text) {
        }, true, 50.0f);

        addSpace();

        addText("--- Triangle ---");

        addInputField("P1 X:", "P1x", &p1.x, [&, this](const char *text) {
        }, false, 50.0f);
        addInputField("Y:", "P1y", &p1.y, [&, this](const char *text) {
        }, true, 50.0f);
        addInputField("Z:", "P1z", &p1.z, [&, this](const char *text) {
        }, true, 50.0f);

        addInputField("P2 X:", "P2x", &p2.x, [&, this](const char *text) {
        }, false, 50.0f);
        addInputField("Y:", "P2y", &p2.y, [&, this](const char *text) {
        }, true, 50.0f);
        addInputField("Z:", "P2z", &p2.z, [&, this](const char *text) {
        }, true, 50.0f);

        addInputField("P3 X:", "P3x", &p3.x, [&, this](const char *text) {
        }, false, 50.0f);
        addInputField("Y:", "P3y", &p3.y, [&, this](const char *text) {
        }, true, 50.0f);
        addInputField("Z:", "P3z", &p3.z, [&, this](const char *text) {
        }, true, 50.0f);

        addSpace();

        addText("--- Circle ---");

        addText("--- Select shape ---");

        addSpace();

        /////////////////////////
        /// Shape selection
        /////////////////////////

        bool checked1 = (m_shapeSelected == ShapeSelected::CIRCLE_SHAPE);
        bool checked2 = (m_shapeSelected == ShapeSelected::TRIANGLE_SHAPE);
        bool checked3 = (m_shapeSelected == ShapeSelected::RECTANGLE_SHAPE);
        bool checked4 = (m_shapeSelected == ShapeSelected::BATCH_SHAPE);
        bool checked5 = (m_shapeSelected == ShapeSelected::CUBE_SHAPE);

        if (addCheckBox("Circle", checked1, true)) {
            m_shapeSelected = ShapeSelected::CIRCLE_SHAPE;
        }

        if (addCheckBox("Triangle", checked2, true)) {
            m_shapeSelected = ShapeSelected::TRIANGLE_SHAPE;
        }

        if (addCheckBox("Rect", checked3, true)) {
            m_shapeSelected = ShapeSelected::RECTANGLE_SHAPE;
        }

        if (addCheckBox("Batch", checked4, true)) {
            m_shapeSelected = ShapeSelected::BATCH_SHAPE;
        }

        if (addCheckBox("Cube", checked5, true)) {
            m_shapeSelected = ShapeSelected::CUBE_SHAPE;
        }

        addSpace();
        addSpace();

        /////////////////////////
        /// Add button
        /////////////////////////

        addButton("Add", [&, this](const char *) {

            LOG_INFO("Adding new shape:");

            LOG_INFO("*** width {}, height {}", widthAndHeight.x, widthAndHeight.y);

            LOG_INFO("*** P1 ({},{},{}) P2 ({},{},{}) P3 ({},{},{})", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x,
                     p3.y, p3.z);

            LOG_INFO("*** center ({},{},{})", center.x, center.y, center.z);

            addShape();

        }, false);
    }

    void ShapesComponentUI::addShape() {

        switch (m_shapeSelected) {

            case ShapeSelected::RECTANGLE_SHAPE: {
                submitRectangle();
            }

            break;

            case ShapeSelected::CIRCLE_SHAPE: {
                submitCircle();
            }

            break;

            case ShapeSelected::TRIANGLE_SHAPE: {
                submitTriangle();
            }

            break;

            case ShapeSelected::BATCH_SHAPE: {
                submitBatch();
            }

            break;

            case ShapeSelected::CUBE_SHAPE: {
                submitCube();
            }

            break;

        }
    }

    void ShapesComponentUI::submitRectangle() {

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        std::string shaderPath = xengine::file::buildShaderPath(m_app->getResourcePath(), "base.shader");
        std::string texturePath = xengine::file::buildTexturePath(m_app->getResourcePath(), "wood_surface.png");

        auto* object = ComponentUIFactory::createRectShape(shaderPath, texturePath, model, m_color, 1.0f, 1.0f, 1.0f);

        m_renderer->submit(object);

    }

    void ShapesComponentUI::submitTriangle() {

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        std::string shaderPath = xengine::file::buildShaderPath(m_app->getResourcePath(), "base.shader");

        glm::vec3 points[] = { p1, p2, p3 };
        auto* object = ComponentUIFactory::createTriangleShape(shaderPath, "", model, m_color, points, -1.0f);

        m_renderer->submit(object);

    }

    void ShapesComponentUI::submitCircle() {

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        std::string shaderPath = xengine::file::buildShaderPath(m_app->getResourcePath(), "circle.shader");

        auto* object = ComponentUIFactory::createRectShape(shaderPath, "", model, m_color, 1.0f, 1.0f, -1.0f);

        m_renderer->submit(object);

    }

    void ShapesComponentUI::submitBatch() {

        using namespace xengine;

        m_renderer->batchStart();

        {
            glm::vec4 m_color = Color(GREY_COLOR_LIGHT);

            auto model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            std::string shaderPath = xengine::file::buildShaderPath(m_app->getResourcePath(), "base.shader");
            std::string texturePath = xengine::file::buildTexturePath(m_app->getResourcePath(), "wood_surface.png");

            auto* object = ComponentUIFactory::createRectShape(shaderPath, texturePath, model, m_color, 1.0f, 1.0f, -1.0f);
            m_renderer->batchSubmit(object);
        }

        {
            glm::vec4 m_color = Color(GREY_COLOR_DARK);

            auto model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            std::string shaderPath = xengine::file::buildShaderPath(m_app->getResourcePath(), "base.shader");
            std::string texturePath = xengine::file::buildTexturePath(m_app->getResourcePath(), "wood_surface.png");

            auto* object = ComponentUIFactory::createRectShape(shaderPath, texturePath, model, m_color, 0.5f, 0.5f, -1.0f);
            m_renderer->batchSubmit(object);
        }

        m_renderer->batchEnd();

    }

    void ShapesComponentUI::submitCube() {

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        std::string shaderPath = xengine::file::buildShaderPath(m_app->getResourcePath(), "base.shader");
        std::string texturePath = xengine::file::buildTexturePath(m_app->getResourcePath(), "wood_surface.png");

        auto* object = ComponentUIFactory::createCubeShape(shaderPath, texturePath, model);

        m_renderer->submit(object);

    }
}
