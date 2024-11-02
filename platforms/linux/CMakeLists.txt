cmake_minimum_required(VERSION 3.26.3)

# Set project name
project(OpenGLProject)

# Set Cpp version
set (CMAKE_CXX_STANDARD 17)
set (PROJECT_DEPENDENCIES "${CMAKE_SOURCE_DIR}/../../dependencies")

# Add sources
add_executable(app 
    ../../src/Application.cpp
    ../../src/opengl/IndexBuffer.cpp
    ../../src/opengl/VertexArray.cpp
    ../../src/opengl/VertexBuffer.cpp
)

# Define macros
add_compile_definitions(LINUX_PLATFORM)

# Ask Cmake to find OpenGL on the system
find_package(OpenGL REQUIRED)

# Include dirs & libs
include_directories(${PROJECT_DEPENDENCIES}/linux/GLEW/include)
link_directories(${PROJECT_DEPENDENCIES}/linux/GLEW/lib)

include_directories(${PROJECT_DEPENDENCIES}/linux/GLFW/include)
link_directories(${PROJECT_DEPENDENCIES}/linux/GLFW/lib)

# Link all dependencies:
# 1) glfw
# 2) opengl
# 2) glew
target_link_libraries(app 
    GLEW
    ${OPENGL_LIBRARY} # Filled by Cmake
    glfw
)