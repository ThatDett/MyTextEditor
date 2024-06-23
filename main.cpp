#include <iostream>

#include "GLFW/glfw3.h"

#include "Application.hpp"

int main()
{
    Application application;
    application.Run();
    
    std::cout << "Terminated\n";
    return EXIT_SUCCESS;
}