#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

namespace MyEngine
{
	// Manage all inputs and what the player object should handle it
	class PlayerControllerSystem : public iSystem
	{
	public:
		PlayerControllerSystem() = default;
		virtual ~PlayerControllerSystem() { };

		virtual std::string SystemName() { return "PlayerControllerSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		void m_Shoot(Scene* pScene, TransformComponent* pTransform, 
					 RigidBodyComponent* pRigidBody, PlayerComponent* pPlayer,
                     SoundComponent* pSound);
	};
}
