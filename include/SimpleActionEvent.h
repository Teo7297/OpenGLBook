#pragma once

#include "Event.h"


// Custom event class
class SimpleActionEvent : public Event
{
public:
    SimpleActionEvent() = default;
};

// Custom listener class
class SimpleActionEventListener : public EventListener
{
public:

    SimpleActionEventListener(void (*func)());

    void onEvent(Event* event) override;

private:
    void(*m_Callback)();
};