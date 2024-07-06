#ifndef EDITOR_H
#define EDITOR_H

#include <cstdint>

#include "Renderer.hpp"
#include "Font.hpp"
#include "TextCursor.hpp"
#include "Line.hpp"
#include "Rectangle.hpp"

#include "GLFW/glfw3.h"

enum Direction
{
    LEFT  = -1,
    UP    = 0,
    RIGHT = 1,
    DOWN  = 2
};

struct Selector 
{
    //x = column, y = row
    glm::vec2 start;
    glm::vec2 end;
    Rectangle box;
};

class Editor
{
public:
    Editor(uint32_t numberOfLines = 256);
    ~Editor();

    void SetFont(Font &font);

    void InsertChar(GLFWwindow*, int codepoint);
    void EraseText();
    void TextCursorMove(GLFWwindow*, Direction);
    void NewLine();
    void Grow();
    void DeleteLine();

    Line& CurrentLine();
    unsigned int NumberOfLines();
    unsigned int Capacity();
public:
    Renderer *renderer;
    Font *font;
    TextCursor textCursor;
    Selector selector = {.start = {0, 0}, .end = {0, 0}};
    Line *lines;
private:
    size_t m_size;
    size_t m_capacity;
private:
};
#endif
