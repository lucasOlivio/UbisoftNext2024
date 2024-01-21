#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class CoreLocator
	{
	public:
		static FrameCounterComponent* GetFrameCounter();

		static void SetFrameCounter(FrameCounterComponent* pFrameCounter);

		static void Clear();

	private:
		static FrameCounterComponent* m_pFrameCounter;
	};
}
