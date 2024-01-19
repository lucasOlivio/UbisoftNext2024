#pragma once

#include "NullVAOManager.hpp"
#include "iVAOManager.h"

namespace MyEngine
{
	class VAOManagerLocator
	{
	public:
		static iVAOManager* Get();

		static void Set(iVAOManager* pVAOManager);

	private:
		static iVAOManager* m_pVAOManager;
		static NullVAOManager m_nullService;
	};
}
