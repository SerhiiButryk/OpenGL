#include "Exception.h"

int ApplicationInitException::WINDOW_CREATION_ERROR = -1;
int ApplicationInitException::LIB_INIT_ERROR = -2;
int ApplicationInitException::ENGINE_INIT_ERROR = -2;

void throwApplicationInitException(int code) {
    auto ex = ApplicationInitException();
    ex.code = code;
    throw ex;
}

