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
            positionCamera.y -= moveSpeed *times;
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

        addColorPicker("Set color", glm::value_ptr(color), [&, this](const char *text) {});

        addText("--- Rectangle ---");

        float f = 0.0f;
        addInputField("Width", &f, [&, this](const char *text) {});
        addInputField("Height", &f, [&, this](const char *text) {});
        addInputField("Center1", &f, [&, this](const char *text) {});

        addSpace();
        addButton("Add1", [&, this](const char *text) {
            addShape(ShapesUIMode::RECTANGLE_SHAPE);
        }, false);

        addText("--- Triangle ---");

        addInputField("X", &f, [&, this](const char *text) {});
        addInputField("Y", &f, [&, this](const char *text) {});
        addInputField("Z", &f, [&, this](const char *text) {});
        addInputField("Center2", &f, [&, this](const char *text) {});

        addSpace();
        addButton("Add2", [&, this](const char *text) {
            addShape(ShapesUIMode::TRIANGLE_SHAPE);
        }, false);

        addText("--- Circle ---");

        addSpace();
        addButton("Add3", [&, this](const char *text) {
            addShape(ShapesUIMode::CIRCLE_SHAPE);
        }, false);

        // auto updateRectangle = [&, this](const char *text) {
        //
        //     auto shape = (Rectangle*) m_renderer->getShapeById(m_shapeId);
        //
        //     glm::vec4 newColor = { m_color[0], m_color[1], m_color[2], 1.0f };
        //     glm::vec3 defaultPosition = { 0.0f, 0.0f, 0.0f };
        //
        //     float texutureIndex = -1.0f;
        //
        //     if (strcmp(text, "change_texture") == 0) {
        //         texutureIndex = shape->getTextureIndex() * -1.0f;
        //     }
        //
        //     auto newshape = ComponentUIFactory::createRectShape(defaultPosition, newColor, texutureIndex);
        //
        //     submitShape(newshape, "base.shader");
        // };
        //
        // if (m_shapesUIModeCurrent == ShapesUIMode::RECTANGLE_SHAPE) {
        //
        //     Shape* shape = m_renderer->getShapeById(m_shapeId);
        //
        //     auto vec4 = shape->getColor();
        //     m_color = glm::value_ptr(vec4);
        //
        //     addColorPicker("Color", m_color, updateRectangle);
        //
        //     auto rect = (Rectangle*) shape;
        //
        //     addText("Width: %.1f", rect->getWidth());
        //     addText("Height: %.1f", rect->getHeight());
        //     addText("Center (X,Y,Z): (%.1f, %.1f, %.1f)", rect->getCoord().x, rect->getCoord().y, rect->getCoord().z);
        //
        //     static bool enableTexture = false;
        //
        //     addSpace();
        //     if (addCheckBox("Set texture", enableTexture)) {
        //         updateRectangle("change_texture");
        //     }
        //
        // }
        //
        // auto updateTriangle = [&, this](const char *text) {
        //
        //     glm::vec4 color = { m_colorTriangle[0], m_colorTriangle[1], m_colorTriangle[2], 1.0f};
        //
        //     auto shape = ComponentUIFactory::createTriangleShape(
        //         { -0.5f, -0.5f, 0.0f },
        //         { 0.5f, -0.5f, 0.0f },
        //         { 0.0f, 0.5f, 0.0f },
        //         color);
        //
        //     submitShape(shape, "base.shader");
        //
        // };
        //
        // if (m_shapesUIModeCurrent == ShapesUIMode::TRIANGLE_SHAPE) {
        //
        //     m_colorTriangle = glm::value_ptr(color);
        //
        //     addColorPicker("Color", m_colorTriangle, updateTriangle);
        //
        //     auto triangle = (Triangle*) m_renderer->getShapeById(m_shapeId);
        //
        //     auto arrPtr = triangle->getBuffer();
        //     addText("P 1 (X,Y,Z): (%.1f, %.1f, %.1f)", arrPtr->position.x, arrPtr->position.y, arrPtr->position.z);
        //
        //     arrPtr++; // Next element
        //     addText("P 2 (X,Y,Z): (%.1f, %.1f, %.1f)", arrPtr->position.x, arrPtr->position.y, arrPtr->position.z);
        //
        //     arrPtr++; // Next element
        //     addText("P 3 (X,Y,Z): (%.1f, %.1f, %.1f)", arrPtr->position.x, arrPtr->position.y, arrPtr->position.z);
        // }
        //
        // if (m_shapesUIModeCurrent == ShapesUIMode::CIRCLE_SHAPE) {
        //
        //     Shape* shape = m_renderer->getShapeById(m_shapeId);
        //
        //     auto rect = (Rectangle*) shape;
        //
        //     addText("Width: %.1f", rect->getWidth());
        //     addText("Height: %.1f", rect->getHeight());
        //     addText("Center (X,Y,Z): (%.1f, %.1f, %.1f)", rect->getCoord().x, rect->getCoord().y, rect->getCoord().z);
        // }
        //
        // if (m_shapesUIModeCurrent != ShapesUIMode::INIT) {
        //     addSpace();
        //     addText("Camera controls:");
        //     addText("Left, right, up, down - A, D, W, S");
        //     addText("Rotation - R");
        // }

    }

    void ShapesComponentUI::addShape(ShapesUIMode mode) {

        m_shapesUIModeCurrent = mode;

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
