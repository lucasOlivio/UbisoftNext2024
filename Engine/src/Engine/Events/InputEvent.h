#pragma once

#include "Event.hpp"
#include "Engine/Core/InputProperties.h"

namespace MyEngine
{
	enum eInputEvents
	{
		KEYBOARD,
		MOUSE
	};

	class KeyboardEvent : public Event<eInputEvents>
	{
	public:
		KeyboardEvent() :
			Event<eInputEvents>(eInputEvents::KEYBOARD, "Keyboard") {};
		virtual ~KeyboardEvent() {};

		sKeyData keyData;
	};

	class MouseEvent : public Event<eInputEvents>
	{
	public:
		MouseEvent() :
			Event<eInputEvents>(eInputEvents::MOUSE, "Mouse") {};
		virtual ~MouseEvent() {};

		sMouseData mouseData;
	};
}
