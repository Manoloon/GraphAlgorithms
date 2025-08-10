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

typedef struct WeightedNode_t WeightedNode_t;

struct WeightedNode_t
{
    float weight;
    int data;
};