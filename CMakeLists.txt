cmake_minimum_required(VERSION 3.3)

project(MyTextEditor)

set(FILE_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${FILE_SOURCES})

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include/
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/
)   

target_link_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/src/
)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} opengl32)