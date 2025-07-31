cmake_minimum_required(VERSION 3.5)
project(loom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

#-------------------------------------------------------------------------------
# Find SDL3

find_package(SDL3 CONFIG REQUIRED)


#-------------------------------------------------------------------------------
# Find alpaka

if(NOT TARGET alpaka::alpaka)
    option(alpaka_USE_SOURCE_TREE "Use alpaka's source tree instead of an alpaka installation" ON)

    if(alpaka_USE_SOURCE_TREE)
        # Don't build the examples recursively
        set(alpaka_BUILD_EXAMPLES OFF)
        add_subdirectory("/home/ikbuibui/src/alpaka3" "${CMAKE_BINARY_DIR}/alpaka")
    else()
        find_package(alpaka REQUIRED)
    endif()
endif()

#-------------------------------------------------------------------------------
# Add executable.

alpaka_add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 )
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    alpaka::alpaka)
