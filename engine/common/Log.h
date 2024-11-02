#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <time.h>

static std::string getTimestamp()
{
    using namespace std::chrono;

    // Get current time
    auto now = system_clock::now();

    // Get number of milliseconds for the current time
    // (a remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // Convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // Convert to broken time
    time_t t = time(NULL);
    
    std::tm bt;
    #ifndef LINUX_PLATFORM
        localtime_s(&bt, &t);
    #else 
        localtime_r( &t, &bt);
    #endif

    std::ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

template < typename... Args >
static auto logError(const Args&... args)
{
    std::thread::id tid = std::this_thread::get_id();
    std::string timestamp = getTimestamp();

    std::cout << tid << "::" << timestamp << "  INFO:  ";

    // lambda used as decorator to add a space
    // expands to ( ( ( std::cout << v1 ) << v2 ) << ... )
    (std::cout << ... << [&](const auto& ref) -> char { std::cout << ref; return ' '; }(args)) << '\n';
}

template < typename... Args >
static auto logInfo(const Args&... args)
{
    std::thread::id tid = std::this_thread::get_id();
    std::string timestamp = getTimestamp();

    std::cout << tid << "::" << timestamp << "  INFO:  ";

    // lambda used as decorator to add a space
    // expands to ( ( ( std::cout << v1 ) << v2 ) << ... )
    (std::cout << ... << [&](const auto& ref) -> char { std::cout << ref; return ' '; }(args)) << '\n';
}