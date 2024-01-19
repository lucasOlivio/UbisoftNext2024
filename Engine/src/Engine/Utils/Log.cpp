#include "pch.h"

#include "Log.h"

namespace MyEngine
{
    void Log::Print(LogLevel level, const std::string& message)
    {
        switch (level)
        {
        case LogLevel::LEVEL_INFO:
            SetConsoleColor(ConsoleColor::WHITE);
            std::cout << "[INFO] ";
            break;
        case LogLevel::LEVEL_WARNING:
            SetConsoleColor(ConsoleColor::YELLOW);
            std::cout << "[WARNING] ";
            break;
        case LogLevel::LEVEL_ERROR:
            SetConsoleColor(ConsoleColor::RED);
            std::cerr << "[ERROR] ";
            break;
        case LogLevel::LEVEL_DEBUG:
            SetConsoleColor(ConsoleColor::CYAN);
            std::cout << "[DEBUG] ";
            break;
        }

        // Reset color after printing the level
        ResetConsoleColor();

        // Print the actual message
        std::cout << message << std::endl;
    }

    void Log::SetConsoleColor(ConsoleColor color)
    {
#if defined(_WIN32)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
#else
        const char* ansiColorCode = "\033[0;"; // Reset color
        switch (color)
        {
        case ConsoleColor::BLACK:
            ansiColorCode = "\033[0;30m";
            break;
        case ConsoleColor::RED:
            ansiColorCode = "\033[0;31m";
            break;
        case ConsoleColor::GREEN:
            ansiColorCode = "\033[0;32m";
            break;
        case ConsoleColor::YELLOW:
            ansiColorCode = "\033[0;33m";
            break;
        case ConsoleColor::BLUE:
            ansiColorCode = "\033[0;34m";
            break;
        case ConsoleColor::MAGENTA:
            ansiColorCode = "\033[0;35m";
            break;
        case ConsoleColor::CYAN:
            ansiColorCode = "\033[0;36m";
            break;
        case ConsoleColor::WHITE:
            ansiColorCode = "\033[0;37m";
            break;
        }

        std::cout << ansiColorCode;
#endif
    }

    void Log::ResetConsoleColor()
    {
        SetConsoleColor(ConsoleColor::WHITE);
    }
}
