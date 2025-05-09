#include <iostream>
#include <unordered_map>
#include <string>

#include "common.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "TextCursor.hpp"

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
        std::cerr << errorCode << ": " << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

#define GLCheck(x) x; glCheckError_(__FILE__, __LINE__) 

Font fonts[1][24];

Window window("Text Editor");
Editor editor(32);

void FramebuffersizeCallback(GLFWwindow *glfwwindow, int width, int height)
{
    glViewport(0, 0, width, height);
    window.width = width; 
    window.height = height; 
} 

unsigned int fontIndex = 2;
int timer = 0;
float textYOffset = 0.f;

void KeyboardInputCallback(GLFWwindow *glfwwindow, int key, int scancode, int action, int mods)
{   
    timer = 120;
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window.ptr, true);
            } break;
            case GLFW_KEY_F8:
            {
                if (fontIndex > 0)
                    --fontIndex;
            } break;
            case GLFW_KEY_F9:
            {
                if (fontIndex < 23)
                    ++fontIndex;
            } break;
            case GLFW_KEY_F11:
            {
                glfwSetWindowMonitor(	
                    window.ptr,
                    window.fullscreen? NULL : window.monitor,
                    0, 30,
                    window.mode->width, window.mode->height - 30, 
                    window.mode->refreshRate
                );	
                window.fullscreen = !window.fullscreen;
            } break;
            case GLFW_KEY_TAB:
            {
                for (int i = 0; i < 4; ++i)
                    editor.InsertChar(glfwwindow, ' ');
            } break;
            case GLFW_KEY_ENTER:
            {
                editor.NewLine();
            } break;
            case GLFW_KEY_LEFT:
            {
                editor.TextCursorMove(glfwwindow, Direction::LEFT);
            } break;
            case GLFW_KEY_RIGHT:
            {
                editor.TextCursorMove(glfwwindow, Direction::RIGHT);
            } break;
            case GLFW_KEY_UP:
            {
                editor.TextCursorMove(glfwwindow, Direction::UP);
            } break;
            case GLFW_KEY_DOWN:
            {
                editor.TextCursorMove(glfwwindow, Direction::DOWN);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                if (editor.textCursor.hIndex > 0)
                    editor.EraseText();
                else if (editor.textCursor.vIndex > 0)
                    editor.DeleteLine();
            } break;
        }
    }
    else if (action == GLFW_REPEAT)
    {
        switch (key)
        {   
            case GLFW_KEY_F8:
            {
                if (fontIndex > 0)
                    --fontIndex;
            } break;
            case GLFW_KEY_F9:
            {
                if (fontIndex < 23)
                    ++fontIndex;
            } break;
            case GLFW_KEY_TAB:
            {
                for (int i = 0; i < 4; ++i)
                    editor.InsertChar(glfwwindow, ' ');
            } break;
            case GLFW_KEY_ENTER:
            {
                editor.NewLine();
            } break;
            case GLFW_KEY_LEFT:
            {
                editor.TextCursorMove(glfwwindow, Direction::LEFT);
            } break;
            case GLFW_KEY_RIGHT:
            {
                editor.TextCursorMove(glfwwindow, Direction::RIGHT);
            } break;
            case GLFW_KEY_UP:
            {
                editor.TextCursorMove(glfwwindow, Direction::UP);
            } break;
            case GLFW_KEY_DOWN:
            {
                editor.TextCursorMove(glfwwindow, Direction::DOWN);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                if (editor.textCursor.hIndex > 0)
                    editor.EraseText();
                else if (editor.textCursor.vIndex > 0)
                    editor.DeleteLine();
            } break;
        }
    }
    else {}
}

void CharInputCallback(GLFWwindow* glfwwindow, unsigned int codepoint)
{
    editor.InsertChar(glfwwindow, codepoint);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    textYOffset += yoffset * fontIndex * 5;
    textYOffset = glm::clamp(textYOffset, 0.f, 99999999.f);
}

