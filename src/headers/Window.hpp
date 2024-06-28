#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <string_view>

#include "GLFW/glfw3.h"

class Window
{
public:
    Window(const char *name, GLuint width, GLuint height);    
public: 

    std::string name;
    GLuint width;
    GLuint height;

    GLFWwindow *ptr;
    GLFWmonitor *monitor;

    bool fullscreen;
private:    
private:    
};
#endif