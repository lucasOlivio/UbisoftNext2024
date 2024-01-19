#include "pch.h"

#include "SceneManagerLocator.h"

namespace MyEngine
{
	NullSceneManager SceneManagerLocator::m_nullService = NullSceneManager();
	iSceneManager* SceneManagerLocator::m_pSceneManager = &(SceneManagerLocator::m_nullService);

	iSceneManager* SceneManagerLocator::Get()
	{
		return m_pSceneManager;
	}

	void SceneManagerLocator::Set(iSceneManager* pSceneManager)
	{
		if (pSceneManager == nullptr)
		{
			m_pSceneManager = &m_nullService;
		}
		else
		{
			m_pSceneManager = pSceneManager;
		}
	}
}
