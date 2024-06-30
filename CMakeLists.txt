cmake_minimum_required(VERSION 3.3)

project(MyTextEditor)

set(FILE_SOURCES 
    main.cpp 
    src/Application.cpp
    src/Shader.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/Window.cpp
    src/Rectangle.cpp
    src/Font.cpp
    src/Renderer.cpp
    src/TextCursor.cpp
    src/Line.cpp
    src/Editor.cpp
    external/stb_image/stb_implementation.cpp
    #external/glad/glad/glad.c i dont need to compile everytime, just have the .o, but should include for others
    
)

set(CMAKE_CXX_STANDARD 20)
set(DEBUG_BUILD 1)

# Define optimization flags based on build type
if(${DEBUG_BUILD} EQUAL 1)
    add_compile_options(-O0)
    add_compile_options(-g)
else(${DEBUG_BUILD} EQUAL 0)
    add_compile_options(-O2)
endif()

configure_file (src/headers/CMakeVariables.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/CMakeVariables.h @ONLY)
add_executable(${PROJECT_NAME} ${FILE_SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

add_subdirectory(external/glfw)
add_subdirectory(external/FreeType)

target_include_directories(${PROJECT_NAME} 
    PRIVATE external/glad
    PRIVATE external/glfw/include
    PRIVATE external/FreeType/include
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
target_link_libraries(${PROJECT_NAME} freetype)
target_link_libraries(${PROJECT_NAME} opengl32)