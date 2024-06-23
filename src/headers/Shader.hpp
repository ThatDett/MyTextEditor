#ifndef SHADER_H
#define SHADER_H

#include <string_view>
#include <string>

#include "glad/glad.h"

class Shader
{
public:
    Shader(std::string_view filepath);
    ~Shader();

    void LoadFromFile(std::string_view filepath);
    void Compile();
    void Use() const;

    void SetUniform(std::string_view name, bool value) const;
    void SetUniform(std::string_view name, int value) const;
    void SetUniform(std::string_view name, float value) const;

    GLuint program;

    GLuint vertexShader;
    GLuint fragmentShader;

    const char* vertexSource;
    const char* fragmentSource;
};
#endif