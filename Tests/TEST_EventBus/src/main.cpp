#include <gtest/gtest.h>
#include <iostream>

#include <Engine/Events/EventBus.hpp>
#include <Engine/Events/EventBusLocator.hpp>
#include <Engine/Events/WindowEvents.h>

using namespace MyEngine;

class EventBusTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up your event bus implementation
        eventBus = new EventBus<eWindowEvents, WindowCloseEvent>();
        EventBusLocator<eWindowEvents, WindowCloseEvent>::Set(eventBus);
    }

    void TearDown() override
    {
        delete eventBus;
    }

    iEventBus<eWindowEvents, WindowCloseEvent>* eventBus;
};

TEST_F(EventBusTest, SubscribeAndPublishEvent)
{
    bool eventHandled = false;

    // Subscribe to the "WINDOW_CLOSE" event
    eventBus->Subscribe(eWindowEvents::WINDOW_CLOSE, [&eventHandled](const Event<eWindowEvents>& event) {
        eventHandled = true;
        });

    // Publish the "WINDOW_CLOSE" event
    WindowCloseEvent event = WindowCloseEvent();
    eventBus->Publish(event);

    // Assert that the event was handled
    EXPECT_TRUE(eventHandled);
}

TEST_F(EventBusTest, PublishEventWithNoSubscribers)
{
    // Publish the "WINDOW_CLOSE" event
    // This should not cause any issues even if there are no subscribers
    WindowCloseEvent event = WindowCloseEvent();
    ASSERT_NO_THROW(eventBus->Publish(event));
}

TEST_F(EventBusTest, AccessUnsetEventBus)
{
    // Set the eventBus to null to simulate an unset service
    EventBusLocator<eWindowEvents, WindowCloseEvent>::Set(nullptr);
    iEventBus<eWindowEvents, WindowCloseEvent>* nullEventBus = EventBusLocator<eWindowEvents, WindowCloseEvent>::Get();

    // Attempt to publish an event without a set eventBus
    WindowCloseEvent event = WindowCloseEvent();
    ASSERT_NO_THROW(nullEventBus->Publish(event));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
