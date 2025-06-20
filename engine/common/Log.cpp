#include "Log.h"

#include <fstream>

#include "spdlog/sinks/basic_file_sink.h"
#include <file/Resources.h>

namespace xengine {

    void clearFileIfExists(const std::string& filename) {
        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            file.close(); // The file is now empty
        } else {
            spdlog::error("Failed to open file: {}", filename);
        }
    }

    Log::Log() {
        init();
    }

    void Log::init() {
#ifdef ENABLE_LOGGING
        // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
        spdlog::set_pattern("%^[%T.%e] [%P] [%t] : %L : %v%$");
        spdlog::set_level(spdlog::level::trace);

        const auto currPath = std::string(file::getCurrentPath());
        const auto finalPath = file::getPlatformPath(currPath + "/" + CORE_LOG_FILE_NAME);
        clearFileIfExists(finalPath);

        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(CORE_LOG_FILE_NAME));

        mFileLogger = std::make_shared<spdlog::logger>("CORE", begin(sinks), end(sinks));
        mFileLogger->set_level(spdlog::level::trace);

        spdlog::register_logger(mFileLogger);

#endif
    }

    void Log::setLogLevel(bool enableDebug) {

        auto level = spdlog::level::trace;

        if (!enableDebug) {
            level = spdlog::level::info;
        }

        spdlog::set_level(level);
        mFileLogger->set_level(level);
    }

    bool Log::isDebugLogEnabled() {
        return spdlog::get_level() == spdlog::level::trace;
    }

    void  Log::cleanup() {
        spdlog::shutdown();
        m_LoggerStopped = true;
    }

    void logMat4(const std::string& mes, const glm::mat4& m) {

        std::string message = mes + "\n";

        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                message += std::to_string(m[col][row]);
                message += " ";
            }

            if (row != 3) // Do not put for the last line
                message += "\n";
        }

        LOG_INFO(message);
    }
}
