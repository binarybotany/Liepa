#ifndef Subscriber_hpp
#define Subscriber_hpp

#include "EventArgs.hpp"
#include "EventHandler.hpp"

class Subscriber
{
public:
    EventHandler<const EventArgs&> handler;
};

#endif