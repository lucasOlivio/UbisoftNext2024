#include "pch.h"

#include "MaterialManagerLocator.h"

namespace MyEngine
{
	NullMaterialManager MaterialManagerLocator::m_nullService = NullMaterialManager();
	iMaterialManager* MaterialManagerLocator::m_materialManager = &(MaterialManagerLocator::m_nullService);

    iMaterialManager* MaterialManagerLocator::Get() { return m_materialManager; }

    void MaterialManagerLocator::Set(iMaterialManager* materialManager)
	{
		if (materialManager == nullptr)
		{
			m_materialManager = &m_nullService;
		}
		else
		{
			m_materialManager = materialManager;
		}
	}
}
