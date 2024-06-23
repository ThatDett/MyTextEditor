#include <string_view>
#include <string>

#include "glad/glad.h"

class Shader
{
public:
                                      //Should use the program it generates as soon as it compiles
    Shader(std::string_view filepath, bool shouldAttach = true);

    void Compile();

    GLuint program;

    GLuint vertexShader;
    GLuint fragmentShader;

    const char* vertexSource;
    const char* fragmentSource;
};