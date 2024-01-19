#pragma once

#include "Base.h"

namespace MyEngine
{
    class ComponentPool
    {
    public:
        ComponentPool(size_t elementSize);

        ~ComponentPool();

        // Get a component from the pool based on its index
        void* Get(ComponentId componentId);

        // Remove component at index from the pool 
        // and replace it with last component to mantain array density.
        // Returns the component index that replaced the removed one
        void Remove(ComponentId componentId, ComponentId& componentIdReplaceOut);

        // Return the next location to put the new component, its index location
        // and increases pool size.
        // This should only be used when a component is added in the given address,
        // or else this address will return an invalid component later.
        void* Add(ComponentId& componentIdOut);

        size_t Size();

    private:
        char* m_pData;        // Compact array of char* to hold any component type
        size_t m_size;        // # of active components in array
        size_t m_elementSize; // Size of the component been managed
    };
}
