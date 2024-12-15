#include "InitTests.h"

#include <common/Log.h>
#include <opengl/GLEngine.h>

#include "base/Assert.h"

namespace test {

    int InitTests::run() const {
        logInfo("InitTests::run");

        using namespace xengine;

        ASSERT(GLEngine::initEngine(), "InitTests::run Cannot init engine something is very wrong");

        return 0;
    }
}
