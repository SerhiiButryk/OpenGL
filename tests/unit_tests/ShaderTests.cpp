#include "ShaderTests.h"

#include <opengl/GLEngine.h>
#include <opengl/Shader.h>
#include <opengl/external/GLEWBridge.h>
#include <window/Window.h>

#include "base/Assert.h"

namespace test {

    /**
     * This test checks that shader works well
     */
    int ShaderTests::run() const {

        LOG_INFO("ShaderTests::run Started");

        using namespace xengine;

        ASSERT_LOG(GLEngine::initEngine(), "ShaderTests::run Engine is not initialized");

        // 1. Create window for test
        const auto window = std::make_unique<Window>();
        window->create("Test", 100, 100);

        ASSERT_LOG(GLEWBridge::init(), "ShaderTests::run GLEW is not initialized");

        // 2. Load basic shader
        std::string resPath = "../../../engine/res";
        const auto shader = std::make_unique<Shader>(resPath + "/shader/Basic.shader");

        // 3. Check results
        ASSERT_LOG(shader->shaderParsedOkay(), "ShaderTests::run Failed to parse or locate shader file");
        ASSERT_LOG(shader->getRendererID() != 0, "ShaderTests::run Failed to create shader");

        // 4. Uniform test
        int location = shader->getUniformForTest("u_Color");
        ASSERT_LOG(location != -1, "ShaderTests::run Failed to get uniform");

        // Should be false at this point
        ASSERT_LOG(!shader->gotLastUniformFromCache(), "ShaderTests::run Not expected value");

        // This time it should be from cache
        int location2 = shader->getUniformForTest("u_Color");
        ASSERT_LOG(location2 != -1, "ShaderTests::run Failed to get uniform second time");

        // Check this
        ASSERT_LOG(shader->gotLastUniformFromCache(), "ShaderTests::run Not from cache uniform");

        window->destroy();

        return 0;
    }

}
