#ifndef Publisher_hpp
#define Publisher_hpp

#include <list>
#include "Subscriber.hpp"

enum class Event
{
    Default = 0,
};

class Publisher 
{
public:
    ~Publisher() { }

    void Subscribe(Subscriber* subscriber) 
    {
        _subscribers.push_back(subscriber);
    }

    void Unsubscribe(Subscriber* subscriber)
    {
        _subscribers.remove(subscriber);
    }

    void Notify()
    {
        for (
            std::list<Subscriber*>::iterator iter = _subscribers.begin(); 
            iter != _subscribers.end(); 
            iter++) 
        {
            EventArgs e;
            (*iter)->handler(e);
        }
    }

private:
    std::list<Subscriber*> _subscribers;
};

#endif