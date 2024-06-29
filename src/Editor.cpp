#include "Editor.hpp"

Editor::Editor(uint32_t NumberOfLines) :
    lines(NumberOfLines), m_size(NumberOfLines),
    m_capacity(NumberOfLines)
{}

Line& Editor::CurrentLine()
{
    return lines[textCursor.vIndex];
}

unsigned int Editor::NumberOfLines()
{
    return m_size;
}