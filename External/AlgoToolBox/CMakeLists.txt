add_library(AlgoToolBox
            Algo/algo_bfs.c
            Algo/algo_dfs.c
            DataStructure/Queue.c
            DataStructure/Stack.c)
# Optionally expose its headers
target_include_directories(AlgoToolBox PUBLIC 
                    ${CMAKE_CURRENT_SOURCE_DIR}/Algo
                    ${CMAKE_CURRENT_SOURCE_DIR}/DataStructure)        