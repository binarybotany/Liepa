#ifndef Window_hpp
#define Window_hpp

#include <GL/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <list>

#include "Globals.hpp"
#include "Event.hpp"
#include "Publisher.hpp"
#include "Rectangle.hpp"

class Window : public Publisher
{
private:
    static void ErrorCallback(int error, const char *description);

    static void KeyCallback(
        GLFWwindow* window, 
        int key, 
        int scancode, 
        int action, 
        int mods
    );

    static void ResizeCallback(GLFWwindow *window, int width, int height);

    std::list<Rectangle*> _rectangles;

public:
    Window(int width, int height, bool fullscreen);
    ~Window();

    void MessageLoop();
};

#endif