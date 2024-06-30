#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <string_view>

#include "GLFW/glfw3.h"

class Window
{
public:
    void PreCreate();
    void Create(int width, int height, const char *name);

    Window(const char *name, GLuint width, GLuint height);    

    //Automatically gets the monitor resolution
    Window(const char *name);   

public: 
    std::string name;
    GLuint width;
    GLuint height;

    unsigned int screenWidth;
    unsigned int screenHeight;

    GLFWwindow *ptr;
    GLFWmonitor *monitor;
    const GLFWvidmode *mode;

    bool fullscreen;
private:    
private:    
};
#endif