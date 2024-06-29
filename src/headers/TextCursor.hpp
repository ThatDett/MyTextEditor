#ifndef TEXT_CURSOR_H
#define TEXT_CURSOR_H

#include "Rectangle.hpp"

class TextCursor
{
public:

    void Draw();
public:
    Rectangle box;

    unsigned int hIndex;
    unsigned int vIndex;
};
#endif