#include <gtest/gtest.h>

extern "C"
{
    #include "../Advanced/Heap.h"
}
class DSTB_Heap : public ::testing::Test
{
    protected:
        heap_t* heap;
        WeightedNode_t nod1 = {0.1f,10};
        WeightedNode_t nod2 = {0.2f,20};
        WeightedNode_t nod3 = {0.7f,70};
        WeightedNode_t nod4 = {0.4f,40};
    void SetUp() override
    {
        heap = heap_create_min(10);
    }
    void TearDown() override
    {
        // destroy heap
    }
};
TEST_F(DSTB_Heap,CreateMinEmpty)
{
    ASSERT_NE(heap,nullptr);
    EXPECT_EQ(heap_is_empty(heap),true);
    ASSERT_TRUE(heap_is_min(heap));
}
TEST_F(DSTB_Heap,Insert)
{
    heap_insert(heap,nod2);
    heap_insert(heap,nod3);
    heap_insert(heap,nod4);
    ASSERT_FALSE(heap_is_empty(heap));
}
TEST_F(DSTB_Heap,Extract)
{
    heap_insert(heap,nod1);
    WeightedNode_t ext = heap_extract(heap);
    ASSERT_EQ(ext.weight,nod1.weight);
    EXPECT_EQ(ext.data,nod1.data);
}
