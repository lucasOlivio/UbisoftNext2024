#include "pch.h"

#include "ShaderManagerLocator.h"

namespace MyEngine
{
	NullShaderManager ShaderManagerLocator::m_nullService = NullShaderManager();
	iShaderManager* ShaderManagerLocator::m_shaderManager = &(ShaderManagerLocator::m_nullService);

	iShaderManager* ShaderManagerLocator::Get() { return m_shaderManager; }

	void ShaderManagerLocator::Set(iShaderManager* pShaderManager)
	{
		if (pShaderManager == nullptr)
		{
			m_shaderManager = &m_nullService;
		}
		else
		{
			m_shaderManager = pShaderManager;
		}
	}
}
