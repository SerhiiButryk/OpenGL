#include "TextureTest.h"

#include <ComponentUIFactory.h>
#include <public/XEngine.h>

/**
 * This is an example to demonstrate how to work with a texture
 */

static xengine::RenderGL glRenderer;

static xengine::Shape* shape = nullptr;

static bool setColor = false;

namespace test {

    void TextureTest::onAttach() {

        using namespace xengine;

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        std::string shaderPath = file::buildShaderPath(m_app->getResourcePath(), "base.shader");
        std::string texturePath = file::buildTexturePath(m_app->getResourcePath(), "wood_surface.png");

        float textureIndex = 1.0f;
        glm::vec4 color = { 1.0f, 0.0f, 0.0f, 1.0f};

        auto* object = ComponentUIFactory::createRectShape(shaderPath, texturePath, model, color, 1.0f, 1.0f, textureIndex);
        shape = object->getShape();

        glRenderer.submit(object);

    }

    void TextureTest::onDetach() {
    }

    static float x_Shift = 0.0f;
    static float y_Shift = 0.0f;

    void onClick(const char* text) {
        LOG_INFO("onClick() button with '{}' name is clicked", text);
        float base = 10;
        if (strcasecmp(text, "Left") == 0) {
            x_Shift -= base;
        } else if (strcasecmp(text, "Right") == 0) {
            x_Shift += base;
        } else if (strcasecmp(text, "Up") == 0) {
            y_Shift += base;
        } else if (strcasecmp(text, "Down") == 0) {
            y_Shift -= base;
        }
        LOG_INFO("onClick() {} {}", x_Shift, y_Shift);
    }

    void TextureTest::onDraw() {

        using namespace xengine;

        glRenderer.render();
    }

    void TextureTest::onDrawUI() {

        using namespace xengine;

        addSpace();

        // TODO: Doesn't work
        // addButton("Left", &onClick, false);
        // addButton("Right", &onClick);
        // addButton("Up", &onClick);
        // addButton("Down", &onClick);

        if (addCheckBox("Set color", setColor)) {

            auto* shapeRef = glRenderer.getShapeById(shape->getID());

            if (setColor) {
                shapeRef->setTextureIndex(-1.0f);
            } else {
                shapeRef->setTextureIndex(1.0f);
            }

            shapeRef->invalidate();
        }

    }
}
