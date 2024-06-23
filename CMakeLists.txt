cmake_minimum_required(VERSION 3.3)

project(MyTextEditor)

set(FILE_SOURCES 
    main.cpp 
    src/Application.cpp
    src/Shader.cpp
    #external/glad/glad/glad.c i dont need to compile everytime, just have the .o, but should include for others
    
)

add_executable(${PROJECT_NAME} ${FILE_SOURCES})

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glad
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/KHR
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
)   

target_link_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/src
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/glad
)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} opengl32)