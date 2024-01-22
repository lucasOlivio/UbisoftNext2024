#pragma once
#include "stdafx.h"

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

        virtual void Subscribe(T eventType, const EventHandler& handler) 
        {};
        virtual void Unsubscribe(T eventType, const EventHandler & handler)
        {};

        virtual void Publish(const F& event)
        {};
    };
}
