#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "GLAD/glad.h"

class IndexBuffer
{
public:
    IndexBuffer(GLuint *data, size_t bufferSize);

    void Bind();
    void SendData(GLenum bufferMode = GL_STATIC_DRAW);
    void Unbind();

public:
    GLuint *data;
    size_t bufferSize;
    GLuint ID;
};
#endif