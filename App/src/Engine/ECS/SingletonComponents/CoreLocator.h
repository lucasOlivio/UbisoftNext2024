#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class CoreLocator
	{
	public:
		static FrameCounterComponent* GetFrameCounter();
		static StateComponent* GetState();

		static void SetFrameCounter(FrameCounterComponent* pFrameCounter);
		static void SetState(StateComponent* pState);

		static void Clear();

	private:
		static FrameCounterComponent* m_pFrameCounter;
		static StateComponent* m_pState;
	};
}
