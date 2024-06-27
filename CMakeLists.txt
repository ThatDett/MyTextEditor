cmake_minimum_required(VERSION 3.3)

project(MyTextEditor)

set(FILE_SOURCES 
    main.cpp 
    src/Application.cpp
    src/Shader.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/Camera.cpp
    external/stb_image/stb_implementation.cpp
    #external/glad/glad/glad.c i dont need to compile everytime, just have the .o, but should include for others
    
)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} ${FILE_SOURCES})

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PRIVATE external/glad
    PRIVATE external/glfw/include
    PRIVATE external/glm
    PRIVATE external/KHR
    PRIVATE external/stb_image
    PRIVATE src/headers
)   

target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
    PRIVATE external/glad/glad
)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} opengl32)