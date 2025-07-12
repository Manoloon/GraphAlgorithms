cmake_minimum_required(VERSION 3.25.0)
project(GraphAlgorithm VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-std=c11 -Wall -Wextra -Wpedantic -Wshadow)
# Set source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Src")

add_subdirectory(Src)

# Create the executable with main.c and src's sources
add_executable(GraphAlgorithm main.c ${SRC_SOURCES} ${ALGO_SOURCES})

# Add include directories
target_include_directories(GraphAlgorithm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Algo
)