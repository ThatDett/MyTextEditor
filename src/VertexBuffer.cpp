#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(GLfloat* data, size_t bufferSize) :
    m_data(data), m_bufferSize(bufferSize)
{
    glGenBuffers(1, &ID);
}

VertexBuffer::VertexBuffer() :
    m_data(nullptr), m_bufferSize(0)
{}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}

VertexBuffer& VertexBuffer::GenerateBuffer(GLfloat *data, size_t bufferSize)
{
    m_data = data;
    m_bufferSize = bufferSize; 
    glGenBuffers(1, &ID);
    return *this;
}

VertexBuffer& VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    return *this;
}

VertexBuffer& VertexBuffer::SendData(GLenum bufferMode /*= GL_STATIC_DRAW*/)
{
    glBufferData(GL_ARRAY_BUFFER, m_bufferSize, m_data, bufferMode);
    return *this;
}

VertexBuffer& VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    return *this;
}