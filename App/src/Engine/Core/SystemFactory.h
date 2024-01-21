#pragma once

#include "Engine/Core/iSystem.h"

#include <string>

namespace MyEngine
{
	class SystemFactory
	{
	public:
		static iSystem* CreateSystem(std::string systemName);
	};
}
