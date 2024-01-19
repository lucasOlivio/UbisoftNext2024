#include "pch.h"

#include "MaterialManager.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"
#include "Engine/Graphics/Textures/TextureManagerLocator.h"
#include "Engine/ECS/Scene/SceneView.hpp"

namespace MyEngine
{
	MaterialManager::MaterialManager()
	{}

	MaterialManager::~MaterialManager()
	{
	}

	void MaterialManager::BindMaterial(Scene* pScene, std::string materialName)
	{
		// Only change material if not already binded
		if (materialName == m_currMaterial)
		{
			return;
		}

		MaterialComponent* pMaterial = GetMaterialByName(pScene, materialName);

		// Material not found
		if (!pMaterial)
		{
			std::string warning = "Material '" + materialName + "' not found!";
			LOG_WARNING(warning);
			return;
		}
		// Unbind current material on shader
		UnbindMaterial();

		std::vector<TextureComponent*> vecTexturesComp = pMaterial->texturesComponents;

		iShaderProgram* pShader = ShaderManager::GetActiveShader();
		iTextureManager* pTextureManager = TextureManagerLocator::Get();

		// Update offset, alpha and if is emissive material
		// TODO: Regulate the intensity of the emissiviness
		pShader->SetUniformInt("isEmissive", pMaterial->isEmissive);

		glm::vec3 finaloffset = pMaterial->currOffset + pMaterial->offset;
		pShader->SetUniformVec2("UVOffset", finaloffset);

		pShader->SetUniformVec2("HeightMapOffset", pMaterial->currOffsetHeightMap);

		// Bind color textures
		for (int i = 0; i < pMaterial->colorTextures.size(); i++)
		{
			pTextureManager->BindTexture(pMaterial->colorTextures[i],
										 eTextureType::COLOR,
										 pMaterial->colorTexturesRatios[i]);
		}

		// TODO: Remove repetition, all could be in a vector or map
		// Bind heightmap textures
		if (pMaterial->useHeightMap)
		{
			// Height scale can be passed as the "ratio parameter", will be placed on the heightscale uniform
			pTextureManager->BindTexture(pMaterial->heightMapTexture,
				eTextureType::HEIGHTMAP,
				pMaterial->heightScale);
		}

		// Bind normal textures
		if (pMaterial->useNormalTexture)
		{
			pTextureManager->BindTexture(pMaterial->normalTexture,
				eTextureType::NORMAL,
				0);
		}

		// Bind specular textures
		if (pMaterial->useSpecularTexture)
		{
			pTextureManager->BindTexture(pMaterial->specularTexture,
				eTextureType::SPECULAR,
				0);
		}

		// Bind discard textures
		if (pMaterial->useDiscardTexture)
		{
			pTextureManager->BindTexture(pMaterial->discardTexture,
				eTextureType::DISCARD,
				0);
		}

		// Bind alpha textures
		if (pMaterial->useAlphaTexture)
		{
			pTextureManager->BindTexture(pMaterial->alphaTexture,
				eTextureType::TRANSPARENCY,
				0);
		}

		// Bind cube textures
		if (pMaterial->useCubeTexture)
		{
			pTextureManager->BindTexture(pMaterial->cubeTexture,
										   eTextureType::CUBE,
										   0);
		}

		m_currMaterial = materialName;
	}

	void MaterialManager::UnbindMaterial()
	{
		iShaderProgram* pShader = ShaderManager::GetActiveShader();
		iTextureManager* pTextureManager = TextureManagerLocator::Get();

		pTextureManager->ResetSamplers();
		pShader->SetUniformVec2("UVOffset", glm::vec2(0.0, 0.0));
		pShader->SetUniformVec2("HeightMapOffset", glm::vec2(0.0, 0.0));
		pShader->SetUniformInt("isEmissive", false);
	}

	MaterialComponent* MaterialManager::GetMaterialByName(Scene* pScene, std::string materialName)
	{
		typedef std::map<std::string, MaterialComponent*>::iterator itMaterials;

		itMaterials it = m_materials.find(materialName);
		if (it != m_materials.end())
		{
			return it->second;
		}

		// Material not mapped yet, so search for it in the scene
		for (Entity entityId : SceneView<MaterialComponent>(*pScene))
		{
			MaterialComponent* pMaterial = pScene->Get<MaterialComponent>(entityId);

			if (pMaterial->name == materialName)
			{
				m_materials[materialName] = pMaterial;
				return pMaterial;
			}
		}

		return nullptr;
	}

	void MaterialManager::DeleteMaterial(Scene* pScene, std::string materialName)
	{
		MaterialComponent* pMaterial = GetMaterialByName(pScene, materialName);

		if (pMaterial)
		{
			delete pMaterial;
		}

		m_materials.erase(materialName);
	}
}
