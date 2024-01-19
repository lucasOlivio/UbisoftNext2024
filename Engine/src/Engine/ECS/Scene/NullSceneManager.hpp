#pragma once

#include "pch.h"
#include "Engine/ECS/Scene/iSceneManager.h"

namespace MyEngine
{
	class NullSceneManager : public iSceneManager
	{
	public:
		NullSceneManager() {};
		virtual ~NullSceneManager() {};

		virtual std::string GetBasePath()
		{
			LOG_ERROR("SceneManager not loaded yet!");
			return "";
		}

		virtual void SetBasePath(std::string basePath)
		{
			LOG_ERROR("SceneManager not loaded yet!");
			return;
		}

		virtual Scene* CreateNewScene(std::string newSceneName)
		{
			LOG_ERROR("SceneManager not loaded yet!");
			return nullptr;
		}

		virtual Scene* LoadScene(std::string newSceneName)
		{
			LOG_ERROR("SceneManager not loaded yet!");
			return nullptr;
		}

		virtual void SaveScene(std::string sceneName)
		{
			LOG_ERROR("SceneManager not loaded yet!");
			return;
		}

		virtual void ChangeScene(std::string newSceneName, bool reload = false)
		{ 
			LOG_ERROR("SceneManager not loaded yet!");
			return;
		}

		virtual Scene* GetCurrentScene()
		{ 
			LOG_ERROR("SceneManager not loaded yet!");
			return nullptr;
		}

		virtual std::string GetCurrentSceneName()
		{
			LOG_ERROR("SceneManager not loaded yet!");
			return "";
		}

		virtual Scene* GetScene(std::string sceneName)
		{
			LOG_ERROR("SceneManager not loaded yet!");
			return nullptr;
		}

		virtual void ClearDeletedScenes()
		{
			LOG_ERROR("SceneManager not loaded yet!");
		}
	};
}
