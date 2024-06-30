#include <cstring>

#include "Line.hpp"

Line::Line(unsigned int bufferSize) :
    buffer(new char[bufferSize]), 
    m_bufferSize(0),
    m_bufferCapacity(bufferSize)
{
    memset(buffer, 0, bufferSize);
}

Line::~Line()
{
    delete[] buffer;
}

char& Line::CharAtIndex()
{
    return buffer[cursorIndex];
}

char& Line::CharAtIndex(int offset)
{
    return buffer[cursorIndex + offset];
}

unsigned int Line::Size()
{
    return m_bufferSize;
}

unsigned int Line::Capacity()
{
    return m_bufferCapacity;
}