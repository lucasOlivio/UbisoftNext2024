#include "stdafx.h"

#include "Log.h"

#include "Engine/ECS/SingletonComponents/CoreLocator.h"

namespace MyEngine
{
    void Log::Print(LogLevel level, const std::string& message)
    {
        const int MAX_CONSOLE_LINES = 10;
        ConsoleComponent* pConsole = CoreLocator::GetConsole();

        std::string flag = "";
        float color[] = { 1.0f, 1.0f, 1.0f };
        switch (level)
        {
        case LogLevel::LEVEL_INFO:
            // WHITE
            flag = "[INFO] ";
            break;
        case LogLevel::LEVEL_WARNING:
            color[0] = YELLOW[0];
            color[1] = YELLOW[1];
            color[2] = YELLOW[2];
            flag = "[WARNING] ";
            break;
        case LogLevel::LEVEL_ERROR:
            color[0] = RED[0];
            color[1] = RED[1];
            color[2] = RED[2];
            flag = "[ERROR] ";
            break;
        case LogLevel::LEVEL_DEBUG:
            color[0] = BLUE[0];
            color[1] = BLUE[1];
            color[2] = BLUE[2];
            flag = "[DEBUG] ";
            break;
        }

        ConsoleComponent::Line line = ConsoleComponent::Line();
        line.color[0] = color[0];
        line.color[1] = color[1];
        line.color[2] = color[2];
        line.txt = flag + message;

        pConsole->lines.push(line);

        // Keep console at MAX_CONSOLE_LINES lines
        while (pConsole->lines.size() > MAX_CONSOLE_LINES)
        {
            pConsole->lines.pop();
        }
    }
}
