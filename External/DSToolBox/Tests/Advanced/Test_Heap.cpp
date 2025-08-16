#include <gtest/gtest.h>

extern "C"
{
    #include "../Advanced/Heap.h"
}
heap_t* heap = NULL;
TEST(DSTB_Heap,CreateEmptyMin_MinCapacity)
{
    heap = heap_create_min(10);
    ASSERT_NE(heap,nullptr);
    EXPECT_EQ(heap_is_empty(heap),true);
}
TEST(DSTB_Heap,Insert)
{
    heap_insert(heap,(WeightedNode_t){0.1f,10});
    heap_insert(heap,(WeightedNode_t){0.7f,7});
    heap_insert(heap,(WeightedNode_t){0.3f,30});
    ASSERT_EQ(heap_is_empty(heap),false);
}
TEST(DSTB_Heap,Extract)
{
    WeightedNode_t ext = heap_extract(heap);
    ASSERT_EQ(ext.weight,0.1f);
    EXPECT_EQ(ext.data,10);
}
