#ifndef APPLICATION_H
#define APPLICATION_H

#include "GLFW/glfw3.h"

struct Dimensions
{
    int width;
    int height;
};

class Application
{
public:
    Application();
    ~Application();

    void Run() const;
    void ProcessInput(GLFWwindow *window) const;
    void Draw(GLuint numberOfElements) const;
public:
    Dimensions windowSize;
    GLFWwindow *window;
private:
};
#endif