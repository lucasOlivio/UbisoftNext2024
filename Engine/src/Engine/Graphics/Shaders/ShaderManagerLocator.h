#pragma once

#include "NullShaderManager.hpp"
#include "iShaderManager.h"

namespace MyEngine
{
	class ShaderManagerLocator
	{
	public:
		static iShaderManager* Get();

		static void Set(iShaderManager* pShaderManager);

	private:
		static iShaderManager* m_shaderManager;
		static NullShaderManager m_nullService;
	};
}
