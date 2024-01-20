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

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		// direction: 1 forward, -1 backwards
		void m_Accelerate(TransformComponent* pTransform, MovementComponent* pMovement, int direction);

		// direction: 1 left, -1 right
		void m_Rotate(TransformComponent* pTransform, RotationComponent* pRotation, MovementComponent* pMovement, int direction);

		void m_ClipPlayerToWindow(TransformComponent* pTransform, RigidBodyComponent* pRigidBody);
	};
}
