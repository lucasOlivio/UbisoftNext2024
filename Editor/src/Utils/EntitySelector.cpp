#include "EntitySelector.h"

namespace MyEngine
{
    // Entity 0 should always be the empty config
    Entity EntitySelector::m_selectedEntity = 1;

    EntitySelector::EntitySelector()
    {
    }

    EntitySelector::~EntitySelector()
    {
    }

    Entity EntitySelector::GetSelectedEntity()
    {
        return m_selectedEntity;
    }

    Entity EntitySelector::NextEntity(Scene* pScene)
    {
        // Check if new selected entity exists and has components, else just go to next until finds one
        EntityManager* pEntityManager = pScene->GetEntitymanager();

        if (pEntityManager->Size() == 1)
        {
            return 0;
        }

        m_selectedEntity++;

        if (m_selectedEntity >= pEntityManager->Size())
        {
            m_selectedEntity = 1;
        }

        EntityMask mask = pEntityManager->GetMask(m_selectedEntity);
        if (mask == EntityMask())
        {
            m_selectedEntity = PrevEntity(pScene);
        }

        return m_selectedEntity;
    }

    Entity EntitySelector::PrevEntity(Scene* pScene)
    {
        // Check if new selected entity exists and has components, else just go to next until finds one
        EntityManager* pEntityManager = pScene->GetEntitymanager();

        if (pEntityManager->Size() == 1)
        {
            return 0;
        }

        m_selectedEntity--;

        if (m_selectedEntity <= 0)
        {
            m_selectedEntity = (Entity)pEntityManager->Size() - 1;
        }

        EntityMask mask = pEntityManager->GetMask(m_selectedEntity);
        if (mask == EntityMask())
        {
            m_selectedEntity = PrevEntity(pScene);
        }

        return m_selectedEntity;
    }

    void EntitySelector::SetSelectedEntity(Entity entityId)
    {
        m_selectedEntity = entityId;
    }
}
