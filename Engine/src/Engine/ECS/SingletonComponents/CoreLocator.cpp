#include "pch.h"

#include "CoreLocator.h"

namespace MyEngine
{
    ConfigPathComponent* CoreLocator::m_pConfigPath = new ConfigPathComponent();
    FrameCounterComponent* CoreLocator::m_pFrameCounter = new FrameCounterComponent();
    KeyInputComponent* CoreLocator::m_pKeyInput = new KeyInputComponent();
    MouseInputComponent* CoreLocator::m_pMouseInput = new MouseInputComponent();
    StateComponent* CoreLocator::m_pState = new StateComponent();

    ConfigPathComponent* CoreLocator::GetConfigPath()
    {
        return m_pConfigPath;
    }

    FrameCounterComponent* CoreLocator::GetFrameCounter()
    {
        return m_pFrameCounter;
    }

    KeyInputComponent* CoreLocator::GetKeyInput()
    {
        return m_pKeyInput;
    }

    MouseInputComponent* CoreLocator::GetMouseInput()
    {
        return m_pMouseInput;
    }

    StateComponent* CoreLocator::GetState()
    {
        return m_pState;
    }

    void CoreLocator::SetConfigPath(ConfigPathComponent* pConfigPath)
    {
        delete m_pConfigPath;
        m_pConfigPath = pConfigPath;
    }

    void CoreLocator::SetFrameCounter(FrameCounterComponent* pFrameCounter)
    {
        delete m_pFrameCounter;
        m_pFrameCounter = pFrameCounter;
    }

    void CoreLocator::SetKeyInput(KeyInputComponent* pKeyInput)
    {
        delete m_pKeyInput;
        m_pKeyInput = pKeyInput;
    }

    void CoreLocator::SetMouseInput(MouseInputComponent* pMouseInput)
    {
        delete m_pMouseInput;
        m_pMouseInput = pMouseInput;
    }

    void CoreLocator::SetState(StateComponent* pState)
    {
        delete m_pState;
        m_pState = pState;
    }

    void CoreLocator::Clear()
    {
        delete m_pConfigPath;
        delete m_pFrameCounter;
        delete m_pKeyInput;
        delete m_pState;
    }
}
