#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(GLuint *data, size_t bufferSize) :
    data(data), bufferSize(bufferSize)
{
    glGenBuffers(1, &ID);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::SendData(GLenum bufferMode /*= GL_STATIC_DRAW*/)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, data, bufferMode);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
