#pragma once

#include "Event.hpp"

#include <functional>

namespace MyEngine
{
    template <typename T, typename F>
    class iEventBus
    {
    protected:
        using EventHandler = std::function<void(const F&)>;

    public:
        iEventBus() {}
        virtual ~iEventBus() {};

        // Subscribe to an event
        virtual void Subscribe(T eventType, const iEventBus::EventHandler& handler) = 0;
        // Unsubscribe from event
        virtual void Unsubscribe(T eventType, const iEventBus::EventHandler& handler) = 0;

        // Publish an event to all the listeners
        virtual void Publish(const F& event) = 0;
    };
}
