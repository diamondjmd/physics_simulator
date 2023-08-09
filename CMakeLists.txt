cmake_minimum_required(VERSION 3.7.2)
project(physics)

set(CMAKE_CXX_STANDARD 17)

# Trying to find preinstalled SFML
find_package(SFML COMPONENTS graphics)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # If SFML is not found - download and build from source
    message(STATUS "Get SFML from the source code")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    #  Work around potential issues when building sfml-graphics
    # (stb_image.h: 'argument': conversion from 'int' to 'short')
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

# Unfortunately, up to C++20 https://en.cppreference.com/w/cpp/numeric/constants
# no convenient cross-platform way to get pi.
# define below is needed to enable M_PI
if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

add_executable(physics
        main.cpp World.cpp Ball.cpp Physics.cpp Color.cpp Painter.cpp
        black_box/Application.cpp black_box/View.cpp black_box/PainterImpl.cpp)
target_link_libraries(physics PRIVATE sfml-graphics)

target_compile_options(physics PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /EHsc /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -g >
        )

