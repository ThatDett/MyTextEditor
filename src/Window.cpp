#include <iostream>

#include "glad/glad.h"
#include "Window.hpp"

void Window::PreCreate()
{
    if (!glfwInit())
    {   
        std::cout << "Fail on glfw init\n";
        exit(EXIT_FAILURE);
    }

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
 
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
}

void Window::Create(int width, int height, const char *name)
{
    ptr = glfwCreateWindow(width, height, name, monitor, NULL);
    if (!ptr)
    {
        std::cout << "Fail on window creation\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MacOS necessity

    glfwMakeContextCurrent(ptr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize Glad\n";
        exit(EXIT_FAILURE);
    }
}

Window::Window(const char *name, GLuint width, GLuint height) :
    name(name), width(width), height(height)
{
    PreCreate();
    Create(width, height, name);
}

Window::Window(const char *name) :
    name(name)
{
    PreCreate();

    width = mode->width;
    height = mode->height;
    screenWidth = height;
    screenHeight = height;

    Create(width, height, name);
}




