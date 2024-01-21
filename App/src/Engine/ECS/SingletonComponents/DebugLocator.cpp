#include "stdafx.h"

#include "DebugLocator.h"

namespace MyEngine
{
    ConsoleComponent* DebugLocator::m_pConsole = new ConsoleComponent();

    ConsoleComponent* DebugLocator::GetConsole()
    {
        return m_pConsole;
    }

    void DebugLocator::SetConsole(ConsoleComponent* pConsole)
    {
        delete m_pConsole;
        m_pConsole = pConsole;
    }

    void DebugLocator::Clear()
    {
        delete m_pConsole;
    }
}
