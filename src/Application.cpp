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

GLuint cursorIndex = 0;
GLuint buffersize = 0;
constexpr GLuint BUFFER_MAX = 16;
char buffer[BUFFER_MAX + 1];

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void KeyboardInputCallback(GLFWwindow *glfwwindow, int key, int scancode, int action, int mods)
{   
    auto OnArrowMove = [](int direction)
    {
        if (direction == 1 && cursorIndex < buffersize)
            ++cursorIndex;
        else if (direction == -1 && cursorIndex > 0)
            --cursorIndex;
    };

    auto OnBackspace = []()
    {
        if (cursorIndex > 0 && buffersize > 0)
        {
            buffer[cursorIndex - 1] = 0;
            --buffersize;
            --cursorIndex;
        }   
    };

    auto OnCharInput = [key, mods]()
    {
        int capsState = glfwGetKey(window.ptr, GLFW_KEY_CAPS_LOCK);
        if (key > 128) return;
        if (buffersize < BUFFER_MAX)
        {
            buffer[cursorIndex] = mods? key : std::tolower(key);
            ++buffersize;
            ++cursorIndex;
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
                // for (unsigned int i = 0; i < BUFFER_MAX; ++i)
                // {
                //     std::cout << buffer[i];
                // }
                // std::cout << std::endl;
            } break;
            case GLFW_KEY_LEFT:
            {
                OnArrowMove(-1);
            } break;
            case GLFW_KEY_RIGHT:
            {
                OnArrowMove(1);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                OnBackspace();
            } break;
            default:
            {   
                OnCharInput();
            }
        }
    }
    else if (action == GLFW_REPEAT)
    {
        switch (key)
        {   
            case GLFW_KEY_LEFT:
            {
                OnArrowMove(-1);
            } break;
            case GLFW_KEY_RIGHT:
            {
                OnArrowMove(1);
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                OnBackspace();  
            } break;
            default:
            {
                OnCharInput();
            }
        }
    }
    else {}
}

void CharInputCallback(GLFWwindow *window, unsigned int codepoint)
{
    if (buffersize < BUFFER_MAX)
    {
        buffer[cursorIndex] = codepoint;
        ++buffersize;
        cursorIndex = buffersize;
    }
}

Application::Application()
{
    std::cout << "Execute: " << (DEBUG_BUILD? "Debug " : "Release ") << "build\n";

    glViewport(0, 0, window.width, window.height);

    glfwSetFramebufferSizeCallback(window.ptr, FramebufferSizeCallback);
    glfwSetKeyCallback(window.ptr, KeyboardInputCallback);
    // glfwSetCharCallback(window.ptr, CharInputCallback);

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

    Rectangle cursor(glm::vec2(200.0f, 20.0f), 1, 20, glm::vec3(1.0f, 1.0f, 1.0f));

    while (LOOP && !glfwWindowShouldClose(window.ptr))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.DrawText(buffer, glm::vec2(20.0f, 730.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("bufferSize: " + std::to_string(buffersize), glm::vec2(1000.0f, 730.0f), glm::vec4(1.0f), 1.0f);
        renderer.DrawText("cursorIndex: " + std::to_string(cursorIndex), glm::vec2(1000.0f, 710.0f), glm::vec4(1.0f), 1.0f);

        float testpos = 0;

        //<= ?
        for (unsigned int i = 0; i < cursorIndex; ++i)
        {
            testpos += renderer.font.characters[buffer[i]].Advance.x >> 6;
        }

        cursor.pos = glm::vec2(20.0f + testpos, 20.0f);
        cursor.Draw();

        glfwSwapBuffers(window.ptr);
        glfwWaitEventsTimeout(0.5);
    }
}