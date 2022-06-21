#include "Window.hpp"

using std::cerr;
using std::cout;
using std::endl;

Window::Window(int width, int height, bool fullscreen)
{
    Globals<bool>::Instance().Set(FULLSCREEN, fullscreen);
    Globals<int>::Instance()
        .Set(WINDOW_WIDTH, width)
        .Set(WINDOW_HEIGHT, height);

    if (!glfwInit())
        ErrorCallback(-1, "Unable to initialize GLFW");

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    GLFWwindow *window = glfwCreateWindow(
        width,
        height,
        "Liepa",
        fullscreen ? glfwGetPrimaryMonitor() : nullptr,
        nullptr);

    if (!window)
        ErrorCallback(-1, "Unable to create window");

    Globals<GLFWwindow *>::Instance().Set(WINDOW, window);

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    Globals<int>::Instance().Set(REFRESH_RATE, videoMode->refreshRate);

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetWindowSizeCallback(window, ResizeCallback);
    glfwSwapInterval(1);

    Globals<Window*>::Instance().Set(PUBLISHER, this);

    ResizeCallback(window, width, height);
}

Window::~Window()
{
    glfwDestroyWindow(Globals<GLFWwindow *>::Instance().Get(WINDOW));
    glfwTerminate();

    _rectangles.clear();
}

void Window::ErrorCallback(int error, const char *description)
{
    cerr << description << endl;
    exit(EXIT_FAILURE);
}

void Window::KeyCallback(
    GLFWwindow *window,
    int key,
    int scancode,
    int action,
    int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        Globals<Window*>::Instance().Get(PUBLISHER)->
            RaiseEvent(Event::KeyPress);
}

void Window::ResizeCallback(GLFWwindow *window, int width, int height)
{
    if (height == 0) height = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (double)width, (double)height, 0.0, -10.0, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Window::MessageLoop()
{
    GLFWwindow *window = Globals<GLFWwindow *>::Instance().Get(WINDOW);

    GLfloat c1[4] = {0.2f, 0.2f, 0.4f, 1.0f};
    GLfloat c2[4] = {0.2f, 0.2f, 0.7f, 1.0f};

    Rectangle* rectangle1 = new Rectangle(10.0f, 10.0f, 300.0f, 150.0f, c1);
    Rectangle* rectangle2 = new Rectangle(10.0f, 320.0f, 300.0f, 150.0f, c2);

    _rectangles.push_back(rectangle1);
    _rectangles.push_back(rectangle2);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        std::list<Rectangle*>::iterator iterator = _rectangles.begin();
        while (iterator != _rectangles.end()) 
        {
            (*iterator)->Render();
            iterator++;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}