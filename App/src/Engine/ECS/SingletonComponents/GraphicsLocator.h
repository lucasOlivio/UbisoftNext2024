#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class GraphicsLocator
	{
	public:
		static CameraComponent* GetCamera();

		static void SetCamera(CameraComponent* pCamera);

		static void Clear();

	private:
		static CameraComponent* m_pCamera;
	};
}
