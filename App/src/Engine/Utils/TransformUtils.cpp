#include "stdafx.h"

#include "TransformUtils.h"

#include <AppSettings.h>

namespace MyEngine
{
    Vec2 TransformUtils::GetForwardVector(float angle)
    {
        // Calculate the forward vector based on the angle
        float forwardX = std::cos(angle);
        float forwardY = std::sin(angle);

        return Vec2(forwardX, forwardY).Normalize();
    }
}
