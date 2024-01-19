#pragma once

#include "Base.h"
#include <queue>
#include <vector>

namespace MyEngine
{
    class EntityManager
    {
    public:
        EntityManager();
        ~EntityManager() {};

        Entity AddEntity(EntityMask initialMask);

        void RemoveEntity(Entity entityId);

        void SetComponent(Entity entityId, ComponentId componentId);

        void SetMask(Entity entityId, EntityMask newMask);

        EntityMask GetMask(Entity entityId);

        // Check if the entity have a specific component type
        bool HasComponent(Entity entityId, ComponentType component);

        // Check if the entity have all needed components
        bool HasComponents(Entity entityId, const EntityMask& componentMask);

        const std::vector<Entity>& GetEntities();

        // # Of live entities
        size_t Size();

    private:
        std::queue<Entity> m_availableEntities;
        std::vector<Entity> m_liveEntities;
        EntityMask m_masks[MAX_ENTITIES];
    };
}