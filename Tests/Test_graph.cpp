#include <gtest/gtest.h>

extern "C"
{
    #include "../Src/graph.h"
}
TEST(GraphTests,CerateBasicGraph)
{
    int num_nodes = 10;
    bool undirected = true;
    graph_t* g = graph_create(num_nodes,undirected);
    ASSERT_NE(g,nullptr);
    EXPECT_EQ(g->num_nodes,num_nodes);
    EXPECT_EQ(g->undirected,undirected);
    ASSERT_NE(g->nodes,nullptr);

    for(int i= 0;i < num_nodes;++i)
    {
        EXPECT_EQ(g->nodes[i].index,i);
        EXPECT_EQ(g->nodes[i].data,i);
        EXPECT_EQ(g->nodes[i].edges,nullptr);
        EXPECT_EQ(g->nodes[i].num_edges,0);
        EXPECT_EQ(g->nodes[i].edge_capacity,0);
    }
    free(g->nodes);
    free(g);
}

TEST(GraphTests,CreateGraphZeroNodes)
{
    graph_t* g = graph_create(0,false);
    ASSERT_NE(g,nullptr);
    EXPECT_EQ(g->num_nodes,0);
    EXPECT_EQ(g->nodes,nullptr);

    free(g);
}