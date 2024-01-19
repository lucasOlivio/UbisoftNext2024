#pragma once
#include "pch.h"

#include "iEventBus.h"
#include "Event.hpp"

#include <functional>
#include <unordered_map>

namespace MyEngine
{
    // Null service only to avoid crashes in locator
    template <typename T, typename F>
    class NullEventBus : public iEventBus<T, F>
    {
    private:
        using EventHandler = iEventBus<T, F>::EventHandler;

    public:
        NullEventBus() {}
        virtual ~NullEventBus() {};

        // Subscribe to an event
        virtual void Subscribe(T eventType, const EventHandler& handler) 
        {
            LOG_ERROR("EventBus not set!");
        };

        // Publish an event to all the listeners
        virtual void Publish(const F& event)
        {
            LOG_ERROR("EventBus not set!");
        };
    };
}
