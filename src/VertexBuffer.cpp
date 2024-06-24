#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(GLfloat* data, size_t bufferSize) :
    data(data), bufferSize(bufferSize)
{
    glGenBuffers(1, &ID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::SendData(GLenum bufferMode /*= GL_STATIC_DRAW*/)
{
    glBufferData(GL_ARRAY_BUFFER, bufferSize, data, bufferMode);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}