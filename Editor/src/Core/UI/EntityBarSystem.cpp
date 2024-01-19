#include "pch.h"

#include "EntityBarSystem.h"

#include "Utils/EntitySelector.h"
#include "Utils/ComponentUI.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/Scene/SceneManagerLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Utils/Files.h"

namespace MyEngine
{
    void EntityBarSystem::Init()
    {
    }

    void EntityBarSystem::Start(Scene* pScene)
    {
        ComponentUI::MapComponentsUI(pScene);
    }

    void EntityBarSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void EntityBarSystem::Render(Scene* pScene)
    {
        Entity entityId = EntitySelector::GetSelectedEntity();
        std::string sliderTitle = "Entity #" + std::to_string(entityId);

        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("DUPLICATE ENTITY"))
        {
            m_CreateEntity(pScene, entityId);
        }
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        if (ImGui::Button("NEW ENTITY"))
        {
            m_CreateEntity(pScene);
        }
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        if (ImGui::Button("<"))
        {
            EntitySelector::PrevEntity(pScene);
        }
        ImGui::SameLine();
        if (ImGui::Button(">"))
        {
            EntitySelector::NextEntity(pScene);
        }
        ImGui::SameLine();
        bool treeEntity = ImGui::TreeNodeEx(sliderTitle.c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);

        TagComponent* pTag = pScene->Get<TagComponent>(entityId);
        if (pTag)
        {
            ImGui::SameLine();
            ImGui::Text((" | TAG: " + pTag->name).c_str());
        }

        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        m_AddComponentsList(pScene, entityId);
        if (ImGui::Button("ADD COMPONENT"))
        {
            ImGui::OpenPopup("AddComponentsPopup");
        }

        ImGui::Columns(4, nullptr, false);
        if (treeEntity)
        {
            ComponentUI::GenerateComponentsUI(pScene, entityId);
            ImGui::TreePop();
        }
        ImGui::Columns(1);
    }

    void EntityBarSystem::End(Scene* pScene)
    {
    }

    void EntityBarSystem::Shutdown()
    {
    }

    void EntityBarSystem::m_CreateEntity(Scene* pScene)
    {
        Entity entityId = pScene->CreateEntity(true);
        EntitySelector::SetSelectedEntity(entityId);
    }

    void EntityBarSystem::m_CreateEntity(Scene* pScene, Entity entityId)
    {
        Entity newEntityId = pScene->CreateEntity(entityId);
        EntitySelector::SetSelectedEntity(newEntityId);
    }

    void EntityBarSystem::m_AddComponentsList(Scene* pScene, Entity entityId)
    {
        if (ImGui::BeginPopup("AddComponentsPopup"))
        {
            static bool addTag = false;
            static bool addTransform = false;
            static bool addMovement = false;
            static bool addRotation = false;
            static bool addParent = false;
            static bool addTexture = false;
            static bool addMaterial = false;
            static bool addLight = false;
            static bool addModel = false;
            static bool addTiling = false;
            static bool addGravity = false;
            static bool addRigidBody = false;
            static bool addMeshCollider = false;
            static bool addSphereCollider = false;
            static bool addAABBCollider = false;

            ImGui::Checkbox("Tag Component", &addTag);
            ImGui::Checkbox("Transform Component", &addTransform);
            ImGui::Checkbox("Movement Component", &addMovement);
            ImGui::Checkbox("Rotation Component", &addRotation);
            ImGui::Checkbox("Parent Component", &addParent);
            ImGui::Checkbox("Texture Component", &addTexture);
            ImGui::Checkbox("Material Component", &addMaterial);
            ImGui::Checkbox("Light Component", &addLight);
            ImGui::Checkbox("Model Component", &addModel);
            ImGui::Checkbox("Tiling Component", &addTiling);
            ImGui::Checkbox("Gravity Component", &addGravity);
            ImGui::Checkbox("RigidBody Component", &addRigidBody);
            ImGui::Checkbox("MeshCollider Component", &addMeshCollider);
            ImGui::Checkbox("SphereCollider Component", &addSphereCollider);
            ImGui::Checkbox("AABBCollider Component", &addAABBCollider);

            if (ImGui::Button("Add Selected Components"))
            {
                if (addTag) m_AddComponent<TagComponent>(pScene, entityId);
                if (addTransform) m_AddComponent<TransformComponent>(pScene, entityId);
                if (addMovement) m_AddComponent<MovementComponent>(pScene, entityId);
                if (addRotation) m_AddComponent<RotationComponent>(pScene, entityId);
                if (addParent) m_AddComponent<ParentComponent>(pScene, entityId);
                if (addTexture) m_AddComponent<TextureComponent>(pScene, entityId);
                if (addMaterial) m_AddComponent<MaterialComponent>(pScene, entityId);
                if (addLight) m_AddComponent<LightComponent>(pScene, entityId);
                if (addModel) m_AddComponent<ModelComponent>(pScene, entityId);
                if (addTiling) m_AddComponent<TilingComponent>(pScene, entityId);
                if (addGravity) m_AddComponent<GravityComponent>(pScene, entityId);
                if (addRigidBody) m_AddComponent<RigidBodyComponent>(pScene, entityId);
                if (addMeshCollider) m_AddComponent<MeshColliderComponent>(pScene, entityId);
                if (addSphereCollider) m_AddComponent<SphereColliderComponent>(pScene, entityId);
                if (addAABBCollider) m_AddComponent<AABBColliderComponent>(pScene, entityId);

                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}
