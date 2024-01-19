#include "pch.h"

#include "EntityManager.h"

namespace MyEngine
{
    EntityManager::EntityManager()
    {
        m_liveEntities = {};

        for (Entity entityId = 0; entityId < MAX_ENTITIES; ++entityId) {
            m_availableEntities.push(entityId);
        }
    }

    Entity EntityManager::AddEntity(EntityMask initialMask)
    {
        if (m_availableEntities.empty()) 
        {
            LOG_ERROR("Max entities reached. Unable to add more entities.");
            return -1;
        }

        Entity entityId = m_availableEntities.front();
        m_availableEntities.pop();

        m_masks[entityId] = initialMask;
        m_liveEntities.push_back(entityId);

        return entityId;
    }

    void EntityManager::RemoveEntity(Entity entityId)
    {
        if (entityId < 0 || entityId >= MAX_ENTITIES)
        {
            LOG_WARNING("Invalid entity ID for removal.");
            return;
        }

        auto it = remove(m_liveEntities.begin(), m_liveEntities.end(), entityId);
        m_liveEntities.erase(it, m_liveEntities.end());

        // Reset mask for removed entity and decrease count
        m_masks[entityId].reset();
        m_availableEntities.push(entityId);
    }

    void EntityManager::SetComponent(Entity entityId, ComponentId componentId)
    {
        if (entityId < 0 || entityId >= MAX_ENTITIES)
        {
            LOG_WARNING("Invalid entity ID for setting component.");
            return;
        }

        m_masks[entityId].set(componentId, true);
    }

    void EntityManager::SetMask(Entity entityId, EntityMask newMask)
    {
        if (entityId < 0 || entityId >= MAX_ENTITIES)
        {
            LOG_WARNING("Invalid entity ID for setting mask.");
            return;
        }

        m_masks[entityId] = newMask;
    }

    EntityMask EntityManager::GetMask(Entity entityId)
    {
        if (entityId < 0 || entityId >= MAX_ENTITIES)
        {
            LOG_WARNING("Invalid entity ID for getting mask.");
            return EntityMask();
        }

        return m_masks[entityId];
    }

    bool EntityManager::HasComponent(Entity entityId, ComponentType component)
    {
        // Check if the bit at the specified index is set
        EntityMask mask = GetMask(entityId);
        return mask.test(component);
    }

    bool EntityManager::HasComponents(Entity entityId, const EntityMask& componentMask)
    {
        EntityMask entityMask = GetMask(entityId);

        // Check if all the specified components are set in the entity's mask
        return (entityMask & componentMask) == componentMask;
    }

    const std::vector<Entity>& EntityManager::GetEntities()
    {
        return m_liveEntities;
    }

    size_t EntityManager::Size()
    {
        return m_liveEntities.size();
    }
}
