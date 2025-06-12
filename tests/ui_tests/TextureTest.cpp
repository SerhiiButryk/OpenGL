#include "TextureTest.h"

#include <ComponentUIFactory.h>
#include <public/XEngine.h>

/**
 * This is an example to demonstrate how to work with a texture
 */

static xengine::RenderGL glRenderer;

static xengine::Rectangle* rectangle = nullptr;

static xengine::Object* object = nullptr;

static bool setColor = true;

namespace test {

    void TextureTest::onAttach() {

        using namespace xengine;

        object = new Object();

        rectangle = ComponentUIFactory::createRectShape(Color(GREY_COLOR));
        object->shape = rectangle;

        if (setColor) {
            object->shape->setTextureIndex(-1.0f);
        } else {
            object->shape->setTextureIndex(1.0f);
        }

        // Projection matrix
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        // View matrix
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // Model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        object->shader = Shader::createShader(m_app->getResourcePath(), "texture.shader");
        object->shader->bind();

        object->texture = Texture::createTexture(m_app->getResourcePath(), "test.png");
        object->shader->setTextureUniform("u_Texture", 0 /* Slot */);

        // Set a color in RGB format
        object->shader->setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        object->shader->setUniformMat("u_MVP", mvp);

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

            auto* shape = glRenderer.getShapeById(rectangle->getID());

            if (setColor) {
                shape->setTextureIndex(-1.0f);
            } else {
                shape->setTextureIndex(1.0f);
            }

            shape->invalidate();
        }

    }
}
