#pragma once

#ifdef ENABLE_LOGGING
    #include "spdlog/spdlog.h"
    #include <glm/glm.hpp>
#endif

namespace xengine {

    // A pointer
    // logError("Create the visualizer viewer({:p}).", fmt::ptr(obj));

    #define LOG_INFO(...)          ::xengine::Log::getInstance().logInfo(__VA_ARGS__)
    #define LOG_WARN(...)          ::xengine::Log::getInstance().logWarn(__VA_ARGS__)
    #define LOG_ERROR(...)         ::xengine::Log::getInstance().logError(__VA_ARGS__)
    #define LOG_DEBUG(...)         ::xengine::Log::getInstance().logDebug(__VA_ARGS__)

    class Log {
    public:

        static inline const std::string CORE_LOG_FILE_NAME = "CORE.logs";

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
            // Log to default output
            spdlog::error(message, std::forward<Args>(args)...);
            // Log to file
            mFileLogger->error(message, std::forward<Args>(args)...);
            mFileLogger->flush();
#endif
        }

        template<typename... Args>
        auto logInfo(const std::string &message, Args &&... args) {
#ifdef ENABLE_LOGGING
            // Log to default output
            spdlog::info(message, std::forward<Args>(args)...);
            // Log to file
            mFileLogger->info(message, std::forward<Args>(args)...);
            mFileLogger->flush();
#endif
        }

        template<typename... Args>
        auto logWarn(const std::string &message, Args &&... args) {
#ifdef ENABLE_LOGGING
            // Log to default output
            spdlog::warn(message, args...);
            // Log to file
            mFileLogger->warn(message, args...);
            mFileLogger->flush();
#endif
        }

        template<typename... Args>
        auto logDebug(const std::string &message, Args &&... args) {
#ifdef ENABLE_LOGGING
            // Log to default output
            spdlog::debug(message, std::forward<Args>(args)...);
            // Log to file
            mFileLogger->debug(message, std::forward<Args>(args)...);
            mFileLogger->flush();
#endif
        }

    private:
        std::shared_ptr<spdlog::logger> mFileLogger;
    };

    // Helper functions
    void logMat4(const std::string& message, const glm::mat4& m);

}