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
            Iterator(EntityManager* pEntityManager, size_t index, EntityMask mask, bool all)
                : m_pEntityManager(pEntityManager), m_index(index), m_mask(mask), m_all(all)
            {}

            Entity operator*() const
            {
                return m_pEntityManager->GetEntities().at(m_index);
            }

            bool operator==(const Iterator& other) const
            {
                return m_index == other.m_index || m_index == m_pEntityManager->GetEntities().size();
            }

            bool operator!=(const Iterator& other) const
            {
                return m_index != other.m_index && m_index != m_pEntityManager->GetEntities().size();
            }

            Iterator& operator++()
            {
                const std::vector<Entity>& entities = m_pEntityManager->GetEntities();
                // Next entity with correct mask
                do
                {
                    m_index++;
                } while (m_index < entities.size() &&
                        !(m_all || m_pEntityManager->HasComponents(entities[m_index], m_mask)));

                return *this;
            }

        private:
            size_t m_index;
            EntityManager* m_pEntityManager{ nullptr };
            EntityMask m_mask;
            bool m_all{ false };
        };

        const Iterator begin() const
        {
            const std::vector<Entity>& entities = m_pEntityManager->GetEntities();

            // Find first entity with correct mask
            int firstIndex = 0;
            while (firstIndex != entities.size() &&
                   !(m_all || m_pEntityManager->HasComponents(entities[firstIndex], m_mask)))
            {
                firstIndex++;
            }

            return Iterator(m_pEntityManager, firstIndex, m_mask, m_all);
        }

        const Iterator end() const
        {
            // Give an iterator to the end of this view 
            return Iterator(m_pEntityManager, m_pEntityManager->GetEntities().size(), m_mask, m_all);
        }

    protected:
        EntityManager* m_pEntityManager{ nullptr };
        EntityMask m_mask;
        bool m_all{ false };
    };
}
