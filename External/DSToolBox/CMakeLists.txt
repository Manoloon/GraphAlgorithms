add_library(DSToolBox
            Linear/Queue.c
            Linear/Stack.c
            NonLinear/BinarySearchT.c)
# Optionally expose its headers
target_include_directories(DSToolBox PUBLIC 
                    ${CMAKE_CURRENT_SOURCE_DIR}/Linear
                    ${CMAKE_CURRENT_SOURCE_DIR}/NonLinear
                    ${CMAKE_CURRENT_SOURCE_DIR}/Advanced
                    ${CMAKE_CURRENT_SOURCE_DIR}/HashBased
                    ${CMAKE_CURRENT_SOURCE_DIR})        