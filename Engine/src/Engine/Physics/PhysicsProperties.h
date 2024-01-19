#pragma once

#include "Engine/ECS/Base.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace MyEngine
{
	enum eBody
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

	struct sCollisionData
	{
		Entity entityA;
		Entity entityB;
		glm::vec3 contactPoint;
		glm::vec3 collisionNormalA;
		glm::vec3 collisionNormalB;
		glm::vec3 velocityAtCollisionA;
		glm::vec3 velocityAtCollisionB;
	};
}
