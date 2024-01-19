#include "pch.h"

#include "RenderSystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Graphics/Materials/MaterialManagerLocator.h"
#include "Engine/Graphics/Textures/TextureManagerLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"

#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
	void RenderSystem::Init()
	{
	}

	void RenderSystem::Start(Scene* pScene)
    {
		ConfigPathComponent* pConfigPath = CoreLocator::GetConfigPath();
		iTextureManager* pTextureManager = TextureManagerLocator::Get();
		iVAOManager* pVAOManager = VAOManagerLocator::Get();

		// Load textures
		pTextureManager->SetBasePath(pConfigPath->pathTextures);
		for (Entity entityId : SceneView<TextureComponent>(*pScene))
		{
			TextureComponent* pTexture = pScene->Get<TextureComponent>(entityId);
			std::string errorMsg = "";
			bool isLoaded = true;

			if (pTexture->textureType == eTextureType::CUBE)
			{
				isLoaded = pTextureManager->CreateCubeTextureFromBMPFiles(pTexture->fileName,
																		  pTexture->vecTextures[0],
																		  pTexture->vecTextures[1],
																		  pTexture->vecTextures[2],
																		  pTexture->vecTextures[3],
																		  pTexture->vecTextures[4],
																		  pTexture->vecTextures[5],
																		  true,
																		  errorMsg);
				continue;
			}
			else
			{
				isLoaded = pTextureManager->Create2DTextureFromBMPFile(pTexture->fileName, true);
				errorMsg = pTextureManager->GetLastError();
			}

			if (!isLoaded)
			{
				LOG_ERROR(errorMsg);
				continue;
			}
		}

		// Load Models
		pVAOManager->SetBasePath(pConfigPath->pathModels);
		for (Entity entityId : SceneView<ModelComponent>(*pScene))
		{
			ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
			pModel->pMeshes.resize(pModel->models.size(), nullptr);
			for (int i = 0; i < pModel->models.size(); i++)
			{
				sMesh* pMesh = pVAOManager->LoadModelIntoVAO(pModel->models[i], false);
				if (!pMesh)
				{
					continue;
				}
				pModel->pMeshes[i] = pMesh;
			}
		}
    }

    void RenderSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void RenderSystem::Render(Scene* pScene)
    {
		std::vector<TransformComponent*> vecTransparentEntities;
		CameraComponent* pCamera = GraphicsLocator::GetCamera();
		TransparentEntitiesComponent* pTransparents = GraphicsLocator::GetTransparentEntities();
		iMaterialManager* pMaterialManager = MaterialManagerLocator::Get();

		// Render all "not transparent" models
		pTransparents->entities.clear();
		for (Entity entityId : SceneView<TransformComponent, ModelComponent>(*pScene))
		{
			ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
			TilingComponent* pTiling = pScene->Get<TilingComponent>(entityId);

			if (!pModel->isActive)
			{
				continue;
			}

			// Bind material
			MaterialComponent* pMaterial = pMaterialManager->GetMaterialByName(pScene, 
																			   pModel->material);
			if (pMaterial)
			{
				// Transparent objects must be rendered after
				if (pMaterial->useAlphaTexture)
				{
					pTransparents->entities.push_back(entityId);
					continue;
				}

				pMaterialManager->BindMaterial(pScene, pMaterial->name);
			}

			m_RenderModel(pTiling, pTransform, pModel);
		}

		// Render all transparent models, the sorting by distance is done separatedly
		for (Entity entityId : pTransparents->entities)
		{
			ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
			TilingComponent* pTiling = pScene->Get<TilingComponent>(entityId);

			// Bind material
			MaterialComponent* pMaterial = pMaterialManager->GetMaterialByName(pScene,
																			   pModel->material);
			pMaterialManager->BindMaterial(pScene, pMaterial->name);

			m_RenderModel(pTiling, pTransform, pModel);
		}
    }

    void RenderSystem::End(Scene* pScene)
    {
    }

	void RenderSystem::Shutdown()
	{
	}

	void RenderSystem::m_RenderModel(TilingComponent* pTiling,
									 TransformComponent* pTransform, 
									 ModelComponent* pModel)
	{
		// Default we only draw 1 time in each axis
		glm::vec3 axis = glm::vec3(1.0);
		glm::vec3 offset = glm::vec3(0.0);
		// If has tiling then we draw X times per axis based on the offset
		if (pTiling)
		{
			axis = pTiling->axis;
			offset = pTiling->offset;
		}

		glm::vec3 finalPosition = pTransform->worldPosition;

		// Now go for each axis tiling to draw adding the offset
		for (int x = 0; x < axis[0]; x++)
		{
			for (int y = 0; y < axis[1]; y++)
			{
				for (int z = 0; z < axis[2]; z++)
				{
					glm::vec3 delta = offset;
					delta.x = offset.x * x;
					delta.y = offset.y * y;
					delta.z = offset.z * z;
					finalPosition += delta;

					// If the model have a parent we must use the parents transform
					glm::mat4 matTransform = glm::mat4(1.0);

					TransformUtils::GetTransform(finalPosition,
						pTransform->worldOrientation,
						pTransform->worldScale,
						matTransform);

					sMesh* pMesh = pModel->pMeshes[pModel->currMesh];
					GraphicsUtils::DrawModel(matTransform,
						pModel->isWireframe,
						pModel->doNotLight,
						pModel->useColorTexture,
						pMesh->VAO_ID,
						pMesh->numberOfIndices);
				}
			}
		}
	}
}
