#include "Log.h"

namespace xengine {

    Log::Log() {
        init();
    }

    void Log::init() {
#ifdef ENABLE_LOGGING
        // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
        spdlog::set_pattern("%^[%T.%e] [%P] [%t] : %L : %v%$");
        spdlog::set_level(spdlog::level::trace);
#endif
    }

    void Log::setLogLevel(bool enableDebug) {
        if (enableDebug) {
            spdlog::set_level(spdlog::level::trace);
        } else {
            spdlog::set_level(spdlog::level::info);
        }
    }

    bool Log::isDebugLogEnabled() {
        return spdlog::get_level() == spdlog::level::trace;
    }
}
