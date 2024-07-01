#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "glm.hpp"

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

class Rectangle
{
public:
    Rectangle();
    Rectangle(glm::vec2 pos, int width, int height, glm::vec4 color = glm::vec4(1.0f));

    void Draw();
public:
    glm::vec2 pos;
    glm::vec2 lastpos;
    glm::vec3 color;

    int width;
    int height;
private:
    int lastWidth;
    int lastHeight;

    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;

    Shader rectShader;
private:
};
#endif
