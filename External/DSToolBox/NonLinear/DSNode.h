#pragma once 
/*
Generic node for tree structures.
*/
typedef struct DSNode_t DSNode_t;

struct DSNode_t
{
    int data;
    DSNode_t* left;
    DSNode_t* right;
};
