cmake_minimum_required(VERSION 3.25.0)
project(GraphAlgorithm VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-std=c11 -Wall -Wextra -Wpedantic -Wshadow)
find_package(raylib REQUIRED)
add_subdirectory(External/DSToolBox)
# Source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)
set(ALGO_DIR ${SRC_DIR}/Algo)
set(SOURCES
    ${SRC_DIR}/graph.c
    ${SRC_DIR}/graphMatrix.c
    ${SRC_DIR}/node.c
    ${ALGO_DIR}/algo_bfs.c
    ${ALGO_DIR}/algo_dfs.c
)
# Create the executable with main.c and src's sources
add_executable(GraphAlgorithm main.c ${SOURCES})
target_include_directories(GraphAlgorithm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
)
target_link_libraries(GraphAlgorithm PRIVATE DSToolBox)
target_link_libraries(GraphAlgorithm PRIVATE raylib)