#pragma once

#include "Engine/ECS/Scene/Scene.h"

#include <string>

namespace MyEngine
{
	class iSceneManager
	{
	public:
		iSceneManager() {};
		virtual ~iSceneManager() {};

		virtual std::string GetBasePath() = 0;

		virtual void SetBasePath(std::string basePath) = 0;

		// Only creates a new empty scene and creates the file
		virtual Scene* CreateNewScene(std::string newSceneName) = 0;

		// Load new scene from file to cache
		virtual Scene* LoadScene(std::string newSceneName) = 0;

		// Serialize scene to file
		virtual void SaveScene(std::string sceneName) = 0;

		// Change active scene
		virtual void ChangeScene(std::string newSceneName, bool reload = false) = 0;

		// Get active scene
		virtual Scene* GetCurrentScene() = 0;
		virtual std::string GetCurrentSceneName() = 0;

		// Get any scene from cache
		virtual Scene* GetScene(std::string sceneName) = 0;

		// Call in end of frame to avoid deleting while somewhere is using
		virtual void ClearDeletedScenes() = 0;
	};
}
