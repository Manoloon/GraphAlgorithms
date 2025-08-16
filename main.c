#include <stdio.h>
#include <stdlib.h>
#include "Src/node.h"
#include "Src/Algo/algo_bfs.h"
#include "Src/Algo/algo_dfs.h"
#include "BinarySearchT.h"
#include "DDA.h"
#include "Heap.h"
#include "Src/graph.h"
#include "Src/graphMatrix.h"



// int argc,char* argv[]
int main(int argc, char* argv[]) 
{
    if(argc < 3)
    {
        printf("usage %s <input_file> <output_file>\n",argv[0]);
        return 1;
    }
    //argv[1] = input file , argv[2] = output file
    heap_consoleTest(true,argv[1],argv[2]);
    printf("\n");
    heap_consoleTest(false,argv[1],argv[2]);
    // BST test
    //bst_raylib_test(true);
    //DDA_test();
    // graph matrix
    /*
    graphMatrix_t gMatrix;
    graphMatrix_init(&gMatrix,13,true);
    graphMatrix_draw(&gMatrix);
    graphMatrix_destroy(&gMatrix);
*/
   // bfs_test();
   // dfs_test();
    //bst_console_test();
    return 0;
}