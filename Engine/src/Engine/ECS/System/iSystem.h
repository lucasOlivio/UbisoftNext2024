#pragma once

#include "Engine/ECS/Base.h"
#include "Engine/ECS/Scene/Scene.h"

namespace MyEngine
{
	class iSystem
	{
	public:
		iSystem() = default;
		virtual ~iSystem() { };

		// Initializes the system before scene loading
		virtual void Init() = 0;

		// Any initialization the system needs with the scene loaded
		virtual void Start(Scene* pScene) = 0;

		// Simulation per frame
		virtual void Update(Scene* pScene, float deltaTime) = 0;

		// Any rendering in the window
		virtual void Render(Scene* pScene) = 0;

		// Finished this specific scene simulation, not necessarily end of app
		virtual void End(Scene* pScene) = 0;

		// End of app, cleaning of all
		virtual void Shutdown() = 0;
	};
}
