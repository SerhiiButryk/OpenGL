cmake_minimum_required(VERSION 3.26.3)

# Set project name
project(UnitTests)

set (CMAKE_CXX_STANDARD 17)
set (PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../..")

# Enable unit tests
set (ENABLE_UNIT_TESTS "TRUE")

# enable testing functionality
enable_testing()

file(MAKE_DIRECTORY build)
add_subdirectory(${PROJECT_ROOT}/linux build)

add_executable(UniTests
        base/TestLauncher.cpp
        base/Registry.cpp
        BasicTest.cpp
        base/MemoryTracker.cpp
        InitTests.cpp
        ShaderTests.cpp
)

target_compile_definitions(UniTests PUBLIC -DUNIT_TESTS)
target_compile_definitions(UniTests PUBLIC -DENABLE_LOGGING)

target_link_libraries(UniTests
    # Link engine lib
    core
)

# Includes for tests
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${PROJECT_ROOT}/engine)
include_directories(${PROJECT_ROOT}/dependencies)

# Add Unit Tests (Displayed test name + test args)
add_test(NAME BasicTest COMMAND UniTests BasicTest)
add_test(NAME InitTests COMMAND UniTests InitTests)
add_test(NAME ShaderTests COMMAND UniTests ShaderTests)