#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class DebugLocator
	{
	public:
		static DebugSquareComponent* GetSquare();
		static DebugSphereComponent* GetSphere();

		static void SetSquare(DebugSquareComponent* pDebugSquare);
		static void SetSphere(DebugSphereComponent* pDebugSphere);

		static void Clear();

	private:
		static DebugSquareComponent* m_pDebugSquare;
		static DebugSphereComponent* m_pDebugSphere;
	};
}
