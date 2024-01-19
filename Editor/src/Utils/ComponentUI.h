#pragma once

#include "Engine/ECS/Base.h"
#include "Engine/ECS/Scene/Scene.h"

#include <map>
#include <string>
#include <functional>

namespace MyEngine
{
	using ComponentUIHandler = std::function<void(Scene*, Entity)>;

	class ComponentUI
	{
	public:
		static void GenerateComponentsUI(Scene* pScene, Entity entityId);

		// Store components id -> UIhandler to all components in cache
		static void MapComponentsUI(Scene* pScene);

		static ComponentUIHandler GetComponentUI(ComponentType component);

	private:
		static std::map<ComponentId, ComponentUIHandler> m_componentsUI;

		static void m_EmptyUI(Scene* pScene, Entity entityId);

		static void m_TagUI(Scene* pScene, Entity entityId);
		static void m_TransformUI(Scene* pScene, Entity entityId);
		static void m_MovementUI(Scene* pScene, Entity entityId);
		static void m_RotationUI(Scene* pScene, Entity entityId);
		static void m_ParentUI(Scene* pScene, Entity entityId);
		static void m_TextureUI(Scene* pScene, Entity entityId);
		static void m_MaterialUI(Scene* pScene, Entity entityId);
		static void m_LightUI(Scene* pScene, Entity entityId);
		static void m_ModelUI(Scene* pScene, Entity entityId);
		static void m_TilingUI(Scene* pScene, Entity entityId);
		static void m_GravityUI(Scene* pScene, Entity entityId);
		static void m_RigidBodyUI(Scene* pScene, Entity entityId);
		static void m_MeshColliderUI(Scene* pScene, Entity entityId);
		static void m_SphereColliderUI(Scene* pScene, Entity entityId);
		static void m_AABBColliderUI(Scene* pScene, Entity entityId);

	};
}
