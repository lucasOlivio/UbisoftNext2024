#include "pch.h"

#include "PhysicsLocator.h"

namespace MyEngine
{
    NarrowPhaseTestsComponent* PhysicsLocator::m_pNarrowPhaseTests = new NarrowPhaseTestsComponent();
    GridBroadphaseComponent* PhysicsLocator::m_pGridBroadphase = new GridBroadphaseComponent();
    FrameCollisionComponent* PhysicsLocator::m_pFrameCollision = new FrameCollisionComponent();

    NarrowPhaseTestsComponent* PhysicsLocator::GetNarrowPhaseTests()
    {
        return m_pNarrowPhaseTests;
    }

    GridBroadphaseComponent* PhysicsLocator::GetGridBroadphase()
    {
        return m_pGridBroadphase;
    }

    FrameCollisionComponent* PhysicsLocator::GetFrameCollision()
    {
        return m_pFrameCollision;
    }

    void PhysicsLocator::SetNarrowPhaseTests(NarrowPhaseTestsComponent* pNarrowPhaseTests)
    {
        delete m_pNarrowPhaseTests;
        m_pNarrowPhaseTests = pNarrowPhaseTests;
    }

    void PhysicsLocator::SetGridBroadphase(GridBroadphaseComponent* pGridBroadphase)
    {
        delete m_pGridBroadphase;
        m_pGridBroadphase = pGridBroadphase;
    }

    void PhysicsLocator::SetFrameCollision(FrameCollisionComponent* pFrameCollision)
    {
        delete m_pFrameCollision;
        m_pFrameCollision = pFrameCollision;
    }

    void PhysicsLocator::Clear()
    {
        delete m_pNarrowPhaseTests;
        delete m_pGridBroadphase;
        delete m_pFrameCollision;
    }
}
