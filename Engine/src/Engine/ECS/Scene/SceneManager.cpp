#include "pch.h"

#include "SceneManager.h"

#include "Engine/ECS/Scene/SceneSerializerFactory.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/SceneEvent.h"
#include "Engine/Events/EventBusLocator.hpp"

namespace MyEngine
{
	using itScenes = std::map<std::string /*Scene name*/, Scene*>::iterator;
	using pairScenes = std::pair<std::string /*Scene name*/, Scene*>;

	SceneManager::SceneManager()
	{
		m_nameCurrScene = "";
		m_pCurrScene = nullptr;
	}

	SceneManager::~SceneManager()
	{
		for (pairScenes scene : m_mapScenes)
		{
			delete scene.second;
		}

		ClearDeletedScenes();
	}

	std::string SceneManager::GetBasePath()
	{
		return m_basePath;
	}

	void SceneManager::SetBasePath(std::string basePath)
	{
		m_basePath = basePath;
	}

	Scene* SceneManager::CreateNewScene(std::string newSceneName)
	{
		Scene* pNewScene = new Scene();
		iSceneSerializer* pSceneSerializer = SceneSerializerFactory::CreateSceneSerializer(newSceneName);

		pSceneSerializer->SerializeScene(m_basePath + newSceneName, *(pNewScene));

		return pNewScene;
	}

	Scene* SceneManager::LoadScene(std::string newSceneName)
	{
		// Scene not loaded yet
		Scene* pNewScene = new Scene();
		iSceneSerializer* pSceneSerializer = SceneSerializerFactory::CreateSceneSerializer(newSceneName);

		pSceneSerializer->DeserializeScene(m_basePath + newSceneName, *(pNewScene));

		return pNewScene;
	}

	void SceneManager::SaveScene(std::string sceneName)
	{
		Scene* pScene = GetScene(sceneName);
		iSceneSerializer* pSceneSerializer = SceneSerializerFactory::CreateSceneSerializer(sceneName);

		pSceneSerializer->SerializeScene(m_basePath + sceneName, *(pScene));

		return;
	}

	void SceneManager::ChangeScene(std::string newSceneName, bool reload)
	{
		Scene* pNewScene = GetScene(newSceneName);
		itScenes it = m_mapScenes.find(newSceneName);
		if (reload || !pNewScene)
		{
			if (pNewScene)
			{
				// Scene already loaded, so we mark to deletion
				m_pScenesToDelete.push_back(pNewScene);
			}

			pNewScene = LoadScene(newSceneName);
			m_mapScenes[newSceneName] = pNewScene;
		}

		m_nameCurrScene = newSceneName;
		m_pCurrScene = pNewScene;

		m_TriggerSceneChange(newSceneName, pNewScene);
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return m_pCurrScene;
	}

	std::string SceneManager::GetCurrentSceneName()
	{
		return m_nameCurrScene;
	}

	Scene* SceneManager::GetScene(std::string sceneName)
	{
		Scene* pScene = nullptr;
		itScenes it = m_mapScenes.find(sceneName);
		if (it == m_mapScenes.end() || !it->second)
		{
			return nullptr;
		}
		else
		{
			pScene = it->second;
			return pScene;
		}
	}

	void SceneManager::ClearDeletedScenes()
	{
		for (Scene* pSCene : m_pScenesToDelete)
		{
			delete pSCene;
		}

		m_pScenesToDelete.clear();
	}

	void SceneManager::m_TriggerSceneChange(std::string newSceneName, Scene* pNewScene)
	{
		iEventBus<eSceneEvents, SceneChangeEvent>* pEventBus = EventBusLocator<eSceneEvents, SceneChangeEvent>::Get();

		SceneChangeEvent sceneEvent = SceneChangeEvent();
		sceneEvent.newSceneName = newSceneName;
		sceneEvent.pNewScene = pNewScene;
		pEventBus->Publish(sceneEvent);

		return;
	}
}
