#pragma once

#include "iConfigSerializer.h"

namespace MyEngine
{
	class ConfigSerializerFactory
	{
	public:
		// Gets the right config reader and writer accordingly to the file type
		static iConfigSerializer* CreateConfigSerializer(std::string fileExt);
	};
}