#include "stdafx.h"

#include "ConsoleSystem.h"

#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/DebugLocator.h"

#include <app.h>

namespace MyEngine
{
    void ConsoleSystem::Init()
    {
    }

    void ConsoleSystem::Start(Scene* pScene)
    {
    }

    void ConsoleSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void ConsoleSystem::Render(Scene* pScene)
    {
        const float LINE_SPACING = 30.0f;
        ConsoleComponent* pConsole = DebugLocator::GetConsole();

        std::queue< ConsoleComponent::Line> lines = pConsole->lines;

        // Iterate through the console lines and print each line
        float x = 10.0f;
        float y = 80.0f;
        while (!lines.empty())
        {
            ConsoleComponent::Line line = lines.front();

            // Get the front of the queue
            const char* lineTxt = line.txt.c_str();
            float lineColor[3] = { line .color[0], line.color[1] , line.color[2] };

            App::Print(x, y, lineTxt, lineColor[0], lineColor[1], lineColor[2]);

            y += LINE_SPACING;

            lines.pop();
        }
    }

    void ConsoleSystem::End(Scene* pScene)
    {
    }

    void ConsoleSystem::Shutdown()
    {
    }
}
