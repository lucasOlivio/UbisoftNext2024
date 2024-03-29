#pragma once

#include "Engine/Core/iSystem.h"

#include "Engine/ECS/Components.h"

namespace MyEngine
{
	// Manage movement input to truck transform
	class TruckControllerSystem : public iSystem
	{
	public:
		TruckControllerSystem() = default;
		virtual ~TruckControllerSystem() { };

		virtual std::string SystemName() { return "TruckControllerSystem"; };

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
		void m_Rotate(TransformComponent* pTransform, RotationComponent* pRotation, 
					  MovementComponent* pMovement, int direction);
	};
}
