#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <GL/gl.h>
#include <iostream>
#include "Event.hpp"
#include "EventHandler.hpp"
#include "Publisher.hpp"

class Rectangle : public Publisher
{
public:
    Rectangle(
        const char* name, 
        GLfloat x, 
        GLfloat y, 
        GLfloat w, 
        GLfloat h, 
        GLfloat* color)
        : _name(name), _x(x), _y(y), _w(w), _h(h), _color(color) 
    {
        RectangleClicked = EventHandler<const Event&>();
        RectangleClicked.Bind<&Rectangle::HandleClick>(this);
    }

    EventHandler<const Event&> RectangleClicked;

    void Render()
    {
        glColor4fv(_color);
        glRectf(_x, _y, _x + _w, _y + _h);
    }

    void HandleClick(const Event& event)
    {
        if (
            event.xpos >= _x && 
            event.xpos <= _x + _w &&
            event.ypos >= _y &&
            event.ypos <= _y + _h)
        {
            std::cout << _name << " clicked\n";
        }
    }

private:
    const char* _name;
    GLfloat _x, _y, _w, _h;
    GLfloat* _color;
};

#endif