#include "stdafx.h"

#include "FrameSystem.h"

#include "Engine/ECS/SingletonComponents/CoreLocator.h"

namespace MyEngine
{
	void FrameSystem::Init()
	{
	}

	void FrameSystem::Start(Scene* pScene)
	{
		FrameCounterComponent* pFrame = CoreLocator::GetFrameCounter();
		pFrame->frameCount = 0;
		pFrame->fpsTimer = 0;
	}

	void FrameSystem::Update(Scene* pScene, float deltaTime)
	{
		deltaTime = deltaTime / 1000.0f;
		FrameCounterComponent* pFrame = CoreLocator::GetFrameCounter();
		pFrame->frameCount++;
		pFrame->fpsTimer += deltaTime;

		// keeping track of FPS
		if (pFrame->fpsTimer >= 1.0f)
		{
			pFrame->fps = (float)(pFrame->frameCount) / pFrame->fpsTimer;

			pFrame->frameCount = 0;
			pFrame->fpsTimer = 0.0f;

			LOG_INFO("FPS: " + std::to_string(pFrame->fps));
		}
	}

	void FrameSystem::Render(Scene* pScene)
	{
	}

	void FrameSystem::End(Scene* pScene)
	{
	}

	void FrameSystem::Shutdown()
	{
	}
}
