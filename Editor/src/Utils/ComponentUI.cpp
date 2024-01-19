#include "pch.h"

#include "ComponentUI.h"

#include "Utils/UIWidgets.h"

#include "Engine/ECS/Components.h"

namespace MyEngine
{
    std::map<ComponentId, ComponentUIHandler> ComponentUI::m_componentsUI = {};

    void ComponentUI::GenerateComponentsUI(Scene* pScene, Entity entityId)
    {
        EntityManager* pEntityManager = pScene->GetEntitymanager();

        if (pEntityManager->Size() == 1)
        {
            return;
        }

        // For all components that entity have get the UI generator from cache and draw UI
        int numComponents = pScene->GetComponentCount();
        EntityMask mask = pEntityManager->GetMask(entityId);
        for (int i = 0; i <= numComponents; i++)
        {
            if (!mask[i])
            {
                continue;
            }

            Separator();
            Separator();

            ComponentUIHandler handler = GetComponentUI(i);
            handler(pScene, entityId);

            Separator();
            Separator();
        }
    }

    void ComponentUI::MapComponentsUI(Scene* pScene)
    {
        ComponentType TagType = pScene->GetComponentType<TagComponent>();
        m_componentsUI[TagType] = m_TagUI;

        ComponentType TransformType = pScene->GetComponentType<TransformComponent>();
        m_componentsUI[TransformType] = m_TransformUI;

        ComponentType MovementType = pScene->GetComponentType<MovementComponent>();
        m_componentsUI[MovementType] = m_MovementUI;

        ComponentType RotationType = pScene->GetComponentType<RotationComponent>();
        m_componentsUI[RotationType] = m_RotationUI;

        ComponentType ParentType = pScene->GetComponentType<ParentComponent>();
        m_componentsUI[ParentType] = m_ParentUI;

        ComponentType TextureType = pScene->GetComponentType<TextureComponent>();
        m_componentsUI[TextureType] = m_TextureUI;

        ComponentType MaterialType = pScene->GetComponentType<MaterialComponent>();
        m_componentsUI[MaterialType] = m_MaterialUI;

        ComponentType LightType = pScene->GetComponentType<LightComponent>();
        m_componentsUI[LightType] = m_LightUI;

        ComponentType ModelType = pScene->GetComponentType<ModelComponent>();
        m_componentsUI[ModelType] = m_ModelUI;

        ComponentType TilingType = pScene->GetComponentType<TilingComponent>();
        m_componentsUI[TilingType] = m_TilingUI;

        ComponentType GravityType = pScene->GetComponentType<GravityComponent>();
        m_componentsUI[GravityType] = m_GravityUI;

        ComponentType RigidBodyType = pScene->GetComponentType<RigidBodyComponent>();
        m_componentsUI[RigidBodyType] = m_RigidBodyUI;

        ComponentType MeshColliderType = pScene->GetComponentType<MeshColliderComponent>();
        m_componentsUI[MeshColliderType] = m_MeshColliderUI;

        ComponentType SphereColliderType = pScene->GetComponentType<SphereColliderComponent>();
        m_componentsUI[SphereColliderType] = m_SphereColliderUI;

        ComponentType AABBColliderType = pScene->GetComponentType<AABBColliderComponent>();
        m_componentsUI[AABBColliderType] = m_AABBColliderUI;
    }

    ComponentUIHandler ComponentUI::GetComponentUI(ComponentType component)
    {
        std::map<ComponentId, ComponentUIHandler>::iterator it = m_componentsUI.find(component);
        if (it == m_componentsUI.end())
        {
            return m_EmptyUI;
        }

        return it->second;
    }

    void ComponentUI::m_EmptyUI(Scene* pScene, Entity entityId)
    {
    }

    void ComponentUI::m_TagUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Tag:");

        TagComponent* pTag = pScene->Get<TagComponent>(entityId);
        if (!pTag)
        {
            return;
        }

