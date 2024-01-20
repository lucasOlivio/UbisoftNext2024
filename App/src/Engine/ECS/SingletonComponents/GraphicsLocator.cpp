#include "stdafx.h"

#include "GraphicsLocator.h"

namespace MyEngine
{
    CameraComponent* GraphicsLocator::m_pCamera = new CameraComponent();

    CameraComponent* GraphicsLocator::GetCamera()
    {
        return m_pCamera;
    }

    void GraphicsLocator::SetCamera(CameraComponent* pCamera)
    {
        delete m_pCamera;
        m_pCamera = pCamera;
    }

    void GraphicsLocator::Clear()
    {
        delete m_pCamera;
    }
}
