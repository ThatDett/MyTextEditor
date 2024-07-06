#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <sstream>
#include <cstring>
#include <cassert>

#include <gtc/type_ptr.hpp>

#include "Shader.hpp"

#define NOT_SET 100000 

std::unordered_map<unsigned int, unsigned int> Shader::ownershipCounter;

Shader::Shader(std::string_view filepath) :
    program(NOT_SET),
    vertexShader(glCreateShader(GL_VERTEX_SHADER)),
    fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
    filepath(filepath.data())
{
    LoadFromFile(filepath);
    Compile();
    ++ownershipCounter[program];
}

Shader::Shader(const Shader &other) :
    program(other.program),
    filepath(other.filepath),
    vertexPtr(nullptr), 
    fragmentPtr(nullptr)
{++ownershipCounter[program];}

Shader& Shader::operator =(Shader &other)
{
    program = other.program;
    filepath = other.filepath;
    ++ownershipCounter[program];
    return *this;
}

void Shader::LoadFromFile(std::string_view filepath)
{
    std::cout << "LoadFromFile: " << filepath << std::endl;
    std::ifstream file(filepath.data());

    if (file.fail()) 
    { 
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
            ss[(int)shaderType] << line << '\n';
            //test << line << '\n';
        }

        //if (shaderType == ShaderType::VERTEX)
            // std::cout << line << std::endl;
    }

    assert(shaderType != ShaderType::NONE);

    //This is possibly shit code
    vertexPtr = new std::string(ss[(int)ShaderType::VERTEX].str());
    fragmentPtr = new std::string(ss[(int)ShaderType::FRAGMENT].str());

    vertexSource = vertexPtr->c_str();
    fragmentSource = fragmentPtr->c_str();

    //std::cout << vertexSource << std::endl;
}

void Shader::Compile()
{
    // std::cout << "Shader::Compile"  << std::endl;
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

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
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

Shader::~Shader()
{
    if (ownershipCounter[program] == 1)
    {
        glDeleteProgram(program);
        // std::cout << "delete shader program: " << program << " reference count: " << ownershipCounter[program] << std::endl;
    }
    else
        --ownershipCounter[program];

    delete vertexPtr;
    delete fragmentPtr;
}

void Shader::Use() const
{
    glUseProgram(program);
}

void Shader::SetUniform(std::string_view name, bool value)
{         
    glUniform1i(GetUniformLocation(name), (int)value); 
}

void Shader::SetUniform(std::string_view name, int value)
{ 
    glUniform1i(GetUniformLocation(name), value); 
}

void Shader::SetUniform(std::string_view name, unsigned int value)
{ 
    glUniform1i(GetUniformLocation(name), value); 
}

void Shader::SetUniform(std::string_view name, float value)
{ 
    glUniform1f(GetUniformLocation(name), value); 
}

void Shader::SetVec4(std::string_view name, float x, float y, float z ,float w)
{
    glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetMat4(std::string_view name, const glm::mat4 &matrix)
{   
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)); 
}

GLuint Shader::GetUniformLocation(std::string_view name)
{
    if (locationCache.find(name) != locationCache.end())
        return locationCache[name];
    
    GLint location = glGetUniformLocation(program, name.data());
    if (location == -1)
        std::cout << "Uniform " << name.data() << " doesn't exist" << std::endl;
    else
        locationCache[name] = location;

    return location;
}
