#pragma once

#include "Engine/Core/Constants.h"
#include "Engine/Core/StateProperties.h"

#include "Engine/ECS/Base.h"

#include "Engine/Physics/BroadPhase/GridAABB.h"
#include "Engine/Physics/PhysicsProperties.h"

#include "Engine/Utils/Vector2.h"

#include <map>

namespace MyEngine
{
	// Singleton components
	struct CameraComponent
	{
		Vec2 position;
	};

	struct FrameCounterComponent
	{
		int frameCount;
		float fpsTimer;
		float fps;
	};

	struct StateComponent
	{
		eStates prevState; // Only state system should modify this
		eStates currState; // Any system can modify this to stop/run simulation
	};

	struct GridBroadphaseComponent
	{
		// Mapping of AABBs to their indices in the grid
		std::map< uint /*index*/, GridAABB* > mapAABBs;

		// Length per grid box in the grid
		Vec2 lengthPerBox;
	};

	// Generic grouping for any narrow phase testing 
	struct NarrowPhaseTestsComponent
	{
		// Groups of sentities to test,
		// the static entities to be tested against the non static entities will be in the same index
		std::vector<std::vector<Entity>> staticEntitiesToTest;
		std::vector<std::vector<Entity>> nonStaticEntitiesToTest;
	};

	// All collisions that happened in the last <FRAME_RATE> frames
	struct FrameCollisionComponent
	{
		std::vector<sCollisionData> collisions[FRAME_RATE];
		size_t currSize;
	};
}