Application::Application()
{
    std::cout << "Execute: " << (DEBUG_BUILD? "Debug " : "Release ") << "build\n";

    glViewport(0, 0, window.width, window.height);

    glfwSetFramebufferSizeCallback(window.ptr, &FramebuffersizeCallback);
    glfwSetKeyCallback(window.ptr, &KeyboardInputCallback);
    glfwSetCharCallback(window.ptr, &CharInputCallback);
    glfwSetScrollCallback(window.ptr, &ScrollCallback);

    glfwSetInputMode(window.ptr, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(true);

    for (unsigned int i = 0; i < 24; ++i)
    {
        fonts[0][i].filepath = "../res/fonts/Consolas.ttf";
        fonts[0][i].LoadFont(0, 16 + (i * 4));
    }
}

Application::~Application()
{
    std::cout << "Terminated\n";
    glfwTerminate();
}

void Application::Run()
{
    Line commandLine;

    memcpy(commandLine.buffer, "Command test", strlen("Command test"));

    glClearColor(0.01f, 0.05f, 0.08f, 1.0f);

    Renderer renderer(Shader("../res/shaders/font.glsl"), fonts[0][0]);
    editor.renderer = &renderer;

    Rectangle cursor(glm::vec2(200.0f, 21.0f), 1, 22, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    Rectangle bottomBar(glm::vec2(0, window.height - 36), window.width, 36, glm::vec4(0.0f, 0.02f, 0.04f, 1.0f));

    while (LOOP && !glfwWindowShouldClose(window.ptr))
    {
        editor.SetFont(fonts[0][fontIndex]);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.DrawText("current line buffersize: " + std::to_string(editor.CurrentLine().Size()), glm::vec2(1000.0f, 730.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("current line cursorIndex: " + std::to_string(editor.CurrentLine().cursorIndex), glm::vec2(1000.0f, 710.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.textCursor.hIndex: " + std::to_string(editor.textCursor.hIndex), glm::vec2(1000.0f, 690.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.textCursor.vIndex: " + std::to_string(editor.textCursor.vIndex), glm::vec2(1000.0f, 670.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.size: " + std::to_string(editor.NumberOfLines()), glm::vec2(1000.0f, 650.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("editor.capacity: " + std::to_string(editor.Capacity()), glm::vec2(1000.0f, 630.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("canInsertNewLine: " + std::to_string(editor.Capacity() - editor.NumberOfLines() > 0), glm::vec2(1000.0f, 610.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("fullscreen: " + std::to_string(window.fullscreen), glm::vec2(1000.0f, 590.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("box.x: " + std::to_string(editor.selector.box.pos.x), glm::vec2(1000.0f, 570.0f), glm::vec4(1.0f), 1.0f);

        float xpos = 0;
        float ypos = 20.0f;

        //Drawing the lines
        for (uint32_t i = 0; i < 45; ++i)
        {
           renderer.DrawText(editor.lines[i].buffer, glm::vec2(20.0f, window.height - 20.0f - ((i + 1) * editor.font->Height()) + textYOffset), glm::vec4(1.0f), 1.0f);
        }

        //<= ?
        for (unsigned int i = 0; i < editor.textCursor.hIndex; ++i)
        {
            xpos += editor.font->characters[editor.CurrentLine().CharAtIndex(i)].Advance.x >> 6;
        }

        cursor.width = 1 + (float)fontIndex/12.0f;
        cursor.height = editor.font->Height();

        ypos += editor.textCursor.vIndex * editor.font->Height() - 17.0f + fontIndex / 2;  
        cursor.pos = glm::vec2(20.0f + xpos, 22.0f + ypos - textYOffset);

        if (timer > 0 || (int)glfwGetTime() % 2 == 0)
            cursor.Draw();

        editor.selector.box.pos.x = 20.0f;
        editor.selector.box.pos.y = 20.0f;
        editor.selector.box.width = 200;
        editor.selector.box.height = editor.font->Height();
        editor.selector.box.ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.3f));

        for (unsigned int i = 0; i < editor.selector.start.x; ++i)
        {
            editor.selector.box.pos.x += editor.font->characters[editor.CurrentLine().CharAtIndex(i)].Advance.x >> 6;
        }

        if (editor.selector.box.pos.x != editor.selector.box.pos.y)
            editor.selector.box.Draw();

        bottomBar.Draw();

        renderer.DrawText(commandLine.buffer, glm::vec2(bottomBar.pos.x + 10, bottomBar.height / 2 - editor.font->Height() / 3));

        if (timer > 0)
            --timer;
        

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }
}
