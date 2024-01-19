#include "pch.h"

#include "MenuSystem.h"

#include "Engine/ECS/Scene/SceneManagerLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Utils/Files.h"

#include <imgui_internal.h>

namespace MyEngine
{
    void MenuSystem::Init()
    {
    }

    void MenuSystem::Start(Scene* pScene)
    {
    }

    void MenuSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void MenuSystem::Render(Scene* pScene)
    {
        // Open text box popup
        bool openLoadScene = false;
        bool openNewScene = false;

        if (ImGui::BeginMainMenuBar())
        {
            StateComponent* pState = CoreLocator::GetState();
            static bool isStopped = pState->currState == eStates::SIMULATION_RUNNING;

            // Disables load/new/save scene when simulation running
            if (isStopped)
            {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }

            if (ImGui::MenuItem("Load Scene"))
                openLoadScene = true;

            if (ImGui::MenuItem("New Scene"))
                openNewScene = true;

            if (ImGui::MenuItem("Save Scene"))
                m_SaveScene();

            if (isStopped)
            {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }

            if (ImGui::MenuItem("PLAY"))
                m_PlayScene();
            
            if (ImGui::MenuItem("STOP"))
                m_StopScene();

            ImGui::EndMainMenuBar();
        }

        // HACK: ImGui has a bug where the popup wont open if called from within the menubar
        m_LoadScene(openLoadScene);
        m_NewScene(openNewScene);
    }

    void MenuSystem::End(Scene* pScene)
    {
    }

    void MenuSystem::Shutdown()
    {
    }

    void MenuSystem::m_LoadScene(bool openLoadScene)
    {
        if (openLoadScene)
            ImGui::OpenPopup("Load Scene##Popup");

        static char sceneNameBuffer[256] = "";
        if (ImGui::BeginPopupModal("Load Scene##Popup",
                                    NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::InputText("Scene file name (File has to be located in default scenes folder)",
                sceneNameBuffer, IM_ARRAYSIZE(sceneNameBuffer));

            if (ImGui::Button("Load"))
            {
                iSceneManager* pSceneManager = SceneManagerLocator::Get();
                pSceneManager->ChangeScene(sceneNameBuffer, true);

                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Cancel"))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }
    }

    void MenuSystem::m_NewScene(bool openNewScene)
    {
        if (openNewScene)
            ImGui::OpenPopup("New Scene##Popup");

        static char sceneNameBuffer[256] = "";
        if (ImGui::BeginPopupModal("New Scene##Popup",
                                    NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::InputText("Scene file name (Ex: Scene01.json)",
                sceneNameBuffer, IM_ARRAYSIZE(sceneNameBuffer));

            if (ImGui::Button("New"))
            {
                iSceneManager* pSceneManager = SceneManagerLocator::Get();
                std::string filePath = pSceneManager->GetBasePath() + sceneNameBuffer;

                // Avoid overriding existing scenes
                if (FileExists(filePath))
                {
                    LOG_ERROR("Scene alread exists: " + filePath);
                    ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
                    return;
                }

                pSceneManager->CreateNewScene(sceneNameBuffer);

                pSceneManager->ChangeScene(sceneNameBuffer);

                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Cancel"))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }
    }

    void MenuSystem::m_SaveScene()
    {
        iSceneManager* pSceneManager = SceneManagerLocator::Get();

        std::string sceneName = pSceneManager->GetCurrentSceneName();
        pSceneManager->SaveScene(sceneName);

        return;
    }

    void MenuSystem::m_PlayScene()
    {
        StateComponent* pState = CoreLocator::GetState();

        if (pState->currState == eStates::SIMULATION_RUNNING)
        {
            return;
        }

        m_SaveScene();

        pState->currState = eStates::SIMULATION_RUNNING;
    }

    void MenuSystem::m_StopScene()
    {
        StateComponent* pState = CoreLocator::GetState();

        if (pState->currState == eStates::SIMULATION_STOPPED)
        {
            return;
        }

        pState->currState = eStates::SIMULATION_STOPPED;

        iSceneManager* pSceneManager = SceneManagerLocator::Get();
        std::string sceneName = pSceneManager->GetCurrentSceneName();
        pSceneManager->ChangeScene(sceneName, true);
    }
}
