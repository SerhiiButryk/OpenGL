cmake_minimum_required(VERSION 3.26.3)

# Set project name
project(OpenGLProject)

# Set Cpp version
set (CMAKE_CXX_STANDARD 17)

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
# Ask Cmake to find CLEW on the system
find_package(GLEW REQUIRED)

# Link dependencies:
# 1) glfw
# 2) opengl
# 2) glew
target_link_libraries(app 
    ${GLEW_LIBRARIES} # Filled by Cmake
    ${OPENGL_LIBRARY} # Filled by Cmake
    glfw
)