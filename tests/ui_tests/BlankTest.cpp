#include "BlankTest.h"

namespace test {

    /**
    *  Test OpenGL APIs here
    */

    using namespace xengine;

    static RenderGL render;

    void BlankTest::onAttach() {

        render.batchStart();

        auto* obj2 = new Object();
        auto* shape = new Rectangle(1.0f, 1.0f);
        shape->setColor({1.0f, 0.0f, 0.0f, 1.0f});
        obj2->shape = shape;

        auto path = xengine::file::buildShaderPath("../engine/res", "test.shader");
        obj2->shader = xengine::Shader::createShader(path);

        render.batchSubmit(obj2);

        auto* obj = new Object();
        obj->shape = new Rectangle(0.5f, 0.5f);

        obj->shader = xengine::Shader::createShader(path);

        render.batchSubmit(obj);

        render.batchEnd();

    }

    void BlankTest::onDetach() {

    }

    void BlankTest::onDraw() {

        render.render();

    }
}