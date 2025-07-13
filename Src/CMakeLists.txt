add_subdirectory(Algo)
add_subdirectory(DataStructure)

set(SRC_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/node.c
     ${CMAKE_CURRENT_SOURCE_DIR}/graph.c
     ${CMAKE_CURRENT_SOURCE_DIR}/graphMatrix.c
    PARENT_SCOPE
    )