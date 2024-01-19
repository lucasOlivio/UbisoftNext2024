#include "pch.h"

#include "Scene.h"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
    Scene::Scene()
    {
        m_componentCounter = 0;
        m_pEntityManager = new EntityManager();
    }

    Scene::~Scene()
    {
        delete m_pEntityManager;

        using ComponentMapPair = std::pair<ComponentType, BiMap<Entity, ComponentId>*>;
        for (ComponentMapPair componentMap : m_componentMaps)
        {
            delete componentMap.second;
        }

        using ComponentPoolPair = std::pair<ComponentType, ComponentPool*>;
        for (ComponentPoolPair componentPool : m_componentPools)
        {
            delete componentPool.second;
        }
    }

    Entity Scene::CreateEntity(bool addDefault)
    {
        Entity entityId = m_pEntityManager->AddEntity(EntityMask());

        if (addDefault)
        {
            AddComponent<TransformComponent>(entityId);
        }

        return entityId;
    }

    Entity Scene::CreateEntity(Entity entityId)
    {
        Entity newEntityId = CreateEntity();

        EntityMask entityMask = m_pEntityManager->GetMask(entityId);
        for (int componentType = 0; componentType < entityMask.size(); componentType++)
        {
            if (!entityMask[componentType])
            {
                continue;
            }

            // Check which component it is and add to the new entity
            if (componentType == GetComponentType<TagComponent>())
            {
                TagComponent* pTag = AddComponent<TagComponent>(newEntityId);
                *pTag = *(Get<TagComponent>(entityId));
            }
            else if (componentType == GetComponentType<TransformComponent>())
            {
                TransformComponent* pTransform = AddComponent<TransformComponent>(newEntityId);
                *pTransform = *(Get<TransformComponent>(entityId));
            }
            else if (componentType == GetComponentType<MovementComponent>())
            {
                MovementComponent* pMovement = AddComponent<MovementComponent>(newEntityId);
                *pMovement = *(Get<MovementComponent>(entityId));
            }
            else if (componentType == GetComponentType<RotationComponent>())
            {
                RotationComponent* pRotation = AddComponent<RotationComponent>(newEntityId);
                *pRotation = *(Get<RotationComponent>(entityId));
            }
            else if (componentType == GetComponentType<ParentComponent>())
            {
                ParentComponent* pParent = AddComponent<ParentComponent>(newEntityId);
                *pParent = *(Get<ParentComponent>(entityId));
            }
            else if (componentType == GetComponentType<TextureComponent>())
            {
                TextureComponent* pTexture = AddComponent<TextureComponent>(newEntityId);
                *pTexture = *(Get<TextureComponent>(entityId));
            }
            else if (componentType == GetComponentType<MaterialComponent>())
            {
                MaterialComponent* pMaterial = AddComponent<MaterialComponent>(newEntityId);
                *pMaterial = *(Get<MaterialComponent>(entityId));
            }
            else if (componentType == GetComponentType<LightComponent>())
            {
                LightComponent* pLight = AddComponent<LightComponent>(newEntityId);
                *pLight = *(Get<LightComponent>(entityId));
            }
            else if (componentType == GetComponentType<ModelComponent>())
            {
                ModelComponent* pModel = AddComponent<ModelComponent>(newEntityId);
                *pModel = *(Get<ModelComponent>(entityId));
            }
            else if (componentType == GetComponentType<TilingComponent>())
            {
                TilingComponent* pTiling = AddComponent<TilingComponent>(newEntityId);
                *pTiling = *(Get<TilingComponent>(entityId));
            }
            else if (componentType == GetComponentType<GravityComponent>())
            {
                GravityComponent* pGravity = AddComponent<GravityComponent>(newEntityId);
                *pGravity = *(Get<GravityComponent>(entityId));
            }
            else if (componentType == GetComponentType<RigidBodyComponent>())
            {
                RigidBodyComponent* pRigidBody = AddComponent<RigidBodyComponent>(newEntityId);
                *pRigidBody = *(Get<RigidBodyComponent>(entityId));
            }
            else if (componentType == GetComponentType<MeshColliderComponent>())
            {
                MeshColliderComponent* pMeshCollider = AddComponent<MeshColliderComponent>(newEntityId);
                *pMeshCollider = *(Get<MeshColliderComponent>(entityId));
            }
            else if (componentType == GetComponentType<SphereColliderComponent>())
            {
                SphereColliderComponent* pSphereCollider = AddComponent<SphereColliderComponent>(newEntityId);
                *pSphereCollider = *(Get<SphereColliderComponent>(entityId));
            }
            else if (componentType == GetComponentType<AABBColliderComponent>())
            {
                AABBColliderComponent* pAABBCollider = AddComponent<AABBColliderComponent>(newEntityId);
                *pAABBCollider = *(Get<AABBColliderComponent>(entityId));
            }
        }

        return Entity();
    }

    void Scene::RemoveEntity(Entity entityId)
    {
        m_entitiesToDestroy.push_back(entityId);
    }

    void Scene::DestroyEntities()
    {
        for (Entity entityId : m_entitiesToDestroy)
        {
            // Go through every component the entity have
            EntityMask entityMask = m_pEntityManager->GetMask(entityId);
            for (int componentType = 0; componentType < entityMask.size(); componentType++)
            {
                if (!entityMask[componentType])
                {
                    continue;
                }

                BiMap<Entity, ComponentId>* pComponentMap = m_componentMaps[componentType];
                ComponentPool* pComponentPool = m_componentPools[componentType];

                // Component to remove and new location for moved component
                ComponentId componentId;
                pComponentMap->GetByKey(entityId, componentId);

                // Remove the component from the pool
                ComponentId componentIdOld;
                pComponentPool->Remove(componentId, componentIdOld);

                // Remove the relation mapping
                pComponentMap->RemoveByKey(entityId);

                // Get entity id that had component moved
                Entity entityIdMoved;
                pComponentMap->GetByValue(componentIdOld, entityIdMoved);

                // Update the relation for the moved component
                pComponentMap->Update(entityIdMoved, componentId);
            }

            // Remove entity from entity manager list
            m_pEntityManager->RemoveEntity(entityId);
        }
    }

    EntityManager* Scene::GetEntitymanager()
    {
        return m_pEntityManager;
    }
}
