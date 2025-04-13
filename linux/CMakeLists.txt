cmake_minimum_required(VERSION 3.26.3)

# Set project name
project(OpenGLProject)

# Set Cpp version
set (CMAKE_CXX_STANDARD 17)

# Set other properties
if (PROJECT_ROOT)
    message("PROJECT_ROOT found")
else ()
    set (PROJECT_ROOT "${CMAKE_SOURCE_DIR}/..")
endif ()

message("PROJECT_ROOT = ${PROJECT_ROOT}")

set (PROJECT_DEPENDENCIES "${PROJECT_ROOT}/dependencies")

if (UNIX)
    # Enable warnings
    set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
    message("Enabled warning for Unix target")
endif ()

##############################################################################
# Create static lib
##############################################################################

add_library(core
    # Core files
    ${PROJECT_ROOT}/engine/opengl/IndexBuffer.cpp
    ${PROJECT_ROOT}/engine/opengl/VertexArray.cpp
    ${PROJECT_ROOT}/engine/opengl/VertexBuffer.cpp
    ${PROJECT_ROOT}/engine/opengl/Layout.cpp
    ${PROJECT_ROOT}/engine/window/Window.cpp
    ${PROJECT_ROOT}/engine/external/PlatformGateWay.cpp
    ${PROJECT_ROOT}/engine/opengl/Shader.cpp
    ${PROJECT_ROOT}/engine/opengl/external/LoaderOpenGL.cpp
    ${PROJECT_ROOT}/engine/opengl/GLEngine.cpp
    ${PROJECT_ROOT}/engine/opengl/render/Renderer.cpp
    ${PROJECT_ROOT}/engine/opengl/Textures.cpp
    # ImGui files
    ${PROJECT_ROOT}/dependencies/imgui/imgui.cpp
    ${PROJECT_ROOT}/dependencies/imgui/imgui_draw.cpp
    ${PROJECT_ROOT}/dependencies/imgui/imgui_tables.cpp
    ${PROJECT_ROOT}/dependencies/imgui/imgui_widgets.cpp
    ${PROJECT_ROOT}/dependencies/imgui/backends/imgui_impl_opengl3.cpp
    ${PROJECT_ROOT}/dependencies/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_ROOT}/engine/app/MainApplication.cpp
    ${PROJECT_ROOT}/engine/common/Exception.cpp
    ${PROJECT_ROOT}/engine/MainThread.cpp
    ${PROJECT_ROOT}/engine/EntryPoint.cpp
    ${PROJECT_ROOT}/engine/ui/DecoratorUI.cpp
    ${PROJECT_ROOT}/engine/ui/Widgets.cpp
    ${PROJECT_ROOT}/engine/common/Log.cpp
    ${PROJECT_ROOT}/engine/opengl/shapes/Rectangle.cpp
    ${PROJECT_ROOT}/engine/opengl/render/RenderData.cpp
    ${PROJECT_ROOT}/engine/opengl/shapes/Line.cpp
    ${PROJECT_ROOT}/engine/opengl/render/RenderDirector.cpp
    ${PROJECT_ROOT}/engine/opengl/render/RenderDirectorBase.cpp
    ${PROJECT_ROOT}/engine/opengl/Camera.cpp
    ${PROJECT_ROOT}/engine/window/input/Input.cpp
    ${PROJECT_ROOT}/engine/component/LayerStack.cpp
    ${PROJECT_ROOT}/engine/common/Timestamp.cpp
    ${PROJECT_ROOT}/engine/external/GUIHelper.cpp
    ${PROJECT_ROOT}/engine/component/Layer.cpp
)

# Define macros
if (UNIX)
    add_compile_definitions(LINUX_PLATFORM)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(ENABLE_LOGGING)
    message("Enabled debug build configs")
endif ()

if (ENABLE_UNIT_TESTS)
    add_compile_definitions(UNIT_TESTS)
    message("Enabled unit tests build configs")
else ()
    set (BUILD_TEST_APP "TRUE")
endif ()

# Ask Cmake to find OpenGL on the system
find_package(OpenGL REQUIRED)

# Switch to local GLFW build
add_subdirectory(${PROJECT_DEPENDENCIES}/glfw ${PROJECT_DEPENDENCIES}/glfw)

# Include dirs & libs
include_directories(${PROJECT_DEPENDENCIES}/linux/GLEW/include)
include_directories(${PROJECT_DEPENDENCIES}/glfw/include)

include_directories(${PROJECT_ROOT}/engine)
include_directories(${PROJECT_DEPENDENCIES})

# ImGui includes
include_directories(${PROJECT_DEPENDENCIES}/imgui)
include_directories(${PROJECT_DEPENDENCIES}/imgui/backends)

##############################################################################
# Link all dependencies
##############################################################################

# opengl
target_link_libraries(core ${OPENGL_LIBRARY})
# glfw
target_link_libraries(core glfw)
# glew
target_link_libraries(core ${PROJECT_DEPENDENCIES}/linux/GLEW/lib/libGLEW.so)

##############################################################################
# Test app
##############################################################################

if (BUILD_TEST_APP)
    message("Test app build")

    # Build final test app
    add_executable(TestApp
        ../tests/ui_tests/Application.cpp
        ../tests/ui_tests/TestMenuUI.cpp
        ../tests/ui_tests/TextureTest.cpp
        ../tests/ui_tests/BatchingTest.cpp
        ../tests/ui_tests/ShapesTest.cpp
        ../tests/ui_tests/base/TestCase.cpp
        ../tests/ui_tests/BlankTest.cpp
    )

    include_directories(../tests/ui_tests)
    include_directories(../tests)

    target_link_libraries(TestApp
        # Link engine lib
        core
    )

else ()
    message("No test app build")
endif ()