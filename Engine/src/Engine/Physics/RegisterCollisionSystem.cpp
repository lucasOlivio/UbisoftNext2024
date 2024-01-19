#include "pch.h"

#include "RegisterCollisionSystem.h"

#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/EventBusLocator.hpp"
#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	void RegisterCollisionSystem::Init()
	{
		// Subscribe to enter collision event
		iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

		pEventBus->Subscribe(eCollisionEvents::COLLISION_ENTER, RegisterCollision);
	}

	void RegisterCollisionSystem::Start(Scene* pScene)
	{
	}

	void RegisterCollisionSystem::Update(Scene* pScene, float deltaTime)
	{
		StateComponent* pState = CoreLocator::GetState();
		if (pState->currState == eStates::SIMULATION_STOPPED)
		{
			return;
		}

		FrameCollisionComponent* pFrameColl = PhysicsLocator::GetFrameCollision();
		FrameCounterComponent* pFrames = CoreLocator::GetFrameCounter();

		// Module to make sure we stay in FRAME_RATE size
		int currFrame = pFrames->frameCount % FRAME_RATE;
		pFrameColl->collisions[currFrame].clear();
	}

	void RegisterCollisionSystem::Render(Scene* pScene)
	{
	}

	void RegisterCollisionSystem::End(Scene* pScene)
	{
	}

	void RegisterCollisionSystem::Shutdown()
	{
	}

	void RegisterCollisionSystem::RegisterCollision(const CollisionEnterEvent& event)
	{
		FrameCollisionComponent* pFrameColl = PhysicsLocator::GetFrameCollision();
		FrameCounterComponent* pFrames = CoreLocator::GetFrameCounter();

		// Module to make sure we stay in FRAME_RATE size
		int currFrame = pFrames->frameCount % FRAME_RATE;
		pFrameColl->collisions[currFrame].push_back(event.collisionData);
	}
}
