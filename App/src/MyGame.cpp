//------------------------------------------------------------------------
// MyGame.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <app.h>
//------------------------------------------------------------------------
#include "Engine/Core/Engine.h"

#include "Engine/ECS/Components.h"

#include "Engine/Graphics/RenderSystem.h"

#include "Engine/Physics/MovementSystem.h"
#include "Engine/Physics/RotationSystem.h"

#include "Engine/Gameplay/PlayerControllerSystem.h"

#include "Engine/Utils/Random.h"

MyEngine::Engine* gEngine;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	using namespace MyEngine;

	gEngine = new Engine();

	// Setup scene
	Scene* pScene = gEngine->GetScene();

	// Background
	Entity entityIdbackground = pScene->CreateEntity();
	TransformComponent* pTransformBackground = pScene->AddComponent<TransformComponent>(entityIdbackground);
	pTransformBackground->position = Vec2(512, 394);
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
	pTransform->angle = 10;
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

	// Zombie
	Entity entityId2 = pScene->CreateEntity();
	TransformComponent* pTransform2 = pScene->AddComponent<TransformComponent>(entityId2);
	pTransform2->position = Vec2(10.0f, 10.0f);
	pTransform2->angle = 0;
	pTransform2->scale = 1;

	SpriteComponent* pSprite2 = pScene->AddComponent<SpriteComponent>(entityId2);
	pSprite2->name = DEFAULT_SPRITE_PATH + "zombie.png";
	pSprite2->cols = 1;
	pSprite2->rows = 1;
	pSprite2->speed = 1.0f;

	MovementComponent* pMovement2 = pScene->AddComponent<MovementComponent>(entityId2);
	pMovement2->acceleration = Vec2(0.0f, 0.0f);
	pMovement2->velocity = Vec2(0.0f, 0.0f);

	// Create systems
	RenderSystem* pRenderSystem = new RenderSystem();
	MovementSystem* pMovementSystem = new MovementSystem();
	RotationSystem* pRotationSystem = new RotationSystem();
	PlayerControllerSystem* pPlayerControllerSystem = new PlayerControllerSystem();

	gEngine->AddSystem(pRenderSystem, pScene);
	gEngine->AddSystem(pPlayerControllerSystem, pScene);
	gEngine->AddSystem(pMovementSystem, pScene);
	gEngine->AddSystem(pRotationSystem, pScene);

	// Initialize systems
	gEngine->Init();
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