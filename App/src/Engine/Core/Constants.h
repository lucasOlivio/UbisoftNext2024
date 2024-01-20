#pragma once

#include "Engine/Utils/Vector2.h"

#include <string>

namespace MyEngine
{
#define MAX_LINE_LENGTH 65536		// 16x1024

	const std::string DEFAULT_SPRITE_PATH = ".\\assets\\sprites\\";
	const std::string DEFAULT_AUDIO_PATH = ".\\assets\\audios\\";

	const Vec2 UP_VECTOR = Vec2(0, 1);
	const Vec2 FORWARD_VECTOR = Vec2(1, 0);

	const int   FRAME_RATE = 60;  // Frames per second
	const float FRAME_DURATION = 1.0f / (float)FRAME_RATE;

	const float RED[] = {1.0f, 0.0f, 0.0f};
	const float GREEN[] = { 0.0f, 1.0f, 0.0f };
	const float BLUE[] = { 0.0f, 0.0f, 1.0f };
	const float YELLOW[] = { 1.0f, 1.0f, 0.0f };
}