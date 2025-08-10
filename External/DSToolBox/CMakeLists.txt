add_library(DSToolBox
            Linear/SimpleQueue.c
            Linear/Stack.c
            Linear/PriorityQueue.c
            NonLinear/BinarySearchT.c
            NonLinear/DDA.c
            Advanced/Heap.c)
# Optionally expose its headers
target_include_directories(DSToolBox PUBLIC 
                    ${CMAKE_CURRENT_SOURCE_DIR}/Basics
                    ${CMAKE_CURRENT_SOURCE_DIR}/Linear
                    ${CMAKE_CURRENT_SOURCE_DIR}/NonLinear
                    ${CMAKE_CURRENT_SOURCE_DIR}/Advanced
                    ${CMAKE_CURRENT_SOURCE_DIR}/HashBased
                    ${CMAKE_CURRENT_SOURCE_DIR})
find_package(raylib REQUIRED)
target_link_libraries(DSToolBox PRIVATE raylib)