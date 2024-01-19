#pragma once

#include <string>
#include <vector>
#include <map>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <rapidjson/document.h>

namespace MyEngine
{
	class ParserJSON
	{
	public:
		ParserJSON();
		~ParserJSON();

		bool GetValue(rapidjson::Value& jsonObject, std::string& valueOut);
		bool SetValue(rapidjson::Value& jsonObject,
			const std::string& valueIn,
			rapidjson::Document::AllocatorType& allocator);

		bool GetValue(rapidjson::Value& jsonObject, float& valueOut);
		bool SetValue(rapidjson::Value& jsonObject, float valueIn);

		bool GetValue(rapidjson::Value& jsonObject, int& valueOut);
		bool SetValue(rapidjson::Value& jsonObject, int valueIn);

		bool GetValue(rapidjson::Value& jsonObject, std::vector<int>& valueOut);
		bool SetValue(rapidjson::Value& jsonObject, std::vector<int>& valueIn,
			rapidjson::Document::AllocatorType& allocator);

		bool GetValue(rapidjson::Value& jsonObject, glm::vec3& valueOut);
		bool SetValue(rapidjson::Value& jsonObject, glm::vec3& valueIn,
			rapidjson::Document::AllocatorType& allocator);

		bool GetValue(rapidjson::Value& jsonObject, glm::vec4& valueOut);
		bool SetValue(rapidjson::Value& jsonObject, glm::vec4& valueIn,
			rapidjson::Document::AllocatorType& allocator);

		bool GetValue(rapidjson::Value& jsonObject, glm::quat& valueOut);
		bool SetValue(rapidjson::Value& jsonObject, glm::quat& valueIn,
			rapidjson::Document::AllocatorType& allocator);

		bool GetValue(rapidjson::Value& jsonObject, bool& valueOut);
		bool SetValue(rapidjson::Value& jsonObject, bool valueIn);

		bool GetValue(rapidjson::Value& jsonObject, std::vector<std::string>& valueOut);
		bool SetValue(rapidjson::Value& jsonObject,
			const std::vector<std::string>& valueIn,
			rapidjson::Document::AllocatorType& allocator);

		bool GetValue(rapidjson::Value& jsonObject, std::map<std::string, std::string>& valueOut);
		bool SetValue(rapidjson::Value& jsonObject,
			const std::map<std::string, std::string>& valueIn,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key, std::string value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key, int value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key, float value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key,
			const std::map<std::string, std::string>& value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key, std::vector<int>& value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key, glm::vec3& value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key, glm::vec4& value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key, glm::quat& value,
			rapidjson::Document::AllocatorType& allocator);

		bool SetMember(rapidjson::Value& jsonObject, std::string key,
			std::vector<std::string>& value,
			rapidjson::Document::AllocatorType& allocator);

	};
}
