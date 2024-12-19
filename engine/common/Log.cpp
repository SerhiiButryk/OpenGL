#include "Log.h"

namespace xengine {

    Log::Log() {
        Init();
    }

    void Log::Init() {
#ifdef ENABLE_LOGGING
        // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
        spdlog::set_pattern("%^[%T.%e] [%P] [%t] : %L : %v%$");
        spdlog::set_level(spdlog::level::trace);
#endif
    }
}
