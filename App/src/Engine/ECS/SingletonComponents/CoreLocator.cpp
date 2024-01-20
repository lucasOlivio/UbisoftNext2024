#include "stdafx.h"

#include "CoreLocator.h"

namespace MyEngine
{
    FrameCounterComponent* CoreLocator::m_pFrameCounter = new FrameCounterComponent();
    ConsoleComponent* CoreLocator::m_pConsole = new ConsoleComponent();

    FrameCounterComponent* CoreLocator::GetFrameCounter()
    {
        return m_pFrameCounter;
    }

    ConsoleComponent* CoreLocator::GetConsole()
    {
        return m_pConsole;
    }

    void CoreLocator::SetFrameCounter(FrameCounterComponent* pFrameCounter)
    {
        delete m_pFrameCounter;
        m_pFrameCounter = pFrameCounter;
    }

    void CoreLocator::SetConsole(ConsoleComponent* pConsole)
    {
        delete m_pConsole;
        m_pConsole = pConsole;
    }

    void CoreLocator::Clear()
    {
        delete m_pFrameCounter;
        delete m_pConsole;
    }
}
