#pragma once

#ifdef ENABLE_LOGGING
#include "spdlog/spdlog.h"
#endif

namespace xengine {

    class Log {
    public:
        Log();

        void init();

        void setLogLevel(bool enableDebug);
        bool isDebugLogEnabled();

        static Log &getInstance() {
            static Log instance;
            return instance;
        }

        template<typename... Args>
        auto logError(const std::string &message, Args &&... args) {
#ifdef ENABLE_LOGGING
            spdlog::error(message, std::forward<Args>(args)...);
#endif
        }

        template<typename... Args>
        auto logInfo(const std::string &message, Args &&... args) {
#ifdef ENABLE_LOGGING
            spdlog::info(message, std::forward<Args>(args)...);
#endif
        }

        template<typename... Args>
        auto logWarn(const std::string &message, Args &&... args) {
#ifdef ENABLE_LOGGING
            spdlog::warn(message, args...);
#endif
        }

        template<typename... Args>
        auto logDebug(const std::string &message, Args &&... args) {
#ifdef ENABLE_LOGGING
            spdlog::debug(message, std::forward<Args>(args)...);
#endif
        }
    };
}

// A pointer
// logError("Create the visualizer viewer({:p}).", fmt::ptr(obj));

#define LOG_INFO(...)          ::xengine::Log::getInstance().logInfo(__VA_ARGS__)
#define LOG_WARN(...)          ::xengine::Log::getInstance().logWarn(__VA_ARGS__)
#define LOG_ERROR(...)         ::xengine::Log::getInstance().logError(__VA_ARGS__)
#define LOG_DEBUG(...)         ::xengine::Log::getInstance().logDebug(__VA_ARGS__)