        ImGui::Text("Name");
        ImGui::InputText("##Name", &pTag->name);
    }

    void ComponentUI::m_TransformUI(Scene* pScene, Entity entityId)
	{
        ImGui::Text("Transform:");

        TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
        if (!pTransform)
        {
            return;
        }

        ImGui::Text("Position");
        ImGui::InputFloat("##PositionX", &pTransform->position.x);
        ImGui::InputFloat("##PositionY", &pTransform->position.y);
        ImGui::InputFloat("##PositionZ", &pTransform->position.z);

        Separator();
        ImGui::Text("Rotation (Euler)");
        glm::vec3 euler = glm::degrees(glm::eulerAngles(pTransform->orientation));
        if (ImGui::InputFloat("##RotationX", &euler.x)) {
            pTransform->orientation = glm::quat(glm::radians(euler));
        }
        if (ImGui::InputFloat("##RotationY", &euler.y)) {
            pTransform->orientation = glm::quat(glm::radians(euler));
        }
        if (ImGui::InputFloat("##RotationZ", &euler.z)) {
            pTransform->orientation = glm::quat(glm::radians(euler));
        }

        Separator();
        ImGui::Text("Scale");
        ImGui::InputFloat("##Scale", &pTransform->scale);
	}

    void ComponentUI::m_MovementUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Movement:");

        MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);
        if (!pMovement)
        {
            return;
        }

        ImGui::Text("Velocity");
        ImGui::InputFloat("##VelocityX", &pMovement->velocity.x);
        ImGui::InputFloat("##VelocityY", &pMovement->velocity.y);
        ImGui::InputFloat("##VelocityZ", &pMovement->velocity.z);

        Separator();
        ImGui::Text("Acceleration");
        ImGui::InputFloat("##AccelerationX", &pMovement->acceleration.x);
        ImGui::InputFloat("##AccelerationY", &pMovement->acceleration.y);
        ImGui::InputFloat("##AccelerationZ", &pMovement->acceleration.z);
    }

    void ComponentUI::m_RotationUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Rotation:");

        RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);
        if (!pRotation)
        {
            return;
        }

        ImGui::Text("Angular Velocity");
        ImGui::InputFloat("##AngularVelocityX", &pRotation->velocity.x);
        ImGui::InputFloat("##AngularVelocityY", &pRotation->velocity.y);
        ImGui::InputFloat("##AngularVelocityZ", &pRotation->velocity.z);

        Separator();
        ImGui::Text("Angular Acceleration");
        ImGui::InputFloat("##AngularAccelerationX", &pRotation->acceleration.x);
        ImGui::InputFloat("##AngularAccelerationY", &pRotation->acceleration.y);
        ImGui::InputFloat("##AngularAccelerationZ", &pRotation->acceleration.z);
    }

    void ComponentUI::m_ParentUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Parent:");

        ParentComponent* pParent = pScene->Get<ParentComponent>(entityId);
        if (!pParent)
        {
            return;
        }

        ImGui::Text("Parent Entity ID");
        ImGui::InputInt("##ParentEntityID", &pParent->parentId);
    }

    void ComponentUI::m_TextureUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Texture:");

        TextureComponent* pTexture = pScene->Get<TextureComponent>(entityId);
        if (!pTexture)
        {
            return;
        }

        ImGui::Text("File Name");
        ImGui::InputText("##FileName", &pTexture->fileName);

        // Way to set it with a list
        ImGui::Text("Texture Type");
        ImGui::InputInt("##TextureType", reinterpret_cast<int*>(&pTexture->textureType));

        ImGui::Text("Texture Sides");
        for (size_t i = 0; i < pTexture->vecTextures.size(); ++i)
        {
            ImGui::InputText(("##TextureSide" + std::to_string(i)).c_str(), &pTexture->vecTextures[i]);
        }
    }

    void ComponentUI::m_MaterialUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Material:");

        MaterialComponent* pMaterial = pScene->Get<MaterialComponent>(entityId);
        if (!pMaterial)
        {
            return;
        }

        ImGui::Text("Name");
        ImGui::InputText("##MaterialName", &pMaterial->name);

        ImGui::Text("Offset");
        ImGui::InputFloat3("##Offset", &pMaterial->offset.x);

        ImGui::Text("Offset Move");
        ImGui::InputFloat3("##OffsetMove", &pMaterial->offsetMove.x);

        ImGui::Text("Offset Height Map");
        ImGui::InputFloat3("##OffsetHeightMap", &pMaterial->offsetHeightMap.x);

        ImGui::Text("Color Textures");
        for (size_t i = 0; i < pMaterial->colorTextures.size(); ++i)
        {
            ImGui::InputText(("##ColorTexture" + std::to_string(i)).c_str(), &pMaterial->colorTextures[i]);
        }

        ImGui::Text("Color Textures Ratios");
        ImGui::InputFloat3("##ColorTexturesRatios", &pMaterial->colorTexturesRatios.x);

        ImGui::Text("Use Height Map");
        ImGui::Checkbox("##UseHeightMap", &pMaterial->useHeightMap);

        ImGui::Text("Height Map Texture");
        ImGui::InputText("##HeightMapTexture", &pMaterial->heightMapTexture);

        ImGui::Text("Height Scale");
        ImGui::InputFloat("##HeightScale", &pMaterial->heightScale);

        ImGui::Text("Use Normal Texture");
        ImGui::Checkbox("##UseNormalTexture", &pMaterial->useNormalTexture);

        ImGui::Text("Normal Texture");
        ImGui::InputText("##NormalTexture", &pMaterial->normalTexture);

        ImGui::Text("Is Emissive");
        ImGui::Checkbox("##IsEmissive", &pMaterial->isEmissive);

        ImGui::Text("Use Alpha Texture");
        ImGui::Checkbox("##UseAlphaTexture", &pMaterial->useAlphaTexture);

        ImGui::Text("Alpha Texture");
        ImGui::InputText("##AlphaTexture", &pMaterial->alphaTexture);
    }

    void ComponentUI::m_LightUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Light:");

        LightComponent* pLight = pScene->Get<LightComponent>(entityId);
        if (!pLight)
        {
            return;
        }

        // Flickering control
        ImGui::Text("Flicker Offset");
        ImGui::InputFloat4("##FlickerOffset", &pLight->flickerOffset.x);

        // ulBasePath
        ImGui::Text("UL Base Path");
        ImGui::InputText("##ULBasePath", &pLight->ulBasePath);

        // Controls relative to transform component
        ImGui::Text("Position Offset");
        ImGui::InputFloat4("##PositionOffset", &pLight->positionOffset.x);

        ImGui::Text("Direction Offset");
        ImGui::InputFloat4("##DirectionOffset", &pLight->directionOffset.x);

        ImGui::Text("Distance Offset");
        ImGui::InputFloat("##DistanceOffset", &pLight->distanceOffset);

        // Light parameters
        ImGui::Text("Diffuse (R, G, B, A)");
        ImGui::InputFloat4("##Diffuse", &pLight->diffuse.x);

        ImGui::Text("Specular (R, G, B, Power)");
        ImGui::InputFloat4("##Specular", &pLight->specular.x);

        ImGui::Text("Attenuation (Constant, Linear, Quadratic, Distance CutOff)");
        ImGui::InputFloat4("##Attenuation", &pLight->atten.x);

        ImGui::Text("Direction");
        ImGui::InputFloat4("##Direction", &pLight->direction.x);

        ImGui::Text("Parameters (Type, Inner Angle, Outer Angle, Is Flickery)");
        ImGui::InputFloat4("##Params", &pLight->params.x);

        ImGui::Text("Status");
        ImGui::Checkbox("##Status", &pLight->status);
    }

    void ComponentUI::m_ModelUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Model:");

        ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
        if (!pModel)
        {
            return;
        }

        // Model paths
        ImGui::Text("Models");
        for (size_t i = 0; i < pModel->models.size(); ++i)
        {
            ImGui::InputText(("##Model" + std::to_string(i)).c_str(), &pModel->models[i]);
        }

        // Material
        ImGui::Text("Material");
        ImGui::InputText("##Material", &pModel->material);

        // Flags
        ImGui::Checkbox("Wireframe", &pModel->isWireframe);
        ImGui::Checkbox("Do Not Light", &pModel->doNotLight);
        ImGui::Checkbox("Use Color Texture", &pModel->useColorTexture);

        // Other parameters
        ImGui::Text("Elapsed Time");
        ImGui::InputDouble("##ElapsedTime", &pModel->elapsedTime);

        ImGui::Checkbox("Is Active", &pModel->isActive);
    }

    void ComponentUI::m_TilingUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Tiling:");

        TilingComponent* pTiling = pScene->Get<TilingComponent>(entityId);
        if (!pTiling)
        {
            return;
        }

        // Axis
        ImGui::Text("Axis");
        ImGui::InputFloat3("##TilingAxis", &pTiling->axis.x);

        // Offset
        ImGui::Text("Offset");
        ImGui::InputFloat3("##TilingOffset", &pTiling->offset.x);
    }

    void ComponentUI::m_GravityUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Gravity:");

        GravityComponent* pGravity = pScene->Get<GravityComponent>(entityId);
        if (!pGravity)
        {
            return;
        }

        // Acceleration
        ImGui::Text("Acceleration");
        ImGui::InputFloat3("##GravityAcceleration", &pGravity->acceleration.x);
    }

    void ComponentUI::m_RigidBodyUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Rigid Body:");

        RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);
        if (!pRigidBody)
        {
            return;
        }

        // Body Type
        ImGui::Text("Body Type");
        ImGui::InputInt("##BodyType", reinterpret_cast<int*>(&pRigidBody->bodyType));

        // Shape Type
        ImGui::Text("Shape Type");
        ImGui::InputInt("##ShapeType", reinterpret_cast<int*>(&pRigidBody->shapeType));
    }

    void ComponentUI::m_MeshColliderUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Mesh Collider:");

        MeshColliderComponent* pMeshCollider = pScene->Get<MeshColliderComponent>(entityId);
        if (!pMeshCollider)
        {
            return;
        }

        // Name
        ImGui::Text("Name");
        ImGui::InputText("##MeshColliderName", &pMeshCollider->name);
    }

    void ComponentUI::m_SphereColliderUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("Sphere Collider:");

        SphereColliderComponent* pSphereCollider = pScene->Get<SphereColliderComponent>(entityId);
        if (!pSphereCollider)
        {
            return;
        }

        // Radius
        ImGui::Text("Radius");
        ImGui::InputFloat("##SphereColliderRadius", &pSphereCollider->radius);
    }

    void ComponentUI::m_AABBColliderUI(Scene* pScene, Entity entityId)
    {
        ImGui::Text("AABB Collider:");

        AABBColliderComponent* pAABBCollider = pScene->Get<AABBColliderComponent>(entityId);
        if (!pAABBCollider)
        {
            return;
        }

        // Min
        ImGui::Text("Min");
        ImGui::InputFloat3("##AABBColliderMin", &pAABBCollider->min.x);

        // Max
        ImGui::Text("Max");
        ImGui::InputFloat3("##AABBColliderMax", &pAABBCollider->max.x);
    }
}
