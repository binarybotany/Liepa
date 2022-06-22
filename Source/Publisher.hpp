#ifndef Publisher_hpp
#define Publisher_hpp

#include <list>
#include "Event.hpp"
#include "EventType.hpp"
#include "EventHandler.hpp"

class Publisher 
{
public:
    ~Publisher() { }

    void Subscribe(
        Publisher* subscriber,
        EventType eventType, 
        EventHandler<const Event&> handler) 
    {
        Subscription subscription (
            eventType, 
            subscriber, 
            this, 
            handler);

        _subscriptions.push_back(subscription);
    }

    void Unsubscribe(EventType eventType, Publisher* subscriber)
    {
        /* Implement */
    }

    void Notify(Event event)
    {
        for (
            std::list<Subscription>::iterator iter = _subscriptions.begin(); 
            iter != _subscriptions.end(); 
            iter++) 
        {
            iter->_handler(event);
        }
    }

private:
    struct Subscription
    {
        EventType _eventType;
        Publisher* _subscriber;
        Publisher* _publisher;
        EventHandler<const Event&> _handler;

        Subscription(
            EventType eventType, 
            Publisher* subscriber, 
            Publisher* publisher, 
            EventHandler<const Event&> handler
        ) : _eventType(eventType), 
            _subscriber(publisher),
            _publisher(subscriber),
            _handler(handler) { }
    };

    std::list<Subscription> _subscriptions;
};

#endif