#pragma once

#include "Engine/ECS/Base.h"
#include "Engine/ECS/Scene/Scene.h"

namespace MyEngine
{
	// HACK: Hacky way to store selected entity id and next entity id without putting on system
	class EntitySelector
	{
	public:
		EntitySelector();
		~EntitySelector();

		static Entity GetSelectedEntity();
		static Entity NextEntity(Scene* pScene);
		static Entity PrevEntity(Scene* pScene);

		static void SetSelectedEntity(Entity entityId);

	private:
		static Entity m_selectedEntity;
	};
}
