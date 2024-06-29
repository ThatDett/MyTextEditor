#include "Editor.hpp"

Editor::Editor(uint32_t numberOfLines) :
    lines(new Line[numberOfLines]), 
    m_size(numberOfLines),
    m_capacity(numberOfLines)
{}

Editor::~Editor()
{
    delete[] lines;
}

Line& Editor::CurrentLine()
{
    return lines[textCursor.vIndex];
}

unsigned int Editor::NumberOfLines()
{
    return m_size;
}