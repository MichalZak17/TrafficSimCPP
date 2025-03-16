cmake_minimum_required(VERSION 3.5)
project(TrafficSimCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(traffic_sim ${SOURCES})

# In case you want to set compiler warnings:
# if(MSVC)
#   target_compile_options(traffic_sim PRIVATE /W4)
# else()
#   target_compile_options(traffic_sim PRIVATE -Wall -Wextra -pedantic)
# endif()
