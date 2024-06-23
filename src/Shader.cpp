#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <sstream>
#include <cstring>

#include "Shader.hpp"

Shader::Shader(std::string_view filepath, bool shouldAttach) :
    vertexShader(glCreateShader(GL_VERTEX_SHADER)),
    fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
    vertexSource("null"), fragmentSource("null")
{
    std::ifstream file(filepath.data());

    if (file.fail()) { 
        std::cerr << "Error details: " << filepath.data() << ": " << strerror(errno) << std::endl; 
    } 

    enum class ShaderType
    {
        NONE = -1, FRAGMENT = 0, VERTEX = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType shaderType = ShaderType::NONE;
    while(std::getline(file, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)shaderType] << line << std::endl;
        }
    }

    vertexSource   = ss[(int)ShaderType::VERTEX].str().c_str();
    fragmentSource = ss[(int)ShaderType::FRAGMENT].str().c_str();

    Compile();

    if (shouldAttach)
    {
        glUseProgram(program);
    }
}

void Shader::Compile()
{
    if (vertexSource == "null" || fragmentSource == "null")
    {
        std::cout << "Shader::Compile: Nothing to compile\n";
        exit(EXIT_FAILURE);
    }

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
    }

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
}