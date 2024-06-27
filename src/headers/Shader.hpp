#ifndef SHADER_H
#define SHADER_H

#include <string_view>
#include <string>

#include "glad/glad.h"
#include <glm.hpp>

class Shader
{
public:
    Shader(std::string_view filepath);
    ~Shader();

    void Use() const;

    void SetUniform(std::string_view name, bool value) const;
    void SetUniform(std::string_view name, int value) const;
    void SetUniform(std::string_view name, float value) const;

public:
    GLuint program;

    GLuint vertexShader;
    GLuint fragmentShader;

    const char *vertexSource;
    const char *fragmentSource;
    
private:
    void LoadFromFile(std::string_view filepath);
    void Compile();

private:
    std::string *vertexPtr, *fragmentPtr;
};
#endif