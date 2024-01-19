#pragma once

#include "NullEventBus.hpp"
#include "iEventBus.h"

namespace MyEngine
{
	template <typename T, typename F>
	class EventBusLocator
	{
	public:
		static iEventBus<T, F>* Get() { return m_eventBus; }

		static void Set(iEventBus<T, F>* eventBus)
		{
			if (eventBus == nullptr)
			{
				m_eventBus = &m_nullService;
			}
			else
			{
				m_eventBus = eventBus;
			}
		}

	private:
		static iEventBus<T, F>* m_eventBus;
		static NullEventBus<T, F> m_nullService;
	};

	template <typename T, typename F>
	NullEventBus<T, F> EventBusLocator<T, F>::m_nullService = NullEventBus<T, F>();
	template <typename T, typename F>
	iEventBus<T, F>* EventBusLocator<T, F>::m_eventBus = &(EventBusLocator<T, F>::m_nullService);
}
