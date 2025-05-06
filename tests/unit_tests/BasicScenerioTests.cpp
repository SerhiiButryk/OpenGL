#include "BasicScenerioTests.h"

#include <base/Assert.h>
#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <opengl/Shader.h>
#include <opengl/VertexBuffer.h>
#include <opengl/external/LoaderOpenGL.h>
#include <opengl/shapes/Shape.h>
#include <window/Window.h>

namespace test {

    int BasicScenerioTests::run() const {

        LOG_INFO("BasicScenerioTests::run Started");

        using namespace xengine;

        ASSERT_LOG(GLEngine::initEngine(), "BasicScenerioTests::run Engine is not initialized");

        // Create window for test
        const auto window = std::make_unique<Window>();

        WindowConfigs windowConfigs = {100, 100, "Test"};
        window->onCreateWindow(windowConfigs);

        ASSERT_LOG(LoaderOpenGL::init(), "BasicScenerioTests::run OpenGL is not initialized");

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // VertexBuffer basic test
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        {
            VertexBuffer vb = VertexBuffer();

            auto id = vb.getRenderId();
            LOG_INFO("BasicScenerioTests::run id == {}", id);

            ASSERT_LOG(id > 0, "BasicScenerioTests::run Renderer id is wrong");

            vb.bind();

            float vertices[] = {
                1.0f, 2.0f, 3.0f, 4.0f
            };

            vb.createAndInitialize(vertices, sizeof(vertices), true);

            ASSERT_LOG(vb.isDynamic(), "BasicScenerioTests::run wrong isDynamic result");

            float vertices2[] = {
                2.0f, 2.0f, 3.0f, 4.0f
            };

            vb.update(vertices2, sizeof(vertices2));

            vb.deleteBuffer();

        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Shader basic test
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        {
            // 1. Load basic shader
            std::string resPath = "../engine/res";
            const auto shader = std::make_unique<Shader>(resPath + "/shader/Basic.shader");

            // 2. Check results
            ASSERT_LOG(shader->shaderParsedOkay(), "BasicScenerioTests::run Failed to parse or locate shader file");
            ASSERT_LOG(shader->getRendererID() != 0, "BasicScenerioTests::run Failed to create shader");

            // 3. Uniform test
            int location = shader->getUniformForTest("u_Color");
            ASSERT_LOG(location != -1, "BasicScenerioTests::run Failed to get uniform");

            // 4. Uniform cache test

            // Should be false at this point
            ASSERT_LOG(!shader->gotLastUniformFromCache(), "BasicScenerioTests::run Not expected value");

            // This time it should be from cache
            int location2 = shader->getUniformForTest("u_Color");
            ASSERT_LOG(location2 != -1, "BasicScenerioTests::run Failed to get uniform second time");

            // Check this
            ASSERT_LOG(shader->gotLastUniformFromCache(), "BasicScenerioTests::run Not from cache uniform");
        }

        window->onDestroy();

        LOG_INFO("BasicScenerioTests::run Finished");

        return 0;
    }

}


