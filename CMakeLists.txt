cmake_minimum_required(VERSION 3.25.0)
project(GraphAlgorithm VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-std=c11 -Wall -Wextra -Wpedantic -Wshadow)
# Set source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Src")

add_subdirectory(External/AlgoToolBox)

# Create the executable with main.c and src's sources
add_executable(GraphAlgorithm main.c 
                Src/graph.c 
                Src/graphMatrix.c 
                Src/node.c)

target_link_libraries(GraphAlgorithm PRIVATE AlgoToolBox)