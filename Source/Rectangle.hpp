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
    Rectangle(GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat* color)
        : _x(x), _y(y), _w(w), _h(h), _color(color) 
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
        std::cout << "Rectangle clicked\n";
    }

private:
    GLfloat _x, _y, _w, _h;
    GLfloat* _color;
};

#endif