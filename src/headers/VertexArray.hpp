#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "GLAD/glad.h"

class VertexArray 
{
public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();
public:
    GLuint ID;
};
#endif