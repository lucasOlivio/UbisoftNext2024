#pragma once

#include "Event.hpp"

namespace MyEngine
{
	enum eWindowEvents
	{
		WINDOW_RESIZE,
		WINDOW_CLOSE
	};

	class WindowResizeEvent : public Event<eWindowEvents>
	{
	public:
		WindowResizeEvent() :
			Event<eWindowEvents>(eWindowEvents::WINDOW_RESIZE, "WindowResize") {};
		virtual ~WindowResizeEvent() {};

		int width = 0, height = 0;
	};

	class WindowCloseEvent : public Event<eWindowEvents>
	{
	public:
		WindowCloseEvent() :
			Event<eWindowEvents>(eWindowEvents::WINDOW_CLOSE, "WindowClose") {};
		virtual ~WindowCloseEvent() {};
	};
}
