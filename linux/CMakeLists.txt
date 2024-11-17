cmake_minimum_required(VERSION 3.26.3)

# Set project name
project(OpenGLProject)

# Set Cpp version
set (CMAKE_CXX_STANDARD 17)
set (PROJECT_DEPENDENCIES "${CMAKE_SOURCE_DIR}/../dependencies")
set (PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../engine")

# Add sources
add_executable(app 
    Application.cpp
# Core files
    ../engine/opengl/IndexBuffer.cpp
    ../engine/opengl/VertexArray.cpp
    ../engine/opengl/VertexBuffer.cpp
    ../engine/opengl/Layout.cpp
    ../engine/window/Window.cpp
    ../engine/opengl/external/GLFBridge.cpp
    ../engine/opengl/Shader.cpp
    ../engine/opengl/external/GLEWBridge.cpp
    ../engine/opengl/GLEngine.cpp
    ../engine/opengl/Renderer.cpp
    ../engine/opengl/Textures.cpp
#   ImGui files
    ../dependencies/imgui/imgui.cpp
    ../dependencies/imgui/imgui_draw.cpp
    ../dependencies/imgui/imgui_tables.cpp
    ../dependencies/imgui/imgui_widgets.cpp
    ../dependencies/imgui/backends/imgui_impl_opengl3.cpp
    ../dependencies/imgui/backends/imgui_impl_glfw.cpp
    ../engine/Application.cpp
    ../engine/common/Exception.cpp
    ../engine/MainThread.cpp
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

include_directories(${PROJECT_ROOT})
include_directories(${PROJECT_DEPENDENCIES})

# ImGui
include_directories(${PROJECT_DEPENDENCIES}/imgui)
include_directories(${PROJECT_DEPENDENCIES}/imgui/backends)

# Link all dependencies:
# 1) glfw
# 2) opengl
# 2) glew
target_link_libraries(app 
    GLEW
    ${OPENGL_LIBRARY} # Filled by Cmake
    glfw
)