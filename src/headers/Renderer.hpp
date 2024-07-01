#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "glm.hpp"

#include "Shader.hpp"
#include "Font.hpp"

class Renderer
{
public:
    Renderer();
    Renderer(const Shader &shader, Font &font);

    Renderer& DrawText(const std::string &text, glm::vec2 pos, const glm::vec4 &color = glm::vec4(1.0f), float scale = 1);

public:
    Shader shader;
    Font *font;

    GLuint VAO;
    GLuint VBO;

private:
    void DrawChar(char c, glm::vec2 pos, const glm::vec4 &color = glm::vec4(1.0f), float scale = 2);
};
#endif