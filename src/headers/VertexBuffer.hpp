#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "GLAD/glad.h"

class VertexBuffer
{
public:
    VertexBuffer(GLfloat *data, size_t bufferSize);
    ~VertexBuffer();

    void Bind() const;
    void SendData(GLenum bufferMode = GL_STATIC_DRAW) const;    
    void Unbind() const;
public:
    GLfloat *data;
    size_t bufferSize;
    GLuint ID;
};
#endif