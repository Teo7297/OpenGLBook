#include "SimpleActionEvent.h"


SimpleActionEventListener::SimpleActionEventListener(void (*func)())
	: m_Callback(func)
{
	
}

void SimpleActionEventListener::onEvent(Event* event)
{
    SimpleActionEvent* action = dynamic_cast<SimpleActionEvent*>(event);
    if (action)
    {
        m_Callback();
    }
}



