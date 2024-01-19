#include "pch.h"

#include "SortTransparentsSystem.h"
#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/Graphics/Materials/MaterialManagerLocator.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

namespace MyEngine
{
    void SortTransparentsSystem::Init()
    {
    }

    void SortTransparentsSystem::Start(Scene* pScene)
    {
        iMaterialManager* pMaterialManager = MaterialManagerLocator::Get();
        TransparentEntitiesComponent* pTransparents = GraphicsLocator::GetTransparentEntities();

        for (Entity entityId : SceneView<TransformComponent, ModelComponent>(*pScene))
        {
            ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);

            // Check for material
            MaterialComponent* pMaterial = pMaterialManager->GetMaterialByName(pScene,
                                                                               pModel->material);
            if (!pMaterial || !pMaterial->useAlphaTexture)
            {
                continue;
            }

            // TODO: Events to add and destroy entity, so we can add this and remove 
            // when an entity is created or destroied
            // 
            // Material is transparent, so we add to list
            pTransparents->entities.push_back(entityId);
        }
    }

    void SortTransparentsSystem::Update(Scene* pScene, float deltaTime)
    {
        TransparentEntitiesComponent* pTransparents = GraphicsLocator::GetTransparentEntities();
        CameraComponent* pCamera = GraphicsLocator::GetCamera();

        // Update distance to camera
        for (Entity entity : pTransparents->entities)
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entity);

            float distToCamera = glm::distance(pTransform->worldPosition, pCamera->position);
            pTransform->distToCamera = distToCamera;
        }

        // Sort from more distant, to closer
        std::sort(pTransparents->entities.begin(), pTransparents->entities.end(), CheckCloser(pScene));
    }

    void SortTransparentsSystem::Render(Scene* pScene)
    {
    }

    void SortTransparentsSystem::End(Scene* pScene)
    {
        TransparentEntitiesComponent* pTransparents = GraphicsLocator::GetTransparentEntities();
        pTransparents->entities.clear();
    }

    void SortTransparentsSystem::Shutdown()
    {
    }
    bool CheckCloser::operator()(Entity entityA, Entity entityB)
    {
        TransformComponent* pTransformA = m_pScene->Get<TransformComponent>(entityA);
        TransformComponent* pTransformB = m_pScene->Get<TransformComponent>(entityA);

        return pTransformA->distToCamera > pTransformB->distToCamera;
    }
}
