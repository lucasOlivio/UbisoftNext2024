//------------------------------------------------------------------------
// MyGame.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <app.h>
//------------------------------------------------------------------------
#include "Engine/Core/EngineLocator.h"
#include "Engine/Core/SystemFactory.h"

#include "Engine/ECS/Components.h"

#include "Engine/Utils/Random.h"

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	using namespace MyEngine;

	MyEngine::Engine* pEngine = new Engine();
	EngineLocator::Set(pEngine);

	// Initialize engine
	pEngine->Init();

	// Setup scene
	Scene* pScene = pEngine->GetScene();

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

	// Create base systems

	// Core systems
	pEngine->AddSystem(SystemFactory::CreateSystem("CoreSystem"), pScene);
	pEngine->AddSystem(SystemFactory::CreateSystem("StateSystem"), pScene);
	pEngine->AddSystem(SystemFactory::CreateSystem("FrameSystem"), pScene);

	// Graphics systems
	pEngine->AddSystem(SystemFactory::CreateSystem("RenderSystem"), pScene);

	// Gameplay systems
	pEngine->AddSystem(SystemFactory::CreateSystem("GameStateUISystem"), pScene);
	pEngine->AddSystem(SystemFactory::CreateSystem("LevelSystem"), pScene);

#ifdef _DEBUG
	// Debug systems
	pEngine->AddSystem(SystemFactory::CreateSystem("ConsoleSystem"), pScene);
	pEngine->AddSystem(SystemFactory::CreateSystem("DrawGridSystem"), pScene);
#endif
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	using namespace MyEngine;

	Engine* pEngine = EngineLocator::Get();
	pEngine->Update(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	using namespace MyEngine;

	Engine* pEngine = EngineLocator::Get();
	pEngine->Render();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	using namespace MyEngine;

	Engine* pEngine = EngineLocator::Get();
	pEngine->Shutdown();

	delete pEngine;
}