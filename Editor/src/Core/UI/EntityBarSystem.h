#pragma once

#include "Engine/ECS/System/iSystem.h"

#include "Engine/Events/SceneEvent.h"

namespace MyEngine
{
	// Side bar with selected entity and components UI
	class EntityBarSystem : public iSystem
	{
	public:
		EntityBarSystem() = default;
		virtual ~EntityBarSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		void m_CreateEntity(Scene* pScene);
		void m_CreateEntity(Scene* pScene, Entity entityId);

		void m_AddComponentsList(Scene* pScene, Entity entityId);

		template <typename T>
		void m_AddComponent(Scene* pScene, Entity entityId)
		{
			pScene->AddComponent<T>(entityId);
		}

		// TODO: Remove component avoiding conflict with other systems using it
	};
}
