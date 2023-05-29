#pragma once

#include <vector>

// Event class representing a specific event
class Event {
public:
    Event() {}
    virtual ~Event() {}
};

// EventListener class representing a listener that can handle events
class EventListener {
public:
    virtual ~EventListener() {}
    virtual void onEvent(Event* event) = 0;
};

// EventManager class responsible for managing events and listeners
class EventManager {
public:

    static EventManager* instance;

    static EventManager* Get()
    {
        if (instance)
            return instance;
        
    	return new EventManager;
    }

    void addListener(EventListener* listener) {
        listeners.push_back(listener);
    }

    void removeListener(EventListener* listener) {
        // Find and remove the listener from the list
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }

    void dispatchEvent(Event* event) {
        for (auto listener : listeners) {
            listener->onEvent(event);
        }
    }

private:
    //EventManager::EventManager() {};
    std::vector<EventListener*> listeners;
};