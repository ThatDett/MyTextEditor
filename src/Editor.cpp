#include <iostream>
#include <ostream>

#include "Editor.hpp"

Editor::Editor(uint32_t numberOfLines) :
    font(nullptr),
    lines(new Line[numberOfLines * 2]), 
    m_size(numberOfLines),
    m_capacity(numberOfLines * 2)
{}

Editor::~Editor()
{
    delete[] lines;
}

void Editor::SetFont(Font &font)
{
    this->font = &font;
    renderer->font = this->font;
}

void Editor::InsertChar(GLFWwindow  *window, int codepoint)
{
    bool control  = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
    bool capslock = glfwGetKey(window, GLFW_KEY_CAPS_LOCK)    == GLFW_PRESS;
    bool shift    = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)   == GLFW_PRESS;

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
    for (Line *ptr = &CurrentLine() + (NumberOfLines() - textCursor.vIndex); 
        i < (NumberOfLines() - textCursor.vIndex); --ptr, ++i)
    {
        //We don't need to do this in the first iteration
        if (ptr[1].Size() > 0)
            memset(ptr[1].buffer, 0, ptr[1].Size());

        //Next iteration cleans us
        if (ptr->Size() > 0)
            memcpy(ptr[1].buffer, ptr->buffer, ptr->Size());
        
        ptr[1].m_bufferSize = ptr->Size();
        ptr[1].cursorIndex = ptr->cursorIndex;

        //Last iteration
        if (ptr == &CurrentLine() + 1)
        {
            memset(ptr->buffer, 0, ptr->Size());

            if (textCursor.hIndex < CurrentLine().Size())
            {
                memcpy(
                    ptr->buffer, 
                    CurrentLine().buffer + textCursor.hIndex, 
                    CurrentLine().Size() - textCursor.hIndex
                );

                ptr->m_bufferSize = CurrentLine().Size() - textCursor.hIndex;
                ptr->cursorIndex = 0;

                memset(
                    CurrentLine().buffer + textCursor.hIndex,
                    0, CurrentLine().Size() - textCursor.hIndex
                );

                CurrentLine().m_bufferSize -= CurrentLine().Size() - textCursor.hIndex;
            }
            else
            {
                ptr->cursorIndex = 0;
                ptr->m_bufferSize = 0;
            }
            ++textCursor.vIndex;
            textCursor.hIndex = 0;
            ++m_size;
        }
    }
}

void Editor::Grow()
{
    Line *temp;

    m_capacity *= 2;
    if (!(temp = new Line[m_capacity]))
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
    //We should have the assurance that there's at least one line above the current
    for (
        Line *ptr = &CurrentLine(); 
        ptr != &CurrentLine() + (NumberOfLines() - textCursor.vIndex); 
        ++ptr
    )
    {
        //If it is the first iteration
        if (ptr->Size() > 0)
        {
            if (ptr == &CurrentLine())
            {
                //We also need to assure ptr[-1] has enough capacity
                memcpy(
                    ptr[-1].buffer + ptr[-1].Size(),
                    ptr->buffer,
                    ptr->Size()
                );

                memset(
                    ptr->buffer,
                    0, ptr->Size()
                );

                textCursor.hIndex = ptr[-1].m_bufferSize;
                ptr[-1].m_bufferSize += ptr->Size();
                ptr->m_bufferSize = 0;
            }
            else
            {
                memcpy(
                    ptr[-1].buffer,
                    ptr->buffer,
                    ptr->Size()
                );
                memset(
                    ptr->buffer,
                    0, ptr->Size()
                );

                ptr[-1].m_bufferSize = ptr->Size();
                ptr[-1].cursorIndex = ptr->cursorIndex;

                ptr->m_bufferSize = 0;
                ptr->cursorIndex = 0;
            }
        }
        else
        {
            if (ptr == &CurrentLine())
               textCursor.hIndex = ptr[-1].Size(); 
        }
    }

    // if (textCursor.vIndex + 1 == NumberOfLines())
    //     textCursor.hIndex = lines[textCursor.vIndex - 1].Size();

    --textCursor.vIndex;
    --m_size;
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
