#pragma once

#include "Engine/ECS/Base.h"
#include "Engine/ECS/Scene.h"

#include "Engine/Utils/Vector2.h"

namespace MyEngine
{
	class GameplayUtils
	{
	public:
		static Entity CreateBackground(Scene* pScene, Vec2 position);

		static Entity CreatePlayer(Scene* pScene, Vec2 position);

		static Entity CreateZombie(Scene* pScene, Vec2 position, float speed);

		static Entity CreateProjectile(Scene* pScene, Vec2 position, Vec2 direction, float speed, int damage);

		static Entity GetPlayerId(Scene* pScene);
	};
}
