add_library(DSToolBox
            Queue.c
            Stack.c)
# Optionally expose its headers
target_include_directories(DSToolBox PUBLIC 
                    ${CMAKE_CURRENT_SOURCE_DIR})        