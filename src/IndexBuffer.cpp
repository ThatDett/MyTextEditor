#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(GLuint *data, size_t bufferSize) :
    data(data), bufferSize(bufferSize), length(bufferSize / sizeof(decltype(*data)))
{
    glGenBuffers(1, &ID);
}

IndexBuffer& IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    return *this;
}

IndexBuffer& IndexBuffer::SendData(GLenum bufferMode /*= GL_STATIC_DRAW*/)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, data, bufferMode);
    return *this;
}

IndexBuffer& IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return *this;
}

size_t IndexBuffer::Length() const
{
    return length;
}