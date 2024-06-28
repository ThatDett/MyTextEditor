#include <iostream>

#include "Renderer.hpp"

Renderer::Renderer() :
    shader("../src/shaders/shader.glsl"), font("../res/BaskervilleBT.ttf", 0, 24)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Renderer::Renderer(const Shader &shader, const Font &font) :
    shader(shader), font(font)
{}

Renderer& Renderer::DrawText(std::string_view text, glm::vec2 pos, const glm::vec4 &color, float scale)
{
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    shader.Use();

    std::string_view::const_iterator c = text.begin();
    for (GLuint i = 0; c != text.end(); ++c, ++i)
    {
        DrawChar(*c, pos, color, scale);
        pos.x += (font.Characters[*c].Advance.x >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return *this;
}

void Renderer::DrawChar(char c, glm::vec2 pos, const glm::vec4 &color, float scale)
{
    glUniform3f(glGetUniformLocation(shader.program, "textColor"), color.x, color.y, color.z);
    
    Character &ch = font.Characters[c];

    float xpos = pos.x + ch.Bearing.x * scale;
    float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

    float w = ch.Size.x * scale;
    float h = ch.Size.y * scale;

    float vertices[6][4] = {
        { xpos,     ypos + h,   0.0f, 0.0f },            
        { xpos,     ypos,       0.0f, 1.0f },
        { xpos + w, ypos,       1.0f, 1.0f },
        { xpos,     ypos + h,   0.0f, 0.0f },
        { xpos + w, ypos,       1.0f, 1.0f },
        { xpos + w, ypos + h,   1.0f, 0.0f }           
    };

    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glDrawArrays(GL_TRIANGLES, 0, 6);

    pos.x += (ch.Advance.x >> 6) * scale; 
    glBindTexture(GL_TEXTURE_2D, 0);
}