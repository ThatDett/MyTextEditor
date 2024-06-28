#include <iostream>

#include <VertexArray.hpp>

VertexArray::VertexArray()
{
    // std::cout << "Generating vertex array" << std::endl; 
    glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray() 
{
    // std::cout << "Delete vertex array" << std::endl; 
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