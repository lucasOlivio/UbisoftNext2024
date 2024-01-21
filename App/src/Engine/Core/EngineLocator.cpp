#include "stdafx.h"

#include "EngineLocator.h"

namespace MyEngine
{
	Engine* EngineLocator::m_pEngine = nullptr;

	Engine* EngineLocator::Get() { return m_pEngine; }

	void EngineLocator::Set(Engine* pEngine)
	{
		m_pEngine = pEngine;
	}
}