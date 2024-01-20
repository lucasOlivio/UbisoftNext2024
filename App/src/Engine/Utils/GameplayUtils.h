#pragma once

#include "Engine/ECS/Base.h"
#include "Engine/ECS/Scene.h"

#include "Engine/Utils/Vector2.h"

namespace MyEngine
{
	class GameplayUtils
	{
	public:
		static Entity CreateZombie(Scene* pScene, Vec2 position, float speed);
	};
}
