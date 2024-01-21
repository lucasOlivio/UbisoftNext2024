#include "stdafx.h"

#include "CoreLocator.h"

namespace MyEngine
{
    FrameCounterComponent* CoreLocator::m_pFrameCounter = new FrameCounterComponent();

    FrameCounterComponent* CoreLocator::GetFrameCounter()
    {
        return m_pFrameCounter;
    }

    void CoreLocator::SetFrameCounter(FrameCounterComponent* pFrameCounter)
    {
        delete m_pFrameCounter;
        m_pFrameCounter = pFrameCounter;
    }

    void CoreLocator::Clear()
    {
        delete m_pFrameCounter;
    }
}
