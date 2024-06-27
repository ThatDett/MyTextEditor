#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(GLuint *data, size_t bufferSize) :
    data(data), bufferSize(bufferSize), length(bufferSize / sizeof(decltype(*data)))
{
    glGenBuffers(1, &ID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::SendData(GLenum bufferMode /*= GL_STATIC_DRAW*/) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, data, bufferMode);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t IndexBuffer::Length() const
{
    return length;
}