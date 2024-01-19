#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	// Captures mouse and moves the camera around accordingly to keyboard inputs and mouse position
	// Starts moving when mouse button 1 is pressed
	class FlyingCameraSystem : public iSystem
	{
	public:
		FlyingCameraSystem() = default;
		virtual ~FlyingCameraSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		void m_InitiateMouseCapture();

		void m_StopMouseCapture();

		void m_UpdateCameraRotation();

		void m_UpdateCameraPosition(float deltaTime);
	};
}
