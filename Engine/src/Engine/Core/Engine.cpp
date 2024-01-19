#include "pch.h"

#include "Engine.h"

#include "Engine/Core/Configs/ConfigSerializerFactory.h"

#include "Engine/Events/EventBus.hpp"
#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/Scene/SceneManager.h"
#include "Engine/ECS/Scene/SceneManagerLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/ECS/SingletonComponents/DebugLocator.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"

#include "Engine/Graphics/VAO/VAOManagerLocator.h"
#include "Engine/Graphics/VAO/VAOManager.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"
#include "Engine/Graphics/Shaders/ShaderManagerLocator.h"
#include "Engine/Graphics/Materials/MaterialManager.h"
#include "Engine/Graphics/Materials/MaterialManagerLocator.h"
#include "Engine/Graphics/Textures/cBasicTextureManager.h"
#include "Engine/Graphics/Textures/TextureManagerLocator.h"

namespace MyEngine
{
    Engine::Engine()
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::AddSystem(iSystem* pSystem, Scene* pScene)
    {
        m_systems.push_back(pSystem);
        pSystem->Init();

        if (pScene)
        {
            pSystem->Start(pScene);
        }
    }

    void Engine::RemoveSystem(iSystem* pSystem, Scene* pScene)
    {
        for (int i = 0; i < m_systems.size(); i++)
        {
            if (m_systems[i] != pSystem)
            {
                continue;
            }

            iSystem* pDelSystem = m_systems[i];

            // Clean system before deleting
            if (pScene)
            {
                pDelSystem->End(pScene);
            }
            pDelSystem->Shutdown();

            m_systems.erase(m_systems.begin() + i);

            delete pDelSystem;
        }
    }

    void Engine::Init()
    {
        // Setting up events
        m_pEventBusWindow = new EventBus<eWindowEvents, WindowCloseEvent>();
        EventBusLocator<eWindowEvents, WindowCloseEvent>::Set(m_pEventBusWindow);

        m_pEventBusCollision = new EventBus<eCollisionEvents, CollisionEnterEvent>();
        EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Set(m_pEventBusCollision);

        m_pEventBusKeyboard = new EventBus<eInputEvents, KeyboardEvent>();
        EventBusLocator<eInputEvents, KeyboardEvent>::Set(m_pEventBusKeyboard);

        m_pEventBusMouse = new EventBus<eInputEvents, MouseEvent>();
        EventBusLocator<eInputEvents, MouseEvent>::Set(m_pEventBusMouse);

        m_pEventBusStoppedState = new EventBus<eStateChangeEvents, StoppedStateEvent>();
        EventBusLocator<eStateChangeEvents, StoppedStateEvent>::Set(m_pEventBusStoppedState);

        m_pEventBusRunningState = new EventBus<eStateChangeEvents, RunningStateEvent>();
        EventBusLocator<eStateChangeEvents, RunningStateEvent>::Set(m_pEventBusRunningState);

        m_pEventBusSceneChange = new EventBus<eSceneEvents, SceneChangeEvent>();
        EventBusLocator<eSceneEvents, SceneChangeEvent>::Set(m_pEventBusSceneChange);

        // Setting up resources managers
        m_pSceneManager = new SceneManager();
        SceneManagerLocator::Set(m_pSceneManager);

        m_pVAOManager = new VAOManager();
        VAOManagerLocator::Set(m_pVAOManager);

        m_pShaderManager = new ShaderManager();
        ShaderManagerLocator::Set(m_pShaderManager);

        m_pMaterialManager = new MaterialManager();
        MaterialManagerLocator::Set(m_pMaterialManager);

        m_pTextureManager = new cBasicTextureManager();
        TextureManagerLocator::Set(m_pTextureManager);

        // Global events of engine interest
        m_pEventBusSceneChange->Subscribe(eSceneEvents::CHANGE, [this](const SceneChangeEvent& event) { OnSceneChange(event); });

        // Load resources
        ConfigPathComponent* pConfigPaths = CoreLocator::GetConfigPath();
        m_pTextureManager->SetBasePath(pConfigPaths->pathTextures);
        m_pShaderManager->SetBasePath(pConfigPaths->pathShaders);
        m_pVAOManager->SetBasePath(pConfigPaths->pathModels);
        m_pSceneManager->SetBasePath(pConfigPaths->pathScenes);
    }

