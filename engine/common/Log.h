#pragma once

#ifdef ENABLE_LOGGING
    #include "spdlog/spdlog.h"
#endif

// A pointer
// logError("Create the visualizer viewer({:p}).", fmt::ptr(obj));

static void initLogger() {
#ifdef ENABLE_LOGGING
    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    spdlog::set_pattern("%^[%T.%e] [%P] [%t] : %L : %v%$");
    spdlog::set_level(spdlog::level::trace);
#endif
}

template < typename... Args >
static auto logError(const std::string& message, Args&&... args)
{
#ifdef ENABLE_LOGGING
    spdlog::error(message, std::forward<Args>(args)...);
#endif
}

template < typename... Args >
static auto logInfo(const std::string& message, Args&&... args)
{
#ifdef ENABLE_LOGGING
    spdlog::info(message, std::forward<Args>(args)...);
#endif
}

template < typename... Args >
static auto logWarn(const std::string& message, Args&&... args)
{
#ifdef ENABLE_LOGGING
    spdlog::warn(message, args...);
#endif
}

template < typename... Args >
static auto logDebug(const std::string& message, Args&&... args)
{
#ifdef ENABLE_LOGGING
    spdlog::debug(message, std::forward<Args>(args)...);
#endif
}