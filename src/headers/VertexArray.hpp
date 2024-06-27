#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "GLAD/glad.h"

class VertexArray 
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
public:
    GLuint ID;
};
#endif