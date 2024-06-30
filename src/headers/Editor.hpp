#ifndef EDITOR_H
#define EDITOR_H

#include <cstdint>

#include "Font.hpp"
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
    Editor(const Font &font, uint32_t numberOfLines = 256);
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
    Font font;
    TextCursor textCursor;
    Line *lines;
private:

    uint64_t m_size;
    uint64_t m_capacity;
private:
};
#endif