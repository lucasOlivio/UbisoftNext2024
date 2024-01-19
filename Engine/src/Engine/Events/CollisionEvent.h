#pragma once

#include "Event.hpp"
#include "Engine/Physics/PhysicsProperties.h"

namespace MyEngine
{
	enum eCollisionEvents
	{
		COLLISION_ENTER,
		COLLISION_EXIT
	};

	class CollisionEnterEvent : public Event<eCollisionEvents>
	{
	public:
		CollisionEnterEvent() :
			Event<eCollisionEvents>(eCollisionEvents::COLLISION_ENTER, "CollisionEnter") {};
		virtual ~CollisionEnterEvent() {};

		sCollisionData collisionData;
	};

	class CollisionExitEvent : public Event<eCollisionEvents>
	{
	public:
		CollisionExitEvent() :
			Event<eCollisionEvents>(eCollisionEvents::COLLISION_EXIT, "CollisionExit") {};
		virtual ~CollisionExitEvent() {};

		Entity entityA;
		Entity entityB;
	};
}
