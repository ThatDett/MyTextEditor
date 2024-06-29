#ifndef LINE_H
#define LINE_H

#include <vector>

class Line
{
public:
    Line(unsigned int bufferCapacity = 256);

    char& CharAtIndex();
    char& CharAtIndex(int offset);
    unsigned int Size();
    unsigned int Capacity();
public:
    std::vector<char> buffer;
    unsigned int cursorIndex = 0;
    unsigned int buffersize = 0;
private:
    unsigned int m_bufferSize;
    unsigned int m_bufferCapacity;
};
#endif