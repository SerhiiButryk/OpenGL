#include "InitTests.h"

#include <common/Log.h>
#include <opengl/GLEngine.h>

#include "base/Assert.h"

namespace test {

    /**
     * This test make sures that engine can be initialized
     */
    int InitTests::run() const {
        logInfo("InitTests::run Started");

        using namespace xengine;

        ASSERT_LOG(GLEngine::initEngine(), "InitTests::run Cannot init engine something is very wrong");

        return 0;
    }
}
