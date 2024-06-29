#ifndef EDITOR_H
#define EDITOR_H

#include <cstdint>
#include <vector>

#include "TextCursor.hpp"
#include "Line.hpp"

class Editor
{
public:
    Editor(uint32_t numberOfLines);

    Line& CurrentLine();
    unsigned int NumberOfLines();
public:
    TextCursor textCursor;
    std::vector<Line> lines;
private:
    uint64_t m_size;
    uint64_t m_capacity;
private:
};
#endif