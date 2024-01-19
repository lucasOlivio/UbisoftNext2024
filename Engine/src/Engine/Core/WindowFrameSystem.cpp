#include "pch.h"

#include "WindowFrameSystem.h"

#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

namespace MyEngine
{
	void WindowFrameSystem::Init()
	{
	}

	void WindowFrameSystem::Start(Scene* pScene)
	{
		FrameCounterComponent* pFrame = CoreLocator::GetFrameCounter();

		pFrame->frameCount = 0;

		pFrame->fpsTimer = 0;
	}

	void WindowFrameSystem::Update(Scene* pScene, float deltaTime)
	{
		FrameCounterComponent* pFrame = CoreLocator::GetFrameCounter();

		pFrame->frameCount++;

		pFrame->fpsTimer += deltaTime;

		// Update Frame every second in the title
		if (pFrame->fpsTimer >= 1.0f)
		{
			pFrame->fps = (float)(pFrame->frameCount) / pFrame->fpsTimer;

			// Update window name
			WindowComponent* pWindow = GraphicsLocator::GetWindow();
			pWindow->name = std::to_string(pFrame->fps);

			pFrame->frameCount = 0;
			pFrame->fpsTimer = 0.0f;
		}
	}

	void WindowFrameSystem::Render(Scene* pScene)
	{
	}

	void WindowFrameSystem::End(Scene* pScene)
	{
	}

	void WindowFrameSystem::Shutdown()
	{
	}
}
