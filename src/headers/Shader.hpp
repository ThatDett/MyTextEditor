#ifndef SHADER_H
#define SHADER_H

#include <string_view>
#include <string>
#include <unordered_map>

#include "glad/glad.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(std::string_view filepath);
    ~Shader();

    void Use() const;

    void SetUniform(std::string_view name, bool value);
    void SetUniform(std::string_view name, int value);
    void SetUniform(std::string_view name, unsigned int value);
    void SetUniform(std::string_view name, float value);
    void SetMat4(std::string_view name, const glm::mat4 &matrix);

    GLuint GetUniformLocation(std::string_view name);

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
    std::unordered_map<std::string_view, GLuint> locationCache;
    std::string *vertexPtr, *fragmentPtr;
};
#endif