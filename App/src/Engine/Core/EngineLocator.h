#pragma once

#include "Engine/Core/Engine.h"

namespace MyEngine
{
	class EngineLocator
	{
	public:
		static Engine* Get();

		static void Set(Engine* pEngine);

	private:
		static Engine* m_pEngine;
	};
}
