cmake_minimum_required(VERSION 3.26.3)

# Set project name
project(OpenGLProjectTest)

set (PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../")

# Set Cpp version
set (CMAKE_CXX_STANDARD 17)
set (PROJECT_ROOT "${CMAKE_SOURCE_DIR}/..")

# Build engine lib
file(MAKE_DIRECTORY ../build_engine)
add_subdirectory(${PROJECT_ROOT}/linux ../build_engine)

# Add sources
add_executable(app
    Application.cpp
    ui_tests/TestMenuUI.cpp
    ui_tests/base/TestUI.cpp
    ui_tests/BackgroundColorTest.cpp
    ui_tests/TextureTest.cpp
)

include_directories(${PROJECT_ROOT}/dependencies)
include_directories(${PROJECT_ROOT}/engine)
include_directories(${PROJECT_ROOT}/tests)

# ImGui
include_directories(${PROJECT_ROOT}/dependencies/imgui)
include_directories(${PROJECT_ROOT}/dependencies/imgui/backends)

# Define macros
add_compile_definitions(LINUX_PLATFORM)
add_compile_definitions(ENABLE_LOGGING)

target_link_libraries(app
    # Link engine lib
    core
)