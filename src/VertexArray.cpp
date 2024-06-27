#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray() 
{
    glDeleteVertexArrays(1, &ID);  
}

void VertexArray::Bind() const
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}