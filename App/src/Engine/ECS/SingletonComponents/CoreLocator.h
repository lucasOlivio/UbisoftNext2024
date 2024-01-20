#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class CoreLocator
	{
	public:
		static FrameCounterComponent* GetFrameCounter();
		static ConsoleComponent* GetConsole();

		static void SetFrameCounter(FrameCounterComponent* pFrameCounter);
		static void SetConsole(ConsoleComponent* pConsole);

		static void Clear();

	private:
		static FrameCounterComponent* m_pFrameCounter;
		static ConsoleComponent* m_pConsole;
	};
}
