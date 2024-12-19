#pragma once

#include <exception>

namespace xengine {

    class ApplicationInitException : public std::exception {

    public:
        static inline int WINDOW_CREATION_ERROR = -1;
        static inline int LIB_INIT_ERROR = -2;
        static inline int ENGINE_INIT_ERROR = -3;

        inline const char * what () const noexcept {
            return "Failed to initialize the application";
        }

        int code {};
    };

    void throwApplicationInitException(int code);

}