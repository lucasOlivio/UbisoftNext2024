#pragma once

#include "Engine/Utils/Vector2.h"

namespace MyEngine
{
	class TransformUtils
	{
	public:
		static Vec2 GetForwardVector(float angle);

		static bool IsOutsideWindow(const float& x, const float& y);

		static void ClipToWindow(float& x, float& y);
	};
}
