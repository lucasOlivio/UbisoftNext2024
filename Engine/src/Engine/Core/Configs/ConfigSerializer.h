#pragma once

namespace MyEngine {

	class ConfigSerializer
	{
	public:
		ConfigSerializer();

		bool Serialize(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
	};

}