    void Engine::Run(std::string initialSceneName, bool startSimulation)
    {
        // TODO: Now each resource is been loaded by the systems, 
        // but they should be loaded all here and have separate files

        m_pSceneManager->ChangeScene(initialSceneName);
        if (startSimulation)
        {
            StateComponent* pState = CoreLocator::GetState();
            pState->currState = eStates::SIMULATION_RUNNING;
        }

        // TODO: Better closing proccess, should come from event
        GLFWwindow* pGLFWWindow = GraphicsLocator::GetWindow()->pGLFWWindow;

        while (!glfwWindowShouldClose(pGLFWWindow))
        {
            float deltaTime = m_GetDeltaTime();

            Update(deltaTime);

            Render();

            ClearFrame();
        }
    }

    void Engine::Update(float deltaTime)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Update(m_pCurrentScene, deltaTime);
        }
    }

    void Engine::Render()
    {
        m_BeginFrame();

        for (iSystem* pSystem : m_systems)
        {
            pSystem->Render(m_pCurrentScene);
        }

        m_EndFrame();
    }

    void Engine::Shutdown()
    {
        EndSystems(m_pCurrentScene);

        ShutdownSystems();

        for (iSystem* pSystem : m_systems)
        {
            delete pSystem;
        }

        // Delete singleton components
        CoreLocator::Clear();
        DebugLocator::Clear();
        GraphicsLocator::Clear();
        PhysicsLocator::Clear();

        // Delete resouce managers
        delete m_pEventBusWindow;
        delete m_pVAOManager;
        delete m_pShaderManager;
        delete m_pMaterialManager;
        delete m_pTextureManager;
        delete m_pSceneManager;

        // Delete event bus
        delete m_pEventBusWindow;
        delete m_pEventBusCollision;
        delete m_pEventBusKeyboard;
        delete m_pEventBusMouse;
        delete m_pEventBusStoppedState;
        delete m_pEventBusRunningState;
        delete m_pEventBusSceneChange;
    }

    void Engine::LoadConfigurations()
    {
        iConfigSerializer* pConfigSerializer = ConfigSerializerFactory::CreateConfigSerializer(DEFAULT_CONFIG);
        ConfigPathComponent* pConfigPath = CoreLocator::GetConfigPath();

        pConfigSerializer->DeserializeConfig(DEFAULT_CONFIG);
    }

    void Engine::StartSystems(Scene* pScene)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Start(pScene);
        }
    }

    void Engine::EndSystems(Scene* pScene)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->End(pScene);
        }
    }

    void Engine::ShutdownSystems()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Shutdown();
        }
    }

    void Engine::OnSceneChange(const SceneChangeEvent& event)
    {
        // End old scene
        if (m_pCurrentScene)
        {
            EndSystems(m_pCurrentScene);
        }

        // Start new scene
        m_pCurrentScene = event.pNewScene;
        StartSystems(m_pCurrentScene);
    }

    void Engine::ClearFrame()
    {
        // TODO: Resources should be separated from scenes before we can delete scenes
        /*iSceneManager* pSceneManager = SceneManagerLocator::Get();
        pSceneManager->ClearDeletedScenes();*/
    }

    float Engine::m_GetDeltaTime()
    {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        // Clamp delta time to the maximum frame time
        if (deltaTime > FRAME_DURATION) 
        {
            deltaTime = FRAME_DURATION;
        }

        // Add the frame time to the list
        m_frameTimes.push_back(deltaTime);

        // Limit the number of frames
        const size_t maxFrameCount = FRAME_RATE; // Store frame times for a second
        if (m_frameTimes.size() > maxFrameCount) 
        {
            m_frameTimes.erase(m_frameTimes.begin());
        }

        // Calculate the average frame time
        float averageFrameTime = 0;
        for (float time : m_frameTimes) 
        {
            averageFrameTime += time;
        }
        averageFrameTime /= m_frameTimes.size();

        return averageFrameTime;
    }

    void Engine::m_BeginFrame()
    {
        WindowComponent* pWindow = GraphicsLocator::GetWindow();

        // Clear frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ImGui init frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        window_flags |= ImGuiWindowFlags_NoBackground;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        // Start Imgui window context
        ImGui::Begin("ImGuiMainWindow", NULL, window_flags);

        ImGuizmo::BeginFrame();

        ImGuiIO& io = ImGui::GetIO();
        ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

        ImGuizmo::Enable(true);

        // Set default font size
        ImGui::SetWindowFontScale(TEXT_FONT_SIZE);
    }
    
    void Engine::m_EndFrame()
    {
        WindowComponent* pWindow = GraphicsLocator::GetWindow();
        
        // ImGui endframe
        ImGui::End();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)pWindow->width, (float)pWindow->height);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        // GLFW endframe
        glfwSwapBuffers(pWindow->pGLFWWindow);
        glfwPollEvents();

        // 
    }
}
