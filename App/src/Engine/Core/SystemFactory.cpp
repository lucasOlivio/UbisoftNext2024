#include "stdafx.h"
#include "SystemFactory.h"

#include "Engine/Core/FrameSystem.h"
#include "Engine/Core/StateSystem.h"
#include "Engine/Core/CoreSystem.h"
#include "Engine/Core/ParentSystem.h"
#include "Engine/Core/MediaPlayerSystem.h"

#include "Engine/Graphics/RenderSystem.h"

#include "Engine/Debug/ConsoleSystem.h"
#include "Engine/Debug/DrawGridSystem.h"

#include "Engine/Physics/MovementSystem.h"
#include "Engine/Physics/RotationSystem.h"
#include "Engine/Physics/BroadPhase/GridBroadPhaseSystem.h"
#include "Engine/Physics/NarrowPhase/CollisionSystem.h"

#include "Engine/Gameplay/PlayerControllerSystem.h"
#include "Engine/Gameplay/TruckControllerSystem.h"
#include "Engine/Gameplay/ZombieSpawnSystem.h"
#include "Engine/Gameplay/FollowTargetSystem.h"
#include "Engine/Gameplay/DestructionSystem.h"
#include "Engine/Gameplay/ScoreSystem.h"
#include "Engine/Gameplay/PlayerHealthSystem.h"
#include "Engine/Gameplay/LevelSystem.h"

#include "Engine/Gameplay/UI/PlayerUISystem.h"
#include "Engine/Gameplay/UI/GameStateUISystem.h"

namespace MyEngine
{
    iSystem* SystemFactory::CreateSystem(std::string systemName)
    {
        if (systemName == "FrameSystem") {
            return new FrameSystem();
        }
        else if (systemName == "StateSystem") {
            return new StateSystem();
        }
        else if (systemName == "CoreSystem") {
            return new CoreSystem();
        }
        else if (systemName == "ParentSystem") {
            return new ParentSystem();
        }
        else if (systemName == "MediaPlayerSystem") {
            return new MediaPlayerSystem();
        }
        else if (systemName == "RenderSystem") {
            return new RenderSystem();
        }
        else if (systemName == "ConsoleSystem") {
            return new ConsoleSystem();
        }
        else if (systemName == "DrawGridSystem") {
            return new DrawGridSystem();
        }
        else if (systemName == "MovementSystem") {
            return new MovementSystem();
        }
        else if (systemName == "RotationSystem") {
            return new RotationSystem();
        }
        else if (systemName == "GridBroadPhaseSystem") {
            return new GridBroadPhaseSystem();
        }
        else if (systemName == "CollisionSystem") {
            return new CollisionSystem();
        }
        else if (systemName == "PlayerControllerSystem") {
            return new PlayerControllerSystem();
        }
        else if (systemName == "TruckControllerSystem") {
            return new TruckControllerSystem();
        }
        else if (systemName == "ZombieSpawnSystem") {
            return new ZombieSpawnSystem();
        }
        else if (systemName == "FollowTargetSystem") {
            return new FollowTargetSystem();
        }
        else if (systemName == "DestructionSystem") {
            return new DestructionSystem();
        }
        else if (systemName == "ScoreSystem") {
            return new ScoreSystem();
        }
        else if (systemName == "PlayerHealthSystem") {
            return new PlayerHealthSystem();
        }
        else if (systemName == "LevelSystem") {
            return new LevelSystem();
        }
        else if (systemName == "PlayerUISystem") {
            return new PlayerUISystem();
        }
        else if (systemName == "GameStateUISystem") {
            return new GameStateUISystem();
        }
        else {
            LOG_WARNING("System '" + systemName + "' unknown!");
            return nullptr;
        }
    }
}
