#include <iostream>

#include "Editor.hpp"

Editor::Editor(const Font &font, uint32_t numberOfLines) :
    font(font),
    lines(new Line[numberOfLines * 2]), 
    m_size(numberOfLines),
    m_capacity(numberOfLines * 2)
{}

Editor::~Editor()
{
    delete[] lines;
}

void Editor::InsertChar(int codepoint)
{
    if (CurrentLine().Size() < CurrentLine().Capacity() - 1)
    {
        if (textCursor.hIndex == CurrentLine().Size())
        {
            CurrentLine().buffer[textCursor.hIndex] = codepoint;
            ++CurrentLine().m_bufferSize;
            ++textCursor.hIndex;
            CurrentLine().cursorIndex = textCursor.hIndex;
        }
        else
        {
            memmove(   
                &CurrentLine().CharAtIndex(1), 
                &CurrentLine().CharAtIndex(), 
                CurrentLine().Size() - textCursor.hIndex
            );

            CurrentLine().buffer[textCursor.hIndex] = codepoint;
            ++CurrentLine().m_bufferSize;
            ++textCursor.hIndex;
            CurrentLine().cursorIndex = textCursor.hIndex;
        }
    }
}

void Editor::EraseText()
{
    if (textCursor.hIndex > 0)
    {
        if (CurrentLine().Size() > 0)
        {
            if (textCursor.hIndex == CurrentLine().Size())
            {
                CurrentLine().buffer[textCursor.hIndex - 1] = 0;
            }
            else
            {
                memmove(
                    &CurrentLine().CharAtIndex(-1), 
                    &CurrentLine().CharAtIndex(), 
                    CurrentLine().Size() - textCursor.hIndex
                );
                CurrentLine().buffer[CurrentLine().Size() - 1] = 0;
            }
            --CurrentLine().m_bufferSize;
            --textCursor.hIndex;
            --CurrentLine().cursorIndex = textCursor.hIndex;
        }   
    }
    else
    {
        if (textCursor.vIndex > 0)
        {
            --textCursor.vIndex;
            textCursor.hIndex = CurrentLine().Size();
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
            if (textCursor.hIndex < CurrentLine().Size())
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
    if (Capacity() - NumberOfLines() < 1)
        Grow();

    int i = 0;
    for (Line *ptr = &CurrentLine() + (NumberOfLines() - textCursor.vIndex) - 1; 
        i < (NumberOfLines() - textCursor.vIndex) - 1; --ptr, ++i)
    {
        memset(ptr[1].buffer, 0, ptr[1].Size());

        if (ptr->Size() > 0)
        {
            memcpy(ptr[1].buffer, ptr->buffer, ptr->Size());
        }
        
        ptr[1].m_bufferSize = ptr->Size();
        ptr[1].cursorIndex = ptr->cursorIndex;
    }

    ++textCursor.vIndex;
    textCursor.hIndex = 0;
    ++m_size;

    memset(CurrentLine().buffer, 0, CurrentLine().Size()); 
    CurrentLine().cursorIndex = 0;
    CurrentLine().m_bufferSize = 0;
}

void Editor::Grow()
{
    Line *temp;

    m_capacity *= 2;
    if (!(temp = new Line[Capacity()]))
    {
        std::cout << "Editor::Grow couldn't reallocate" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < NumberOfLines(); ++i)
    {
        if (lines[i].Size() > 0)
        {
            memcpy(temp[i].buffer, lines[i].buffer, lines[i].Size());

            temp[i].m_bufferSize = lines[i].Size();
            temp[i].cursorIndex = lines[i].cursorIndex;
        }
    }

    delete[] lines;
    lines = temp;
}

void Editor::DeleteLine()
{

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