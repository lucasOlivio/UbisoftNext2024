#pragma once

#include <string>

/*
* Simple helper Log class that facilitates logging messages
* with different severity levels (INFO, WARNING, ERROR, DEBUG) to the console.
*/

namespace MyEngine
{
    class Log
    {
    public:
        enum class LogLevel
        {
            LEVEL_INFO,
            LEVEL_WARNING,
            LEVEL_ERROR,
            LEVEL_DEBUG
        };

        static void Print(LogLevel level, const std::string& message);
    };
}

#define LOG_DEBUG(message) Log::Print(Log::LogLevel::LEVEL_DEBUG, message)
#define LOG_ERROR(message) Log::Print(Log::LogLevel::LEVEL_ERROR, message)
#define LOG_WARNING(message) Log::Print(Log::LogLevel::LEVEL_WARNING, message)
#define LOG_INFO(message) Log::Print(Log::LogLevel::LEVEL_INFO, message)
