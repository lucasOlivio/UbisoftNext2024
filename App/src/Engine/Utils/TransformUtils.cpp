#include "stdafx.h"

#include "TransformUtils.h"

#include <AppSettings.h>

namespace MyEngine
{
    Vec2 TransformUtils::GetForwardVector(float angle)
    {
        float angleRadians = angle * PI / 180.0f;

        // Calculate the forward vector based on the angle
        float forwardX = std::cos(angleRadians);
        float forwardY = std::sin(angleRadians);

        return Vec2(forwardX, forwardY);
    }
}
