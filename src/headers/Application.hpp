#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.hpp"

class Application
{
public:
    Application();
    ~Application();

    void Run();
    void Draw(GLuint numberOfElements) const;

public:
private:
};
#endif