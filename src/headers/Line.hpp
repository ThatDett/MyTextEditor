#ifndef LINE_H
#define LINE_H

class Line
{
    friend class Editor;
public:
    Line(unsigned int bufferSize = 256);
    ~Line();

    char CharAtIndex(int index);
    unsigned int Size();
    unsigned int Capacity();
public:
    char *buffer;
    unsigned int cursorIndex = 0;
private:
    unsigned int m_bufferSize;
    unsigned int m_bufferCapacity;
};
#endif
