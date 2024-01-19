#pragma once

#include <iostream>

#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif

/*
* Simple helper Log class that facilitates logging messages 
* with different severity levels (INFO, WARNING, ERROR, DEBUG) to the console.
* 
* "Give me a Log class to better print errors and debugs on screen, with different colors" prompt.
* ChatGPT
* https://chat.openai.com/
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

        private:
            enum class ConsoleColor
            {
                RED = 4,
                YELLOW = 6,
                CYAN = 9,
                WHITE = 15
            };

            static void SetConsoleColor(ConsoleColor color);

            static void ResetConsoleColor();
    };
}

#define LOG_DEBUG(message) Log::Print(Log::LogLevel::LEVEL_DEBUG, message)
#define LOG_ERROR(message) Log::Print(Log::LogLevel::LEVEL_ERROR, message)
#define LOG_WARNING(message) Log::Print(Log::LogLevel::LEVEL_WARNING, message)
#define LOG_INFO(message) Log::Print(Log::LogLevel::LEVEL_INFO, message)
