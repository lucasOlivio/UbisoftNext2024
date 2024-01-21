//------------------------------------------------------------------------
// MyGame.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <app.h>
//------------------------------------------------------------------------
#include "Engine/Core/Engine.h"
#include "Engine/Core/FrameSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Graphics/RenderSystem.h"

#include "Engine/Physics/MovementSystem.h"
#include "Engine/Physics/RotationSystem.h"
#include "Engine/Physics/BroadPhase/GridBroadPhaseSystem.h"
#include "Engine/Physics/NarrowPhase/CollisionSystem.h"

#include "Engine/Debug/ConsoleSystem.h"
#include "Engine/Debug/DrawGridSystem.h"

#include "Engine/Gameplay/PlayerControllerSystem.h"
#include "Engine/Gameplay/ZombieSpawnSystem.h"
#include "Engine/Gameplay/FollowTargetSystem.h"
#include "Engine/Gameplay/DestructionSystem.h"
#include "Engine/Gameplay/ScoreSystem.h"
#include "Engine/Gameplay/PlayerHealthSystem.h"
#include "Engine/Gameplay/StateSystem.h"
#include "Engine/Gameplay/UI/PlayerUISystem.h"
#include "Engine/Gameplay/UI/GameStateUISystem.h"

#include "Engine/Utils/Random.h"

MyEngine::Engine* gEngine;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	using namespace MyEngine;

	gEngine = new Engine();

	// Initialize engine
	gEngine->Init();

	// Setup scene
	Scene* pScene = gEngine->GetScene();

	// Background
	Entity entityIdbackground = pScene->CreateEntity();
	TransformComponent* pTransformBackground = pScene->AddComponent<TransformComponent>(entityIdbackground);
	pTransformBackground->position = Vec2(512, 385);
	pTransformBackground->angle = 0;
	pTransformBackground->scale = 1;

	SpriteComponent* pSpriteBackground = pScene->AddComponent<SpriteComponent>(entityIdbackground);
	pSpriteBackground->name = DEFAULT_SPRITE_PATH + "background.jpg";
	pSpriteBackground->cols = 1;
	pSpriteBackground->rows = 1;
	pSpriteBackground->speed = 1.0f;

	// Player
	Entity entityId = pScene->CreateEntity();
	TagComponent* pTag = pScene->AddComponent<TagComponent>(entityId);
	pTag->name = "Player";

	TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(entityId);
	pTransform->position = Vec2(512, 394);
	pTransform->angle = 0.0f;
	pTransform->scale = 1;

	SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(entityId);
	pSprite->name = DEFAULT_SPRITE_PATH + "player.png";
	pSprite->cols = 1;
	pSprite->rows = 1;
	pSprite->speed = 1.0f;

	RotationComponent* pRotation = pScene->AddComponent<RotationComponent>(entityId);
	pRotation->acceleration = 0.0f;
	pRotation->velocity = 0.0f;

	MovementComponent* pMovement = pScene->AddComponent<MovementComponent>(entityId);
	pMovement->acceleration = Vec2(0.0f, 0.0f);
	pMovement->velocity = Vec2(0.0f, 0.0f);

	PlayerComponent* pPlayer = pScene->AddComponent<PlayerComponent>(entityId);

	RigidBodyComponent* pRigidBody = pScene->AddComponent<RigidBodyComponent>(entityId);
	pRigidBody->bodyType = eBody::ACTIVE;
	pRigidBody->radius = 25.0f;

	// Create systems

	// Graphics systems
	RenderSystem* pRenderSystem = new RenderSystem();

	gEngine->AddSystem(pRenderSystem, pScene);
	
	// Physics systems
	MovementSystem* pMovementSystem = new MovementSystem();
	RotationSystem* pRotationSystem = new RotationSystem();
	GridBroadPhaseSystem* pGridBroadPhaseSystem = new GridBroadPhaseSystem();
	CollisionSystem* pCollisionSystem = new CollisionSystem();

	gEngine->AddSystem(pMovementSystem, pScene);
	gEngine->AddSystem(pRotationSystem, pScene);
	gEngine->AddSystem(pGridBroadPhaseSystem, pScene);
	gEngine->AddSystem(pCollisionSystem, pScene);

	// Gameplay systems
	PlayerControllerSystem* pPlayerControllerSystem = new PlayerControllerSystem();
	ZombieSpawnSystem* pZombieSpawnSystem = new ZombieSpawnSystem();
	FollowTargetSystem* pFollowTargetSystem = new FollowTargetSystem();
	DestructionSystem* pDestructionSystem = new DestructionSystem();
	ScoreSystem* pScoreSystem = new ScoreSystem();
	PlayerHealthSystem* pPlayerHealthSystem = new PlayerHealthSystem();
	StateSystem* pStateSystem = new StateSystem();

	PlayerUISystem* pPlayerUISystem = new PlayerUISystem();
	GameStateUISystem* pGameStateUISystem = new GameStateUISystem();

	gEngine->AddSystem(pPlayerControllerSystem, pScene);
	gEngine->AddSystem(pZombieSpawnSystem, pScene);
	gEngine->AddSystem(pFollowTargetSystem, pScene);
	gEngine->AddSystem(pDestructionSystem, pScene);
	gEngine->AddSystem(pScoreSystem, pScene);
	gEngine->AddSystem(pPlayerHealthSystem, pScene);
	gEngine->AddSystem(pStateSystem, pScene);

	gEngine->AddSystem(pPlayerUISystem, pScene);
	gEngine->AddSystem(pGameStateUISystem, pScene);

	// Core systems
	FrameSystem* pFrameSystem = new FrameSystem();

	gEngine->AddSystem(pFrameSystem, pScene);

#ifdef _DEBUG
	// Debug systems
	ConsoleSystem* pConsoleSystem = new ConsoleSystem();
	DrawGridSystem* pDrawGridSystem = new DrawGridSystem();

	gEngine->AddSystem(pConsoleSystem, pScene);
	gEngine->AddSystem(pDrawGridSystem, pScene);
#endif

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	gEngine->Update(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	gEngine->Render();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	gEngine->Shutdown();
}