#include <iostream>
#include <unordered_map>

// Bidirectional map key <-> value

namespace MyEngine
{
    template <typename KeyType, typename ValueType>
    class BiMap
    {
    public:
        void Add(const KeyType& key, const ValueType& value) 
        {
            m_mainMap[key] = value;
            m_inverseMap[value] = key;
        }

        void RemoveByKey(const KeyType& key)
        {
            auto it = m_mainMap.find(key);
            if (it != m_mainMap.end()) {
                m_inverseMap.erase(it->second);
                m_mainMap.erase(it);
            }
        }

        void RemoveByValue(const ValueType& value)
        {
            auto it = m_inverseMap.find(value);
            if (it != m_inverseMap.end()) {
                m_mainMap.erase(it->second);
                m_inverseMap.erase(it);
            }
        }

        // Returns true if key is in maps and the value
        bool GetByKey(const KeyType& key, ValueType& valueOut) const
        {
            auto it = m_mainMap.find(key);

            if (it == m_mainMap.end())
            {
                valueOut = ValueType();
                return false;
            }

            valueOut = it->second;
            return true;
        }

        // Returns true if value is in maps and the key
        bool GetByValue(const ValueType& value, KeyType& keyOut) const
        {
            auto it = m_inverseMap.find(value);

            if (it == m_inverseMap.end())
            {
                keyOut = KeyType();
                return false;
            }

            keyOut = it->second;
            return true;
        }

        // Remove from existing mappings and add new entry
        void Update(const KeyType& key, const ValueType& value)
        {
            RemoveByKey(key);

            Add(key, value);
        }

        void Clear()
        {
            m_mainMap.clear();
            m_inverseMap.clear();
        }

    private:
        std::unordered_map<KeyType, ValueType> m_mainMap;
        std::unordered_map<ValueType, KeyType> m_inverseMap;
    };
}
