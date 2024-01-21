//------------------------------------------------------------------------
// MyGame.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <app.h>
//------------------------------------------------------------------------
#include "Engine/Core/Engine.h"
#include "Engine/Debug/ConsoleSystem.h"
#include "Engine/Core/FrameSystem.h"

#include "Engine/ECS/Components.h"

#include "Engine/Graphics/RenderSystem.h"

#include "Engine/Physics/MovementSystem.h"
#include "Engine/Physics/RotationSystem.h"

#include "Engine/Gameplay/PlayerControllerSystem.h"
#include "Engine/Gameplay/ZombieSpawnSystem.h"
#include "Engine/Gameplay/FollowTargetSystem.h"
#include "Engine/Gameplay/ProjectileSystem.h"

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
	pRigidBody->bodyType = eBody::DYNAMIC;
	pRigidBody->radius = 25.0f;

	// Create systems

	// Graphics systems
	RenderSystem* pRenderSystem = new RenderSystem();

	gEngine->AddSystem(pRenderSystem, pScene);
	
	// Physics systems
	MovementSystem* pMovementSystem = new MovementSystem();
	RotationSystem* pRotationSystem = new RotationSystem();

	gEngine->AddSystem(pMovementSystem, pScene);
	gEngine->AddSystem(pRotationSystem, pScene);

	// Gameplay systems
	PlayerControllerSystem* pPlayerControllerSystem = new PlayerControllerSystem();
	ZombieSpawnSystem* pZombieSpawnSystem = new ZombieSpawnSystem();
	FollowTargetSystem* pFollowTargetSystem = new FollowTargetSystem();
	ProjectileSystem* pProjectileSystem = new ProjectileSystem();

	gEngine->AddSystem(pPlayerControllerSystem, pScene);
	gEngine->AddSystem(pZombieSpawnSystem, pScene);
	gEngine->AddSystem(pFollowTargetSystem, pScene);
	gEngine->AddSystem(pProjectileSystem, pScene);

	// Core systems
	FrameSystem* pFrameSystem = new FrameSystem();

	gEngine->AddSystem(pFrameSystem, pScene);

#ifdef _DEBUG
	// Debug systems
	ConsoleSystem* pConsoleSystem = new ConsoleSystem();

	gEngine->AddSystem(pConsoleSystem, pScene);
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