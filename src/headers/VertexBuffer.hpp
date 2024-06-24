#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "GLAD/glad.h"

class VertexBuffer
{
public:
    VertexBuffer(GLfloat *data, size_t bufferSize);
    ~VertexBuffer();

    void Bind();
    void Unbind();
    void SendData(GLenum bufferMode = GL_STATIC_DRAW);    
public:
    GLfloat *data;
    size_t bufferSize;
    GLuint ID;
};
#endif