#pragma once

#include "NullMaterialManager.hpp"
#include "iMaterialManager.h"

namespace MyEngine
{
	class MaterialManagerLocator
	{
	public:
		static iMaterialManager* Get();

		static void Set(iMaterialManager* materialManager);

	private:
		static iMaterialManager* m_materialManager;
		static NullMaterialManager m_nullService;
	};
}
