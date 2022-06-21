#ifndef Publisher_hpp
#define Publisher_hpp

#include <iostream>
#include "Delegate.hpp"
#include "Event.hpp"

class Publisher
{
public:
    void RaiseEvent(Event event) 
    {
        std::cout << "Pressed" << std::endl;
    }
};

#endif