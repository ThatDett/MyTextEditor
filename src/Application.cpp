#include <iostream>
#include <unordered_map>
#include <string>

#include "glad/glad.h"

#include "CMakeVariables.h"

#include "stb_image.h"
#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"

#include "Application.hpp"
#include "Window.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "Rectangle.hpp"
#include "Renderer.hpp"
#include "Editor.hpp"

#define LOOP true

GLenum glCheckError_(std::string_view file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << errorCode << ": " << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

#define GLCheck(x) x; glCheckError_(__FILE__, __LINE__) 

Window window("Text Editor", 1366, 768);
Editor editor(100);

void FramebuffersizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void KeyboardInputCallback(GLFWwindow *glfwwindow, int key, int scancode, int action, int mods)
{   
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window.ptr, true);
            } break;
            case GLFW_KEY_F11:
            {
                const GLFWvidmode *mode = glfwGetVideoMode(window.monitor);

                glfwSetWindowMonitor(	
                    window.ptr,
                    window.fullscreen? NULL : window.monitor,
                    0, 30,
                    mode->width, mode->height - 30, 
                    mode->refreshRate
                );	
                window.fullscreen = !window.fullscreen;
            } break;
            case GLFW_KEY_ENTER:
            {
                editor.NewLine();
            } break;
            case GLFW_KEY_LEFT:
            {
                editor.TextCursorMove(Direction::LEFT);
            } break;
            case GLFW_KEY_RIGHT:
            {
                editor.TextCursorMove(Direction::RIGHT);
            } break;
            case GLFW_KEY_UP:
            {
                editor.TextCursorMove(Direction::UP);
            } break;
            case GLFW_KEY_DOWN:
            {
                editor.TextCursorMove(Direction::DOWN);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                editor.EraseText();
            } break;
        }
    }
    else if (action == GLFW_REPEAT)
    {
        switch (key)
        {   
            case GLFW_KEY_ENTER:
            {
                editor.NewLine();
            } break;
            case GLFW_KEY_LEFT:
            {
                editor.TextCursorMove(Direction::LEFT);
            } break;
            case GLFW_KEY_RIGHT:
            {
                editor.TextCursorMove(Direction::RIGHT);
            } break;
            case GLFW_KEY_UP:
            {
                editor.TextCursorMove(Direction::UP);
            } break;
            case GLFW_KEY_DOWN:
            {
                editor.TextCursorMove(Direction::DOWN);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                editor.EraseText();  
            } break;
        }
    }
    else {}
}

void CharInputCallback(GLFWwindow *window, unsigned int codepoint)
{
    if (editor.CurrentLine().buffersize < editor.CurrentLine().Size() - 1)
    {
        if (editor.textCursor.hIndex == editor.CurrentLine().buffersize)
        {
            editor.CurrentLine().buffer[editor.textCursor.hIndex] = codepoint;
            ++editor.CurrentLine().buffersize;
            ++editor.textCursor.hIndex;
            editor.CurrentLine().cursorIndex = editor.textCursor.hIndex;
        }
        else
        {
            memmove(   
                &editor.CurrentLine().CharAtIndex(1), 
                &editor.CurrentLine().CharAtIndex(), 
                editor.CurrentLine().buffersize - editor.textCursor.hIndex
            );
            editor.CurrentLine().buffer[editor.textCursor.hIndex] = codepoint;
            ++editor.CurrentLine().buffersize;
            ++editor.textCursor.hIndex;
            editor.CurrentLine().cursorIndex = editor.textCursor.hIndex;
        }
    }
}

Application::Application()
{
    std::cout << "Execute: " << (DEBUG_BUILD? "Debug " : "Release ") << "build\n";

    glViewport(0, 0, window.width, window.height);

    glfwSetFramebufferSizeCallback(window.ptr, FramebuffersizeCallback);
    glfwSetKeyCallback(window.ptr, KeyboardInputCallback);
    glfwSetCharCallback(window.ptr, CharInputCallback);

    glfwSetInputMode(window.ptr, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(true);
}

Application::~Application()
{
    std::cout << "Terminated\n";
    glfwTerminate();
}

void Application::Run()
{
    glClearColor(0.01f, 0.05f, 0.08f, 1.0f);

    Renderer renderer(Shader("../src/shaders/font.glsl"), Font("../res/BaskervilleBT.ttf", 0, 24));

    Rectangle cursor(glm::vec2(200.0f, 21.0f), 1, 22, glm::vec3(1.0f, 1.0f, 1.0f));

    while (LOOP && !glfwWindowShouldClose(window.ptr))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        for (uint32_t i = 0; i < 45; ++i)
        {
           renderer.DrawText(editor.lines[i].buffer, glm::vec2(20.0f, 730.0f - (i * renderer.font.Height() + 4)), glm::vec4(1.0f), 1.0f);
        }

        renderer.DrawText("current line buffersize: " + std::to_string(editor.CurrentLine().buffersize), glm::vec2(1000.0f, 730.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("current line cursorIndex: " + std::to_string(editor.CurrentLine().cursorIndex), glm::vec2(1000.0f, 710.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.textCursor.hIndex: " + std::to_string(editor.textCursor.hIndex), glm::vec2(1000.0f, 690.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.textCursor.vIndex: " + std::to_string(editor.textCursor.vIndex), glm::vec2(1000.0f, 670.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.size: " + std::to_string(editor.m_size), glm::vec2(1000.0f, 650.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.capacity: " + std::to_string(editor.Capacity()), glm::vec2(1000.0f, 630.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.NumberOfLines" + std::to_string(editor.NumberOfLines()), glm::vec2(1000.0f, 610.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("canInsertNewLine: " + std::to_string(editor.Capacity() - editor.NumberOfLines() > 0), glm::vec2(1000.0f, 590.0f), glm::vec4(1.0f), 1.0f);

        float xpos = 0;
        float ypos = 0;

        //<= ?
        for (unsigned int i = 0; i < editor.textCursor.hIndex; ++i)
        {
            xpos += renderer.font.characters[editor.CurrentLine().buffer[i]].Advance.x >> 6;
        }

        for (unsigned int i = 1; i < editor.textCursor.vIndex + 1; ++i)
        {
            ypos = i * renderer.font.Height() + 4;
        }

        cursor.pos = glm::vec2(20.0f + xpos, 22.0f + ypos);
        cursor.Draw();

        glfwSwapBuffers(window.ptr);
        glfwWaitEventsTimeout(0.5);
    }
}