#include "Window.hpp"

int main(int argc, char *argv[])
{
    std::unique_ptr<Window> window = std::make_unique<Window>(1024, 768, false);
    window->MessageLoop();
    return 0;
}