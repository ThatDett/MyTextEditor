#include "Line.hpp"

Line::Line(unsigned int bufferSize) :
    buffer(bufferSize, '\0'), m_bufferSize(bufferSize),
    m_bufferCapacity(bufferSize)
{}

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