#pragma once

#include <exception>

class ApplicationInitException : public std::exception {

public:
    static int WINDOW_CREATION_ERROR;
    static int LIB_INIT_ERROR;
    static int ENGINE_INIT_ERROR;

    inline const char * what () const noexcept {
        return "Failed to initialize the application";
    }

    int code {};
};

void throwApplicationInitException(int code);