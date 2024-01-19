#include "pch.h"

#include "DebugLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"

namespace MyEngine
{
    DebugSquareComponent* DebugLocator::m_pDebugSquare = new DebugSquareComponent();
    DebugSphereComponent* DebugLocator::m_pDebugSphere = new DebugSphereComponent();

    DebugSquareComponent* DebugLocator::GetSquare()
    {
        return m_pDebugSquare;
    }

    DebugSphereComponent* DebugLocator::GetSphere()
    {
        return m_pDebugSphere;
    }

    void DebugLocator::SetSquare(DebugSquareComponent* pDebugSquare)
    {
        delete m_pDebugSquare;
        m_pDebugSquare = pDebugSquare;
    }

    void DebugLocator::SetSphere(DebugSphereComponent* pDebugSphere)
    {
        delete m_pDebugSphere;
        m_pDebugSphere = pDebugSphere;
    }

    void DebugLocator::Clear()
    {
        delete m_pDebugSquare;
        delete m_pDebugSphere;
    }
}
