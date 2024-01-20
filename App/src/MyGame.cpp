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

	Entity entityId = pScene->CreateEntity();
	TransformComponent* pTransform = pScene->AddComponent<TransformComponent>(entityId);
	pTransform->position = Vec2(400, 400);
	pTransform->angle = 0;
	pTransform->scale = 1;

	SpriteComponent* pSprite = pScene->AddComponent<SpriteComponent>(entityId);
	pSprite->name = DEFAULT_SPRITE_PATH + "zombiebasic.png";
	pSprite->cols = 6;
	pSprite->rows = 1;
	pSprite->speed = 1.0f / 30.0f;

	RotationComponent* pRotation = pScene->AddComponent<RotationComponent>(entityId);
	pRotation->velocity = -1.0f;

	Entity entityId2 = pScene->CreateEntity();
	TransformComponent* pTransform2 = pScene->AddComponent<TransformComponent>(entityId2);
	pTransform2->position = Vec2(600, 400);
	pTransform2->angle = 0;
	pTransform2->scale = 1;

	SpriteComponent* pSprite2 = pScene->AddComponent<SpriteComponent>(entityId2);
	pSprite2->name = DEFAULT_SPRITE_PATH + "Test.bmp";
	pSprite2->cols = 8;
	pSprite2->rows = 4;
	pSprite2->speed = 1.0f / 15.0f;

	// Create systems
	RenderSystem* pRenderSystem = new RenderSystem();
	MovementSystem* pMovementSystem = new MovementSystem();
	RotationSystem* pRotationSystem = new RotationSystem();

	gEngine->AddSystem(pRenderSystem, pScene);
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