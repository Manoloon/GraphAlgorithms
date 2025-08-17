#include <gtest/gtest.h>

extern "C"
{
    #include "../Linear/SimpleQueue.h"
}
// fixture
class DSTB_SimpleQueue : public ::testing::Test
{
    protected:
        queue_t* q;
        int val1 = 10;
        int val2 = 20;
        int val3 = 30;
        int val4 = 40;
        void SetUp() override
        {
            q = queue_create(10);
            queue_push(q, &val1);
            queue_push(q, &val2);
            queue_push(q, &val3);
            queue_push(q, &val4);
        }
        void TearDown() override
        {
            queue_destroy(q);
        }
};

TEST_F(DSTB_SimpleQueue,Created)
{
    ASSERT_NE(q,nullptr);
}

TEST_F(DSTB_SimpleQueue,Push)
{
    EXPECT_FALSE(queue_is_empty(q));
    int* peek =(int*) queue_peek(q);
    ASSERT_EQ(10,*peek);
}

TEST_F(DSTB_SimpleQueue,Pop)
{
    int* pop = (int*)queue_pop(q);
    EXPECT_EQ(10,*pop);
    pop = (int*)queue_pop(q);
    EXPECT_EQ(20,*pop);
    pop = (int*)queue_pop(q);
    EXPECT_EQ(30,*pop);
    pop = (int*)queue_pop(q);
    EXPECT_EQ(40,*pop);
    EXPECT_TRUE(queue_is_empty(q));
}