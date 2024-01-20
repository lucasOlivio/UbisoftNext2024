#pragma once

#include "iEventBus.h"
#include "Event.hpp"
#include <functional>
#include <unordered_map>

namespace MyEngine
{
    // Null service only to avoid crashes in locator
    template <typename T>
    class NullEventBus : public iEventBus<T>
    {
    private:
        using EventHandler = iEventBus<T>::EventHandler;

    public:
        NullEventBus() {}
        virtual ~NullEventBus() {};

        // Subscribe to an event
        virtual void Subscribe(T eventType, const EventHandler& handler) {};

        // Publish an event to all the listeners
        virtual void Publish(const Event<T>& event) {};
    };
}
