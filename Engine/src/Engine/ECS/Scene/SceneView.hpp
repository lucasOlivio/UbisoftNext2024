#pragma once

#include "Engine/ECS/Base.h"

#include "Scene.h"

namespace MyEngine
{
    // Iterator to facilitate for the systems to go only through the needed components
    // Ref: https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html
    template<typename... ComponentTypes>
    class SceneView
    {
    public:
        SceneView(Scene& scene)
        {
            m_pEntityManager = scene.GetEntitymanager();

            if (sizeof...(ComponentTypes) == 0)
            {
                // Skip checking components and iterate over all entities
                m_all = true;
            }
            else
            {
                // Unpack the template parameters into an initializer list
                int componentIds[] = { 0, scene.GetComponentType<ComponentTypes>() ... };
                for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
                    m_mask.set(componentIds[i]);
            }
        }

        class Iterator
        {
        public:
            Iterator(EntityManager* pEntityManager, 
                     std::vector<Entity>::const_iterator it,
                     EntityMask mask, bool all)
                : m_pEntityManager(pEntityManager), m_it(it), m_mask(mask), m_all(all)
            {}

            Entity operator*() const
            {
                // give back the entity we're currently at
                return *m_it;
            }

            bool operator==(const Iterator& other) const
            {
                return m_it == other.m_it;
            }

            bool operator!=(const Iterator& other) const
            {
                return m_it != other.m_it;
            }

            Iterator& operator++()
            {
                const std::vector<Entity>& entities = m_pEntityManager->GetEntities();
                do
                {
                    m_it++;
                } while (m_it != entities.end() && 
                        !(m_all || m_pEntityManager->HasComponents(*m_it, m_mask)));

                return *this;
            }

        private:
            std::vector<Entity>::const_iterator m_it;
            EntityManager* m_pEntityManager;
            EntityMask m_mask;
            bool m_all{ false };
        };

        const Iterator begin() const
        {
            const std::vector<Entity>& entities = m_pEntityManager->GetEntities();
            // Give an iterator to the beginning of this components group
            std::vector<Entity>::const_iterator firstIt = entities.begin();
            while (firstIt != entities.end() &&
                    !(m_all || m_pEntityManager->HasComponents(*firstIt, m_mask)))
            {
                firstIt++;
            }
            return Iterator(m_pEntityManager, firstIt, m_mask, m_all);
        }

        const Iterator end() const
        {
            // Give an iterator to the end of this view 
            const std::vector<Entity>& entities = m_pEntityManager->GetEntities();
            return Iterator(m_pEntityManager, entities.end(), m_mask, m_all);
        }

    private:
        EntityManager* m_pEntityManager{ nullptr };
        EntityMask m_mask;
        bool m_all{ false };
    };
}
