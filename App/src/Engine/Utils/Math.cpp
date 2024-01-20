#include "stdafx.h"

#include "Math.h"

namespace MyEngine
{
	float Math::DegreesToRadians(float degrees)
	{
		return degrees * PI / 180.0f;
	}
}