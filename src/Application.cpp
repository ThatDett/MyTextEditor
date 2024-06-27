#include <iostream>

#include "GLAD/glad.h"
#include <stb_image.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <Application.hpp>
#include <Shader.hpp>
#include <VertexArray.hpp>
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>

#define LOOP true

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

Application::Application() :
    windowSize{.width = 1366 / 2, .height = 768 / 2}
{
    std::cout << "Execute\n";

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MacOS necessity

    window = glfwCreateWindow(windowSize.width, windowSize.height, "Text Editor", NULL, NULL);
    if (!window)
    {
        std::cout << "fail on window creation\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize Glad\n";
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, windowSize.width, windowSize.height);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);  
}

Application::~Application()
{
    std::cout << "Terminated\n";
    glfwTerminate();
}
 

void Application::Run() const
{
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
  
        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
  
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
  
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
  
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
 
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f
    };

   unsigned int indices[] = {  
        0, 1, 3,   
        1, 2, 3    
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };

    const VertexArray vao;
    vao.Bind();

    const VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.Bind();
    vbo.SendData();

    const IndexBuffer ibo(indices, sizeof(indices));
    ibo.Bind();
    ibo.SendData();

    const Shader shader("../src/shaders/shader.glsl");
    shader.Use();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);   

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Texture
    stbi_set_flip_vertically_on_load(true);

    unsigned int texture[2];
    glGenTextures(2, texture);  

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("../res/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    data = stbi_load("../res/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    shader.SetUniform("texture1", 0); 
    shader.SetUniform("texture2", 1); 

    glEnable(GL_DEPTH_TEST);

    while (LOOP && !glfwWindowShouldClose(window))
    {
        ProcessInput(window);
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        view = glm::rotate(view, (float)glfwGetTime() * glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(50.0f), (float)windowSize.width / (float)windowSize.height, 0.1f, 100.0f);


        int modelLoc = glGetUniformLocation(shader.program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        int viewLoc = glGetUniformLocation(shader.program, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader.program, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // glDrawElements(GL_TRIANGLES, ibo.Length(), GL_UNSIGNED_INT, 0);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(cubePositions[i].x * sin(glfwGetTime()) * i, cubePositions[i].y * sin(glfwGetTime()) * i, cubePositions[i].z));
            float angle = 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    GLenum error;
    while((error = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "ERROR: " << error << '\n';
    }
}

void Application::ProcessInput(GLFWwindow *window) const
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Application::Draw(GLuint numberOfElements) const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, numberOfElements, GL_UNSIGNED_INT, 0);
}