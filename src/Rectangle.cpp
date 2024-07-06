#include "Rectangle.hpp"

float rectVertices[] =
{
    1.0f,  0.0f, 0.0f, //TR
    0.0f,  0.0f, 0.0f, //TL
    0.0f,  1.0f, 0.0f, //BL
    1.0f,  1.0f, 0.0f, //BR
};

GLuint indices[] = {0, 1, 2, 2, 3, 0};

Rectangle::Rectangle() :
    color(glm::vec4(1.0f)),
    vbo(rectVertices, sizeof(rectVertices)), ibo(indices, sizeof(indices)),
    rectShader("../res/shaders/rectangle.glsl")
{
    Initialize();
}

Rectangle::Rectangle(glm::vec2 pos, int width, int height, glm::vec4 color) :
    pos(pos), color(color), width(width), height(height),
    vbo(rectVertices, sizeof(rectVertices)), ibo(indices, sizeof(indices)),
    rectShader("../res/shaders/rectangle.glsl")
{
    Initialize();
}

void Rectangle::Initialize()
{
    vao.Bind();
    vbo.Bind().SendData();
    ibo.Bind().SendData();
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3 * 2, rectVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    rectShader.Use();
    rectShader.SetMat4("u_projection", glm::ortho(0.0f, 1366.0f, 768.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
    model = glm::scale(model, glm::vec3((float)width, (float)height, 1.0f));

    rectShader.SetMat4("u_model", model);
    ChangeColor(color);

    vbo.Unbind();
    ibo.Unbind();
    vao.Unbind();
}

Rectangle& Rectangle::ChangeColor(const glm::vec4 &color)
{
    this->color = color;

    rectShader.Use();
    rectShader.SetVec4("u_color", color.x, color.y, color.z, color.w);
    return *this;
}

void Rectangle::Draw()
{
    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    rectShader.Use();

    if (lastpos != pos || lastWidth != width || lastHeight != height)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
        model = glm::scale(model, glm::vec3((float)width, (float)height, 1.0f));

        rectShader.SetMat4("u_model", model);
        lastpos = pos;
        lastWidth = width;
        lastWidth = height;
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    vbo.Unbind();
    ibo.Bind();
    vao.Unbind();
}
