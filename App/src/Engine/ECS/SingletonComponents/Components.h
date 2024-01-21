#pragma once

#include "Engine/Core/Constants.h"

#include "Engine/ECS/Base.h"

#include "Engine/Gameplay/GameplayProperties.h"

#include "Engine/Physics/BroadPhase/GridAABB.h"
#include "Engine/Physics/PhysicsProperties.h"

#include "Engine/Utils/Vector2.h"

#include <map>
#include <queue>

namespace MyEngine
{
	// Core global components
	// -------------------------
	struct FrameCounterComponent
	{
		int frameCount;
		float fpsTimer;
		float fps;
	};

	// Debug global components
	// -------------------------
	struct ConsoleComponent
	{
		struct Line
		{
			float color[3];
			std::string txt;
		};
		std::queue<Line> lines;
	};

	// Physics global components
	// -------------------------
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
		// Groups of entities to test,
		// the passive entities to be tested against and the active entities will be in the same index
		std::vector<std::vector<Entity>> activeEntitiesToTest;
		std::vector<std::vector<Entity>> passiveEntitiesToTest;
	};

	// All collisions that happened in the last <FRAME_RATE> frames
	struct FrameCollisionComponent
	{
		std::set<sCollisionData> collisions[FRAME_RATE];
		size_t currSize;
	};

	// Gameplay global components
	// -------------------------
	struct ZombieSpawnComponent
	{
		float spawnRate;
		float lastSpawn;
		
		int totalZombies;
		int maxZombies;

		float spawnDistance; // Radius from window center
		float initialZombieSpeed;
	};

	struct GameStateComponent
	{
		eGameStates prevState; // Only state system should modify this
		eGameStates currState; // Any system can modify this to stop/run simulation
	};
}