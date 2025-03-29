cmake_minimum_required(VERSION 3.30)
project(BlankSample)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(/home/serhii/Development/GitHub/OpenGL/dependencies/glfw /home/serhii/Development/GitHub/OpenGL/dependencies/glfw)

add_executable(BlankSample
        main.cpp
        /home/serhii/Development/GitHub/OpenGL/dependencies/imgui/imgui.cpp
        /home/serhii/Development/GitHub/OpenGL/dependencies/imgui/imgui_draw.cpp
        /home/serhii/Development/GitHub/OpenGL/dependencies/imgui/imgui_tables.cpp
        /home/serhii/Development/GitHub/OpenGL/dependencies/imgui/imgui_widgets.cpp
        /home/serhii/Development/GitHub/OpenGL/dependencies/imgui/backends/imgui_impl_glfw.cpp
        /home/serhii/Development/GitHub/OpenGL/dependencies/imgui/backends/imgui_impl_opengl3.cpp
        /home/serhii/Development/GitHub/OpenGL/dependencies/imgui/imgui_demo.cpp
)

include_directories(/home/serhii/Development/GitHub/OpenGL/dependencies/glfw/include/)

include_directories(/home/serhii/Development/GitHub/OpenGL/dependencies/imgui)
include_directories(/home/serhii/Development/GitHub/OpenGL/dependencies/imgui/backends)

find_package(OpenGL REQUIRED)

target_link_libraries(BlankSample ${OPENGL_LIBRARY})
# Switch to local GLFW build
target_link_libraries(BlankSample glfw)
target_link_libraries(BlankSample /home/serhii/Development/GitHub/OpenGL/dependencies/linux/GLEW/lib/libGLEW.so)
