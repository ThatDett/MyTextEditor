#ifndef APPLICATION_H
#define APPLICATION_H

#include "GLFW/glfw3.h"

class Application
{
public:
    ~Application();

    void Run() const;
    void ProcessInput(GLFWwindow *window) const;
    void Draw() const;
private:
};
#endif