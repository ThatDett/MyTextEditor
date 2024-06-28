#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "GLAD/glad.h"

class IndexBuffer
{
public:
    IndexBuffer(GLuint *data, size_t bufferSize);

    IndexBuffer& Bind();
    IndexBuffer& SendData(GLenum bufferMode = GL_STATIC_DRAW);
    IndexBuffer& Unbind();

    size_t Length() const;

public:
    GLuint *data;
    GLuint ID;
    size_t bufferSize;

private:
    size_t length;
};
#endif