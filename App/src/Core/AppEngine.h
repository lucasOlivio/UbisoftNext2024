#pragma once

#include "Engine/Core/Engine.h"

namespace MyEngine
{
	class Application : public Engine
	{
	public:
		Application() {}
		virtual ~Application() {}

		virtual void Init();
	};
}
