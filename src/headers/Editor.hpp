#ifndef EDITOR_H
#define EDITOR_H

#include <cstdint>

#include "TextCursor.hpp"
#include "Line.hpp"

enum Direction
{
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Editor
{
public:
    Editor(uint32_t numberOfLines);
    ~Editor();

    void InsertChar(int codepoint);
    void EraseText();
    void TextCursorMove(Direction direction);
    void NewLine();
    void Grow();
    void DeleteLine();

    Line& CurrentLine();
    unsigned int NumberOfLines();
    unsigned int Capacity();
public:
    TextCursor textCursor;
    Line *lines;
    uint64_t m_size;
private:
    uint64_t m_capacity;
private:
};
#endif