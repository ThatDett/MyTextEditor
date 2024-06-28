#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "GLAD/glad.h"

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(GLfloat *data, size_t bufferSize);
    ~VertexBuffer();

    VertexBuffer& GenerateBuffer(GLfloat *data, size_t bufferSize);
    VertexBuffer& Bind();
    VertexBuffer& SendData(GLenum bufferMode = GL_STATIC_DRAW);    
    VertexBuffer& Unbind();
public:
    GLuint ID;

private:
    GLfloat *m_data;
    size_t m_bufferSize;
};
#endif