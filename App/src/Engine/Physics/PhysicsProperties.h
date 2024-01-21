#pragma once

#include "Engine/ECS/Base.h"
#include "Engine/ECS/Scene.h"

#include "Engine/Utils/Vector2.h"

#include <vector>

namespace MyEngine
{
	enum eBody
	{
		ACTIVE,
		PASSIVE
	};

	struct sCollisionData
	{
		Scene* pScene;
		Entity entityActive;
		Entity entityPassive;
	};
}
