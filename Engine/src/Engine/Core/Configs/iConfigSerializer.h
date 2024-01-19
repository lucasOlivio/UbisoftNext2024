#pragma once

#include <string>

namespace MyEngine
{
	class iConfigSerializer
	{
	public:
		virtual ~iConfigSerializer() {};

		virtual bool DeserializeConfig(const std::string& filePath) = 0;

		virtual bool SerializeConfig(const std::string& filePath) = 0;
	};
}