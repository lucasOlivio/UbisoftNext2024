#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class DebugLocator
	{
	public:
		static ConsoleComponent* GetConsole();

		static void SetConsole(ConsoleComponent* pConsole);

		static void Clear();

	private:
		static ConsoleComponent* m_pConsole;
	};
}
