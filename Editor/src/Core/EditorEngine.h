#pragma once

#include "Engine/Core/Engine.h"
#include "Core/AppEngine.h"

namespace MyEngine
{
	class Editor : public Engine
	{
	public:
		Editor() {}
		virtual ~Editor() {}

		virtual void Init();
	};
}
