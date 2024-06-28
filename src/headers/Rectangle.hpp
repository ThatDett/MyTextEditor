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
    Rectangle(glm::vec2 pos, GLuint width, GLuint height, glm::vec3 color);

    void Draw();
public:
    glm::vec2 pos;
    glm::vec3 color;
private:
    GLuint m_width;
    GLuint m_height;

    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;

    Shader rectShader;
private:
};
#endif
