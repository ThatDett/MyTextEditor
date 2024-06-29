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

constexpr GLuint BUFFER_MAX = 48;

struct TextCursor
{
    unsigned int hIndex = 0;
    unsigned int vIndex = 0;
};

struct Line 
{
    GLuint cursorIndex = 0;
    GLuint buffersize = 0;
    char buffer[BUFFER_MAX];
};

struct Editor
{
    size_t size;
    Line lines[8];
};

TextCursor textCursor;
Editor editor{.size = sizeof(editor.lines) / sizeof(Line)};

void FramebuffersizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void KeyboardInputCallback(GLFWwindow *glfwwindow, int key, int scancode, int action, int mods)
{   
    enum Direction
    {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    auto OnArrowMove = [](int direction)
    {
        switch (direction)
        {
            case Direction::LEFT:
            {
                if (textCursor.hIndex > 0)
                {
                    --textCursor.hIndex;
                    editor.lines[textCursor.vIndex].cursorIndex = textCursor.hIndex;
                }
            } break;
            case Direction::RIGHT:
            {
                if (textCursor.hIndex < editor.lines[textCursor.vIndex].buffersize)
                {
                    ++textCursor.hIndex;
                    editor.lines[textCursor.vIndex].cursorIndex = textCursor.hIndex;
                }
            } break;
            case Direction::UP:
            {
                if (textCursor.vIndex > 0)
                {
                   --textCursor.vIndex;
                   textCursor.hIndex = editor.lines[textCursor.vIndex].cursorIndex;
                }
            } break;
            case Direction::DOWN:
            {
                if (textCursor.vIndex < editor.size - 1)
                {
                    ++textCursor.vIndex;
                    textCursor.hIndex = editor.lines[textCursor.vIndex].cursorIndex;
                }
            } break;
        }
    };

    auto OnBackspace = []()
    {
        if (textCursor.hIndex > 0)
        {
            if (editor.lines[textCursor.vIndex].buffersize > 0)
            {
                if (textCursor.hIndex == editor.lines[textCursor.vIndex].buffersize)
                {
                    editor.lines[textCursor.vIndex].buffer[textCursor.hIndex - 1] = 0;
                }
                else
                {
                    memmove(editor.lines[textCursor.vIndex].buffer + textCursor.hIndex - 1, editor.lines[textCursor.vIndex].buffer + textCursor.hIndex, editor.lines[textCursor.vIndex].buffersize - textCursor.hIndex);
                    editor.lines[textCursor.vIndex].buffer[editor.lines[textCursor.vIndex].buffersize - 1] = 0;
                }
                --editor.lines[textCursor.vIndex].buffersize;
                --textCursor.hIndex;
                --editor.lines[textCursor.vIndex].cursorIndex = textCursor.hIndex;
            }   
        }
        else
        {
            if (textCursor.vIndex > 0)
            {
                --textCursor.vIndex;
                textCursor.hIndex = editor.lines[textCursor.vIndex].buffersize;
                editor.lines[textCursor.vIndex].cursorIndex = textCursor.hIndex;
            }
        }
    };

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
            } break;
            case GLFW_KEY_LEFT:
            {
                OnArrowMove(Direction::LEFT);
            } break;
            case GLFW_KEY_RIGHT:
            {
                OnArrowMove(Direction::RIGHT);
            } break;
            case GLFW_KEY_UP:
            {
                OnArrowMove(Direction::UP);
            } break;
            case GLFW_KEY_DOWN:
            {
                OnArrowMove(Direction::DOWN);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                OnBackspace();
            } break;
            default:
            {   
                // OnCharInput();
            }
        }
    }
    else if (action == GLFW_REPEAT)
    {
        switch (key)
        {   
            case GLFW_KEY_LEFT:
            {
                OnArrowMove(Direction::LEFT);
            } break;
            case GLFW_KEY_RIGHT:
            {
                OnArrowMove(Direction::RIGHT);
            } break;
            case GLFW_KEY_UP:
            {
                OnArrowMove(Direction::UP);
            } break;
            case GLFW_KEY_DOWN:
            {
                OnArrowMove(Direction::DOWN);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                OnBackspace();  
            } break;
            default:
            {
                // OnCharInput();
            }
        }
    }
    else {}
}

void CharInputCallback(GLFWwindow *window, unsigned int codepoint)
{
    if (editor.lines[textCursor.vIndex].buffersize < BUFFER_MAX - 1)
    {
        if (textCursor.hIndex == editor.lines[textCursor.vIndex].buffersize)
        {
            editor.lines[textCursor.vIndex].buffer[textCursor.hIndex] = codepoint;
            ++editor.lines[textCursor.vIndex].buffersize;
            ++textCursor.hIndex;
            editor.lines[textCursor.vIndex].cursorIndex = textCursor.hIndex;
        }
        else
        {
            memmove(&editor.lines[textCursor.vIndex].buffer[textCursor.hIndex + 1], &editor.lines[textCursor.vIndex].buffer[textCursor.hIndex], editor.lines[textCursor.vIndex].buffersize - textCursor.hIndex);
            editor.lines[textCursor.vIndex].buffer[textCursor.hIndex] = codepoint;
            ++editor.lines[textCursor.vIndex].buffersize;
            ++textCursor.hIndex;
            editor.lines[textCursor.vIndex].cursorIndex = textCursor.hIndex;
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

        for (uint32_t i = 0; i < editor.size; ++i)
            renderer.DrawText(editor.lines[i].buffer, glm::vec2(20.0f, 730.0f - (i * 22.0f)), glm::vec4(1.0f), 1.0f);

        renderer.DrawText("current line buffersize: " + std::to_string(editor.lines[textCursor.vIndex].buffersize), glm::vec2(1000.0f, 730.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("current line cursorIndex: " + std::to_string(editor.lines[textCursor.vIndex].cursorIndex), glm::vec2(1000.0f, 710.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("textCursor.hIndex: " + std::to_string(textCursor.hIndex), glm::vec2(1000.0f, 690.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("textCursor.vIndex: " + std::to_string(textCursor.vIndex), glm::vec2(1000.0f, 670.0f), glm::vec4(1.0f), 1.0f);

        float xpos = 0;
        float ypos = 0;

        //<= ?
        for (unsigned int i = 0; i < textCursor.hIndex; ++i)
        {
            xpos += renderer.font.characters[editor.lines[textCursor.vIndex].buffer[i]].Advance.x >> 6;
        }

        for (unsigned int i = 1; i < textCursor.vIndex + 1; ++i)
        {
            ypos = i * 22.0f;
        }

        cursor.pos = glm::vec2(20.0f + xpos, 22.0f + ypos);
        cursor.Draw();

        glfwSwapBuffers(window.ptr);
        glfwWaitEventsTimeout(0.5);
    }
}