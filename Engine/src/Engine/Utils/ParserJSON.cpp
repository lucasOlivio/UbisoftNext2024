#include "pch.h"

#include "Engine/Utils/ParserJSON.h"

#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

namespace MyEngine
{
#include "ParserJSON.h"

    ParserJSON::ParserJSON()
    {
    }

    ParserJSON::~ParserJSON()
    {
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, std::string& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsString()) {
            valueOut = jsonObject.GetString();
            return true;
        }

        return false;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, const std::string& valueIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        jsonObject.SetString(valueIn.c_str(), static_cast<SizeType>(valueIn.length()), allocator);

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, float& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsNumber()) {
            valueOut = jsonObject.GetFloat();
            return true;
        }

        return false;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, float valueIn)
    {
        using namespace rapidjson;

        jsonObject.SetFloat(valueIn);

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, int& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsInt()) {
            valueOut = jsonObject.GetInt();
            return true;
        }

        return false;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, int valueIn)
    {
        using namespace rapidjson;

        jsonObject.SetInt(valueIn);

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, std::vector<int>& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsArray()) {
            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                if (!jsonObject[i].IsInt()) {
                    return false;
                }
            }


            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                valueOut.push_back(jsonObject[i].GetInt());
            }

            return true;
        }
        return true;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, std::vector<int>& valueIn,
        rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        jsonObject.SetArray();

        for (SizeType i = 0; i < valueIn.size(); i++) {
            Value intVal;
            intVal.SetInt(valueIn[i]);
            jsonObject.PushBack(intVal, allocator);
        }

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, glm::vec3& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsArray() && jsonObject.Size() == 3) {
            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                if (!jsonObject[i].IsFloat()) {
                    return false;
                }
            }


            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                valueOut[i] = jsonObject[i].GetFloat();
            }

            return true;
        }
        return true;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, glm::vec3& valueIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        jsonObject.SetArray();

        for (SizeType i = 0; i < 3; i++) {
            Value floatVal;
            floatVal.SetFloat(valueIn[i]);
            jsonObject.PushBack(floatVal, allocator);
        }

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, glm::vec4& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsArray() && jsonObject.Size() == 4) {
            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                if (!jsonObject[i].IsFloat()) {
                    return false;
                }
            }


            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                valueOut[i] = jsonObject[i].GetFloat();
            }

            return true;
        }
        return true;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, glm::vec4& valueIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        jsonObject.SetArray();

        for (SizeType i = 0; i < 4; i++) {
            Value floatVal;
            floatVal.SetFloat(valueIn[i]);
            jsonObject.PushBack(floatVal, allocator);
        }

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, glm::quat& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsArray() && jsonObject.Size() == 4) {
            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                if (!jsonObject[i].IsFloat()) {
                    return false;
                }
            }


            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                valueOut[i] = jsonObject[i].GetFloat();
            }

            return true;
        }
        return true;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, glm::quat& valueIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        jsonObject.SetArray();

        for (SizeType i = 0; i < 4; i++) {
            Value floatVal;
            floatVal.SetFloat(valueIn[i]);
            jsonObject.PushBack(floatVal, allocator);
        }

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, bool& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsBool()) {
            valueOut = jsonObject.GetBool();
            return true;
        }

        if (jsonObject.IsInt()) {
            valueOut = (bool)jsonObject.GetInt();
            return true;
        }

        return false;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, bool valueIn)
    {
        using namespace rapidjson;

        jsonObject.SetBool(valueIn);

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, std::vector<std::string>& valueOut)
    {
        using namespace rapidjson;

        if (jsonObject.IsArray()) {
            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                if (!jsonObject[i].IsString()) {
                    return false;
                }
            }


            for (SizeType i = 0; i < jsonObject.Size(); i++) {
                valueOut.push_back(jsonObject[i].GetString());
            }

            return true;
        }

        return false;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject,
        const std::vector<std::string>& valueIn,
        rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        jsonObject.SetArray();

        for (SizeType i = 0; i < valueIn.size(); i++) {
            Value strVal;
            strVal.SetString(valueIn[i].c_str(), allocator);
            jsonObject.PushBack(strVal, allocator);
        }

        return true;
    }

    bool ParserJSON::GetValue(rapidjson::Value& jsonObject, std::map<std::string, std::string>& valueOut)
    {
        using namespace rapidjson;
        if (!jsonObject.IsObject())
        {
            return false;
        }

        for (Value::ConstMemberIterator member = jsonObject.MemberBegin(); member != jsonObject.MemberEnd(); ++member)
        {
            std::string key;
            std::string value;

            if (!member->name.IsString() || !member->value.IsString())
            {
                return false;
            }

            key = member->name.GetString();
            value = member->value.GetString();

            valueOut[key] = value;
        }

        return true;
    }

    bool ParserJSON::SetValue(rapidjson::Value& jsonObject, const std::map<std::string, std::string>& valueIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        if (!jsonObject.IsObject())
        {
            return false;
        }

        for (auto& valuePair : valueIn)
        {
            // Create Value objects for langKey and langFile
            Value key(valuePair.first.c_str(), allocator);
            Value value(valuePair.second.c_str(), allocator);

            // Add the key-value pair to object
            jsonObject.AddMember(key, value, allocator);
        }

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, std::string value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue(value.c_str(), allocator);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, int value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue(value);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, float value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue(value);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, const std::map<std::string, std::string>& value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;
        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue;
        memberValue.SetObject();
        this->SetValue(memberValue, value, allocator);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, std::vector<int>& value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;
        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue;
        memberValue.SetObject();
        this->SetValue(memberValue, value, allocator);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, glm::vec3& value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;
        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue;
        memberValue.SetObject();
        this->SetValue(memberValue, value, allocator);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, glm::vec4& value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;
        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue;
        memberValue.SetObject();
        this->SetValue(memberValue, value, allocator);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, glm::quat& value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;
        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue;
        memberValue.SetObject();
        this->SetValue(memberValue, value, allocator);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }

    bool ParserJSON::SetMember(rapidjson::Value& jsonObject, std::string key, std::vector<std::string>& value, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;
        if (!jsonObject.IsObject())
        {
            return false;
        }

        Value memberKey(key.c_str(), allocator);
        Value memberValue;
        memberValue.SetObject();
        this->SetValue(memberValue, value, allocator);
        jsonObject.AddMember(memberKey, memberValue, allocator);

        return true;
    }
}
