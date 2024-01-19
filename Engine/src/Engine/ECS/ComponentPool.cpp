#include "pch.h"

#include "ComponentPool.h"

namespace MyEngine
{
    ComponentPool::ComponentPool(size_t elementSize) :
        m_elementSize(elementSize)
    {
        // Allocate memory for the component pool
        m_size = 0;
        m_pData = new char[m_elementSize * MAX_ENTITIES];
    }

    ComponentPool::~ComponentPool()
    {
        // Deallocate memory
        delete[] m_pData;
    }

    void* ComponentPool::Get(ComponentId componentId)
    {
        if (componentId >= m_size)
        {
            LOG_WARNING("Invalid component id for get in pool.");
            return nullptr;
        }

        return m_pData + componentId * m_elementSize;
    }

    void ComponentPool::Remove(ComponentId componentId, ComponentId& componentIdReplaceOut)
    {
        if (componentId >= m_size)
        {
            LOG_WARNING("Invalid component id for remove in pool.");
            return;
        }

        // Minus 1 active component
        --m_size;
        componentIdReplaceOut = (ComponentId)m_size;

        if (m_size < 1 || componentId == m_size)
        {
            // No more active components
            return;
        }

        // Move the last component to the position of the deleted component
        char* lastComponent = m_pData + m_size * m_elementSize;
        char* removedComponent = m_pData + componentId * m_elementSize;
        std::memcpy(removedComponent, lastComponent, m_elementSize);
    }

    void* ComponentPool::Add(ComponentId& componentIdOut)
    {
        componentIdOut = (ComponentId)m_size;

        // Get last address of active components in array
        void* mem = m_pData + m_size * m_elementSize;

        // More 1 active component
        ++m_size;

        return mem;
    }
    size_t ComponentPool::Size()
    {
        return m_size;
    }
}
