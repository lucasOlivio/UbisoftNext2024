#include "stdafx.h"

#include "CoreLocator.h"

namespace MyEngine
{
    FrameCounterComponent* CoreLocator::m_pFrameCounter = new FrameCounterComponent();
    StateComponent* CoreLocator::m_pState = new StateComponent();

    FrameCounterComponent* CoreLocator::GetFrameCounter()
    {
        return m_pFrameCounter;
    }

    StateComponent* CoreLocator::GetState()
    {
        return m_pState;
    }

    void CoreLocator::SetFrameCounter(FrameCounterComponent* pFrameCounter)
    {
        delete m_pFrameCounter;
        m_pFrameCounter = pFrameCounter;
    }

    void CoreLocator::SetState(StateComponent* pState)
    {
        delete m_pState;
        m_pState = pState;
    }

    void CoreLocator::Clear()
    {
        delete m_pFrameCounter;
        delete m_pState;
    }
}
