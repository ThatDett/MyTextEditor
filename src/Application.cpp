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

GLuint textCursor = 0;
GLuint buffersize = 0;
constexpr GLuint BUFFER_MAX = 16;
char buffer[BUFFER_MAX];

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
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
            case GLFW_KEY_LEFT:
            {
                if (textCursor > 0)
                    --textCursor;
            } break;
            case GLFW_KEY_RIGHT:
            {
                if (textCursor < buffersize)
                    ++textCursor;
            } break;
            case GLFW_KEY_BACKSPACE:
            {
                if (textCursor > 0 && buffersize > 0)
                {
                    buffer[textCursor] = '\0';
                    --buffersize;
                    --textCursor;
                }   
            } break;
            default:
            {
                if (buffersize < BUFFER_MAX)
                {
                    buffer[textCursor] = key;
                    ++buffersize;
                    ++textCursor;
                }
            }
        }
    }
    // std::cout << key << std::endl;
}

Application::Application()
{
    std::cout << "Execute: " << (DEBUG_BUILD? "Debug " : "Release ") << "build\n";

    glViewport(0, 0, window.width, window.height);

    glfwSetFramebufferSizeCallback(window.ptr, FramebufferSizeCallback);
    glfwSetKeyCallback(window.ptr, KeyboardInputCallback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(true);
}

Application::~Application()
{
    std::cout << "Terminated\n";
    glfwTerminate();
}

#if 0
void RenderChar(Shader &s, unsigned char c, float x, float y, float scale, const glm::vec3 &color)
{
    s.Use();
    glUniform3f(glGetUniformLocation(s.program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    
    Character &ch = Characters[c];

    float xpos = x + ch.Bearing.x * scale;
    float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

    float w = ch.Size.x * scale;
    float h = ch.Size.y * scale;

    float vertices[6][4] = {
        { xpos,     ypos + h,   0.0f, 0.0f },            
        { xpos,     ypos,       0.0f, 1.0f },
        { xpos + w, ypos,       1.0f, 1.0f },
        { xpos,     ypos + h,   0.0f, 0.0f },
        { xpos + w, ypos,       1.0f, 1.0f },
        { xpos + w, ypos + h,   1.0f, 0.0f }           
    };

    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += (ch.Advance.x >> 6) * scale; 
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderText(Shader &s, std::string_view text, float x, float y, float scale, const glm::vec3 &color)
{
    std::string_view::const_iterator c = text.begin();
    for (GLuint i = 0; c != text.end(); ++c, ++i)
    {
        RenderChar(s, *c, x, y, scale, /*(i == textCursor)? glm::vec3(1.0f, 0.0f, 0.0f) : */color);
        x += (Characters[*c].Advance.x >> 6) * scale;
    }
}
#endif

void Application::Run()
{
    glClearColor(0.01f, 0.05f, 0.08f, 1.0f);

    Renderer renderer;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window.width), 0.0f, static_cast<float>(window.height));

    // VertexArray vao using these crashes for some reason;
    // VertexBuffer vbo;

    // Shader shader("../src/shaders/shader.glsl");
    // shader.Use();
    // shader.SetMat4("projection", projection);

    Rectangle rect(glm::vec2(500.0f, 500.0f), 120, 200, glm::vec3(1.0f, 1.0f, 1.0f));

    while (LOOP && !glfwWindowShouldClose(window.ptr))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // shader.Use();
        // RenderText(shader, buffer, 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        // RenderText(shader, "textcursor: " + std::to_string(textCursor), 25.0f, 700.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        renderer.DrawText("Test", glm::vec2(25.0f, 700.0f));

        rect.Draw();

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Application::Draw(GLuint numberOfElements) const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, numberOfElements, GL_UNSIGNED_INT, 0);
}