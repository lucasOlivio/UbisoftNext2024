#include "pch.h"

#include "GuizmoSystem.h"

#include "Utils/EntitySelector.h"
#include "Utils/UIWidgets.h"

namespace MyEngine
{
    void GuizmoSystem::Init()
    {
    }

    void GuizmoSystem::Start(Scene* pScene)
    {
    }

    void GuizmoSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void GuizmoSystem::Render(Scene* pScene)
    {
        Entity entityId = EntitySelector::GetSelectedEntity();

        Guizmo(pScene, entityId);
    }

    void GuizmoSystem::End(Scene* pScene)
    {
    }

    void GuizmoSystem::Shutdown()
    {
    }
}
