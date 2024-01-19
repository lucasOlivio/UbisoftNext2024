#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	class CheckCloser
	{
	public:
		CheckCloser(Scene* pScene) : m_pScene(pScene) {}

		bool operator () (Entity entityA, Entity entityB);

	private:
		Scene* m_pScene;
	};

	class SortTransparentsSystem : public iSystem
	{
	public:
		SortTransparentsSystem() = default;
		virtual ~SortTransparentsSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
