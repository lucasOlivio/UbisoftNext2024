#pragma once

#include "Event.hpp"

namespace MyEngine
{
	enum eStateChangeEvents
	{
		STOPPED,
		RUNNING
	};

	class StoppedStateEvent : public Event<eStateChangeEvents>
	{
	public:
		StoppedStateEvent() :
			Event<eStateChangeEvents>(eStateChangeEvents::STOPPED, "StoppedState") {};
		virtual ~StoppedStateEvent() {};
	};

	class RunningStateEvent : public Event<eStateChangeEvents>
	{
	public:
		RunningStateEvent() :
			Event<eStateChangeEvents>(eStateChangeEvents::RUNNING, "RunningState") {};
		virtual ~RunningStateEvent() {};
	};
}
