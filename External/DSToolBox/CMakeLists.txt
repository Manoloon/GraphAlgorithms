add_library(DSToolBox
            Linear/SimpleQueue.c
            Linear/Stack.c
            Linear/PriorityQueue.c
            NonLinear/BinarySearchT.c
            NonLinear/DDA.c
            Advanced/Heap.c)
set(SOURCES 
            ${CMAKE_CURRENT_SOURCE_DIR}/Basics
            ${CMAKE_CURRENT_SOURCE_DIR}/Linear
            ${CMAKE_CURRENT_SOURCE_DIR}/NonLinear
            ${CMAKE_CURRENT_SOURCE_DIR}/Advanced
            ${CMAKE_CURRENT_SOURCE_DIR}/HashBased)
# Optionally expose its headers
target_include_directories(DSToolBox PUBLIC ${SOURCES})
find_package(raylib REQUIRED)
target_link_libraries(DSToolBox PRIVATE raylib)
# test
find_package(GTest REQUIRED)
add_executable(DSToolBoxTests Tests/Linear/Test_SimpleQueue.cpp ${SOURCES})
target_include_directories(DSToolBoxTests PRIVATE ${SOURCES})
target_link_libraries(DSToolBoxTests PRIVATE DSToolBox raylib GTest::gtest_main)