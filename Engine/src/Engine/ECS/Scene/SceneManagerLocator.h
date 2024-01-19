#pragma once

#include "NullSceneManager.hpp"
#include "iSceneManager.h"

namespace MyEngine
{
	class SceneManagerLocator
	{
	public:
		static iSceneManager* Get();

		static void Set(iSceneManager* pSceneManager);

	private:
		static iSceneManager* m_pSceneManager;
		static NullSceneManager m_nullService;
	};
}
