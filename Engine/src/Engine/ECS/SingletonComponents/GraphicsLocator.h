#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class GraphicsLocator
	{
	public:
		static CameraComponent* GetCamera();
		static TransparentEntitiesComponent* GetTransparentEntities();
		static WindowComponent* GetWindow();

		static void SetCamera(CameraComponent* pCamera);
		static void SetTransparentEntities(TransparentEntitiesComponent* pTransparentEntities);
		static void SetWindow(WindowComponent* pWindow);

		static void Clear();

	private:
		static CameraComponent* m_pCamera;
		static TransparentEntitiesComponent* m_pTransparentEntities;
		static WindowComponent* m_pWindow;
	};
}
