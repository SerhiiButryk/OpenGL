cmake_minimum_required(VERSION 3.26.3)

# Set project name
project(OpenGLProject)

# Set Cpp version
set (CMAKE_CXX_STANDARD 17)
set (PROJECT_DEPENDENCIES "${CMAKE_SOURCE_DIR}/../dependencies")
set (PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../engine")

# Building unit tests
set (BUILD_UNIT_TESTS "TRUE")
# Building test app
set (BUILD_TEST_APP "TRUE")

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
    ../engine/MainApplication.cpp
    ../engine/common/Exception.cpp
    ../engine/MainThread.cpp
    ../engine/EntryPoint.cpp
    ../engine/ui/AppUI.cpp
    ../engine/ui/Widgets.cpp
)

# Define macros
if (UNIX)
    add_compile_definitions(LINUX_PLATFORM)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(ENABLE_LOGGING)

    if (${BUILD_UNIT_TESTS} STREQUAL "TRUE")
        add_compile_definitions(UNIT_TESTS)
    endif ()

    message("Enabled debug build configs")
endif ()

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

##############################################################################
# Link all dependencies
##############################################################################

# 1) glfw
# 2) opengl
# 2) glew
target_link_libraries(core
    GLEW
    ${OPENGL_LIBRARY} # Filled by Cmake
    glfw
)

##############################################################################
# Build test app
##############################################################################

if (${BUILD_TEST_APP} STREQUAL "TRUE")
    message("Building test app")

    # Build final test app
    add_executable(TestApp
        ../tests/Application.cpp
        ../tests/ui_tests/TestMenuUI.cpp
        ../tests/ui_tests/base/TestUI.cpp
        ../tests/ui_tests/BackgroundColorTest.cpp
        ../tests/ui_tests/TextureTest.cpp
    )

    include_directories(../tests/ui_tests)
    include_directories(../tests)

    include_directories(${PROJECT_DEPENDENCIES}/linux/GLFW/include)
    link_directories(${PROJECT_DEPENDENCIES}/linux/GLFW/lib)

    target_link_libraries(TestApp
        # Link engine lib
        core
        glfw
    )

else ()
    message("No test app")
endif ()

##############################################################################
# Unit tests
##############################################################################

if (${BUILD_UNIT_TESTS} STREQUAL "TRUE")
    message("Building unit tests")

    # enable testing functionality
    enable_testing()

    add_executable(UniTests
        ../tests/unit_tests/base/TestLauncher.cpp
        ../tests/unit_tests/base/Registry.cpp
        ../tests/unit_tests/MemoryLeakTest.cpp
        ../tests/unit_tests/base/MemoryTracker.cpp
        ../tests/unit_tests/InitTests.cpp
    )

    target_link_libraries(UniTests
            # Link engine lib
            core
    )

    # Add Unit Tests (Displayed test name + test args)
    add_test(NAME MemoryLeakTest COMMAND UniTests MemoryLeakTest)
    add_test(NAME InitTests COMMAND UniTests InitTests)

else ()
    message("No unit tests")
endif ()