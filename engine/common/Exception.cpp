#include "Exception.h"

namespace xengine {

    void throwApplicationInitException(int code) {
        auto ex = ApplicationInitException();
        ex.code = code;
        throw ex;
    }

}