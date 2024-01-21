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

#include "Engine/Utils/GameplayUtils.h"

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

	// Setup initial scene
	Scene* pScene = pEngine->GetScene();

	GameplayUtils::CreateBackground(pScene, Vec2(512, 385));

	GameplayUtils::CreatePlayer(pScene, Vec2(512, 394));

	// Create base systems

	// Core systems
	pEngine->AddSystem(SystemFactory::CreateSystem("CoreSystem"), pScene);
	pEngine->AddSystem(SystemFactory::CreateSystem("StateSystem"), pScene);
	pEngine->AddSystem(SystemFactory::CreateSystem("FrameSystem"), pScene);
	pEngine->AddSystem(SystemFactory::CreateSystem("ParentSystem"), pScene);

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