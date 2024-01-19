#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/ECS/Components.h"
#include <glm/mat4x4.hpp>

namespace MyEngine
{
	class RenderSystem : public iSystem
	{
	public:
		RenderSystem() = default;
		virtual ~RenderSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		void m_RenderModel(TilingComponent* pTiling,
						   TransformComponent* pTransform, 
						   ModelComponent* pModel);
	};
}
