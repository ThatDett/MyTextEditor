#include <iostream>

#include "Editor.hpp"

Editor::Editor(uint32_t numberOfLines) :
    lines(new Line[numberOfLines * 2]), 
    m_size(numberOfLines),
    m_capacity(numberOfLines * 2)
{}

Editor::~Editor()
{
    delete[] lines;
}

void Editor::EraseText()
{
    if (textCursor.hIndex > 0)
    {
        if (CurrentLine().buffersize > 0)
        {
            if (textCursor.hIndex == CurrentLine().buffersize)
            {
                CurrentLine().buffer[textCursor.hIndex - 1] = 0;
            }
            else
            {
                memmove(
                    &CurrentLine().CharAtIndex(-1), 
                    &CurrentLine().CharAtIndex(), 
                    CurrentLine().buffersize - textCursor.hIndex
                );
                CurrentLine().buffer[CurrentLine().buffersize - 1] = 0;
            }
            --CurrentLine().buffersize;
            --textCursor.hIndex;
            --CurrentLine().cursorIndex = textCursor.hIndex;
        }   
    }
    else
    {
        if (textCursor.vIndex > 0)
        {
            --textCursor.vIndex;
            textCursor.hIndex = CurrentLine().buffersize;
            CurrentLine().cursorIndex = textCursor.hIndex;
        }
    }
}

void Editor::TextCursorMove(Direction direction)
{
    switch (direction)
    {
        case Direction::LEFT:
        {
            if (textCursor.hIndex > 0)
            {
                --textCursor.hIndex;
                CurrentLine().cursorIndex = textCursor.hIndex;
            }
        } break;
        case Direction::RIGHT:
        {
            if (textCursor.hIndex < CurrentLine().buffersize)
            {
                ++textCursor.hIndex;
                CurrentLine().cursorIndex = textCursor.hIndex;
            }
        } break;
        case Direction::UP:
        {
            if (textCursor.vIndex > 0)
            {
               --textCursor.vIndex;
               textCursor.hIndex = CurrentLine().cursorIndex;
            }
        } break;
        case Direction::DOWN:
        {
            if (textCursor.vIndex < NumberOfLines() - 1)
            {
                ++textCursor.vIndex;
                textCursor.hIndex = CurrentLine().cursorIndex;
            }
        } break;
    }
}

void Editor::NewLine()
{
    if (m_capacity - NumberOfLines() > 0)
    {
        int i = 0;
        for (Line *ptr = &CurrentLine() + (NumberOfLines() - textCursor.vIndex) - 1; i < (NumberOfLines() - textCursor.vIndex) - 1; --ptr, ++i)
        {
            if (ptr->buffersize > 0)
                memcpy(ptr[1].buffer, ptr->buffer, ptr->buffersize);
            else
                memset(ptr[1].buffer, 0, ptr[1].buffersize);
            ptr[1].buffersize = ptr->buffersize;
            ptr[1].cursorIndex = ptr->cursorIndex;
        }


        ++textCursor.vIndex;
        textCursor.hIndex = 0;
        ++m_size;

        memset(CurrentLine().buffer, 0, CurrentLine().buffersize); 
        CurrentLine().cursorIndex = 0;
        CurrentLine().buffersize = 0;
    }
    else
    {
        Grow();
    }
}

void Editor::Grow()
{
    delete[] lines;
    lines = nullptr;

    m_capacity *= 2;
    if (!(lines = new Line[m_capacity]))
        std::cout << "Editor::Grow couldn't reallocate" << std::endl;

    NewLine();
}

Line& Editor::CurrentLine()
{
    return lines[textCursor.vIndex];
}

unsigned int Editor::NumberOfLines()
{
    return m_size;
}

unsigned int Editor::Capacity()
{
    return m_capacity;
}