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

    bool TransformUtils::IsOutsideWindow(const float& x, const float& y)
    {
        if (x > APP_VIRTUAL_WIDTH)
        {
            return true;
        }
        
        if (x < 0.0f)
        {
            return true;
        }

        if (y > APP_VIRTUAL_HEIGHT)
        {
            return true;
        }
        
        if (y < 0.0f)
        {
            return true;
        }

        return false;
    }

    void TransformUtils::ClipToWindow(float& x, float& y)
    {
        if (x > APP_VIRTUAL_WIDTH)
        {
            x = APP_VIRTUAL_WIDTH;
        } else if (x < 0.0f)
        {
            x = 0.0f;
        }

        if (y > APP_VIRTUAL_HEIGHT)
        {
            y = APP_VIRTUAL_HEIGHT;
        } else if (y < 0.0f)
        {
            y = 0.0f;
        }
    }
}
