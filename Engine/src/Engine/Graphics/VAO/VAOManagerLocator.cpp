#include "pch.h"

#include "VAOManagerLocator.h"

namespace MyEngine
{
	NullVAOManager VAOManagerLocator::m_nullService = NullVAOManager();
	iVAOManager* VAOManagerLocator::m_pVAOManager = &(VAOManagerLocator::m_nullService);

	iVAOManager* VAOManagerLocator::Get()
    {
        return m_pVAOManager;
    }

    void VAOManagerLocator::Set(iVAOManager* pVAOManager)
    {
		if (pVAOManager == nullptr)
		{
			m_pVAOManager = &m_nullService;
		}
		else
		{
			m_pVAOManager = pVAOManager;
		}
    }
}
