#pragma once

#include "Engine/ECS/EntityManager.h"
#include "Engine/ECS/ComponentPool.h"

#include "Engine/Utils/BiMap.hpp"

namespace MyEngine
{
    class Scene 
    {
    public:
        Scene();
        ~Scene();

        // Create an entity using the EntityManager
        // addDefault = Add default components (Transform) to it
        Entity CreateEntity(bool addDefault = false);
        // entityId = Entity to duplicate the components from
        Entity CreateEntity(Entity entityId);

        // Flag entity to be deleted later on a safer time
        void RemoveEntity(Entity entityId);

        // Unique ID for each component type
        template <class T>
        ComponentType GetComponentType()
        {
            static int componentType = m_componentCounter++;
            return componentType;
        }

        // Add new component to entity and return the instance
        template <typename T>
        T* AddComponent(Entity entityId)
        {
            ComponentType componentType = GetComponentType<T>();

            if (m_componentPools.find(componentType) == m_componentPools.end())
            {
                // New component type, make a new pool
                m_componentPools[componentType] = new ComponentPool(sizeof(T));
                m_componentMaps[componentType] = new BiMap<Entity, ComponentId>();
            }

            T* pComponent = Get<T>(entityId);
            if (pComponent != nullptr)
            {
                // Entity already have component, so just return it
                return pComponent;
            }

            // Looks up the component id and mem location in the pool, 
            // and initializes it with placement new
            ComponentId componentId;
            void* mem = m_componentPools[componentType]->Add(componentId);
            pComponent = new (mem) T();

            // Set the relation between the component id and the entity id
            m_componentMaps[componentType]->Add(entityId, componentId);

            // Add component to the entity mask and return the created component
            m_pEntityManager->SetComponent(entityId, componentType);

            return pComponent;
        }

        // Get an entity component using the BiMap and ComponentPool
        template<typename T>
        T* Get(Entity entityId)
        {
            if (m_componentCounter < 0)
            {
                return nullptr;
            }

            ComponentType componentType = GetComponentType<T>();

            if (m_componentPools.find(componentType) == m_componentPools.end())
            {
                return nullptr;
            }

            ComponentId componentId;
            bool hasComponent = m_componentMaps[componentType]->GetByKey(entityId, 
                                                                         componentId);

            if (!hasComponent)
                return nullptr;

            T* pComponent = static_cast<T*>(m_componentPools[componentType]->Get(componentId));
            return pComponent;
        }

        int GetComponentCount()
        {
            return (int)m_componentMaps.size();
        }

        // TODO: This should be more encapsulated, to make sure we only call
        // this in the end of the frame.
        // 
        // Really removes and destroy all pending entities and its components
        void DestroyEntities();


        // TODO: This should also be more encapsulated, but couln't find a way to 
        // let it open only for sceneview class since its a template class
        EntityManager* GetEntitymanager();

    private:
        EntityManager* m_pEntityManager;
        std::unordered_map<ComponentType, BiMap<Entity, ComponentId>*> m_componentMaps;
        std::unordered_map<ComponentType, ComponentPool*> m_componentPools;
        
        int m_componentCounter;

        std::vector<Entity> m_entitiesToDestroy;
    };
}