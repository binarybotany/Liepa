#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <GL/gl.h>
#include <iostream>

class Rectangle 
{
public:
    Rectangle(GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat* color)
        : _x(x), _y(y), _w(w), _h(h), _color(color) { }

    void Render()
    {
        glColor4fv(_color);
        glRectf(_x, _y, _x + _w, _y + _h);
    }

private:
    GLfloat _x, _y, _w, _h;
    GLfloat* _color;
};

#endif