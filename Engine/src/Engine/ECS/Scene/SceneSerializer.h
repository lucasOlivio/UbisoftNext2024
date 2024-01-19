#pragma once

#include "Scene.h"

namespace MyEngine {

	class SceneSerializer
	{
	public:
		SceneSerializer(Scene* pScene);

		bool Serialize(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
	private:
		Scene* m_pScene;
	};

}
