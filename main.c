#include <stdio.h>
#include <stdlib.h>
#include "Src/node.h"
#include "Src/Algo/algo_bfs.h"
#include "Src/Algo/algo_dfs.h"
#include "BinarySearchT.h"
#include "DDA.h"
#include "Src/graph.h"
#include "Src/graphMatrix.h"

// int argc,char* argv[]
int main() 
{
    // BST test
    //bst_raylib_test(true);
    DDA_test();
    // graph matrix
    /*
    graphMatrix_t gMatrix;
    graphMatrix_init(&gMatrix,13,true);
    graphMatrix_draw(&gMatrix);
    graphMatrix_destroy(&gMatrix);
*/
   // bfs_test();
   // dfs_test();
    bst_console_test();
    return 0;
}