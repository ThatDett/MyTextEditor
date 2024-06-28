#include <iostream>
#include <unordered_map>
#include <string>

#include "glad/glad.h"

#include "CMakeVariables.h"

#include "stb_image.h"
#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H

#include "Application.hpp"
#include "Window.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"

#define FontCheck(x) if (x){std::cout << "ERROR::FREETYTPE: Failed to load Glyph. Line: " << __LINE__ << std::endl;exit(EXIT_FAILURE);}
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

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void KeyboardInputCallback(GLFWwindow *glfwwindow, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(window.ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.ptr, true);

    if (glfwGetKey(window.ptr, GLFW_KEY_F11) == GLFW_RELEASE)
    {
        const GLFWvidmode *mode = glfwGetVideoMode(window.monitor);

        glfwSetWindowMonitor(	
            window.ptr,
            window.fullscreen? NULL : window.monitor,
            0, 30,
            mode->width, mode->height, 
            mode->refreshRate
        );	
        window.fullscreen = !window.fullscreen;
    }

    if (glfwGetKey(window.ptr, GLFW_KEY_W) == GLFW_PRESS)
    {
        
    }

    if (glfwGetKey(window.ptr, GLFW_KEY_S) == GLFW_PRESS)
    {

    }
}

struct Character 
{
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    FT_Vector_ Advance;    // Offset to advance to next glyph
};

std::unordered_map<char, Character> Characters;


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
    for (char c : text)
    {
        RenderChar(s, c, x, y, scale, color);
        x += (Characters[c].Advance.x >> 6) * scale;
    }
}

void Application::Run()
{
    glClearColor(0.01f, 0.05f, 0.08f, 1.0f);

    FT_Library ft;
    FontCheck(FT_Init_FreeType(&ft));

    FT_Face face;
    FontCheck(FT_New_Face(ft, "../res/BaskervilleBT.ttf", 0, &face));

    FT_Set_Pixel_Sizes(face, 0, 32);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window.width), 0.0f, static_cast<float>(window.height));

    // VertexArray vao using these crashes for some reason;
    // VertexBuffer vbo;

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    Shader shader("../src/shaders/shader.glsl");
    shader.Use();
    shader.SetMat4("projection", projection);

    while (LOOP && !glfwWindowShouldClose(window.ptr))
    {
        ProcessInput();
    
        glClear(GL_COLOR_BUFFER_BIT);

        RenderText(shader, "Hello, World!", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Application::ProcessInput()
{
    
}

void Application::Draw(GLuint numberOfElements) const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, numberOfElements, GL_UNSIGNED_INT, 0);
}