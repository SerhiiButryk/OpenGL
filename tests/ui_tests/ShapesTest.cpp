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

        if (m_renderer->hasRenderData()) {
            m_renderer->getData()->configs.viewProjMatrix = m_camera->getViewProjMatrix();
            m_renderer->render();
        }
    }

    void ShapesComponentUI::onDrawUI() {
        using namespace xengine;

        addSpace();
        addButton("Clear draw buffer", [&, this](const char *text) {
            m_renderer->releaseObjects();
            m_renderer->releaseDrawBuffer();
            m_renderer->releaseConfigs();
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

        if (addCheckBox("Circle", checked1, true)) {
            m_shapeSelected = ShapeSelected::CIRCLE_SHAPE;
        }

        if (addCheckBox("Triangle", checked2, true)) {
            m_shapeSelected = ShapeSelected::TRIANGLE_SHAPE;
        }

        if (addCheckBox("Rect", checked3, true)) {
            m_shapeSelected = ShapeSelected::RECTANGLE_SHAPE;
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

                auto shape = ComponentUIFactory::createRectShape(center, m_color, textIndex, widthAndHeight.x,
                                                                 widthAndHeight.y);

                submitShape(shape, "base.shader");
            }

            break;

            case ShapeSelected::CIRCLE_SHAPE: {

                auto shape = ComponentUIFactory::createRectShape(center, m_color, textIndex, widthAndHeight.x,
                                                                 widthAndHeight.y);

                submitShape(shape, "circle.shader");
            }

            break;

            case ShapeSelected::TRIANGLE_SHAPE: {

                auto shape = ComponentUIFactory::createTriangleShape(p1, p2, p3, m_color);

                submitShape(shape, "base.shader");
            }

            break;
        }
    }

    void ShapesComponentUI::submitShape(xengine::Shape *shape, const char *shaderName) {

        m_data->configs.height = m_app->getHeight();
        m_data->configs.width = m_app->getWidth();
        m_data->configs.assetsPath = m_app->getResourcePath();
        m_data->configs.viewProjMatrix = m_camera->getProjectionMatrix();

        m_renderer->setConfigs(m_data.get());

        // Setup object configs
        auto object = new xengine::RenderData::Objects();

        object->shape = shape;
        object->shader = xengine::Shader::createShader(m_app->getResourcePath(), shaderName);
        object->texture = xengine::Texture::createTexture(m_app->getResourcePath(), "test.png");

        object->shader->setTextureUniform("u_Texture", 0);

        m_renderer->submit(object);
    }
}
