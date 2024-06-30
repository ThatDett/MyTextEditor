#ifndef LINE_H
#define LINE_H

#include <vector>

class Line
{
public:
    Line(unsigned int bufferSize = 256);
    ~Line();

    char& CharAtIndex();
    char& CharAtIndex(int offset);
    unsigned int Size();
    unsigned int Capacity();
public:
    char *buffer;
    unsigned int buffersize = 0;
    unsigned int cursorIndex = 0;
private:
    unsigned int m_bufferSize;
    unsigned int m_bufferCapacity;
};
#endif