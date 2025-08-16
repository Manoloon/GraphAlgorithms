#include <gtest/gtest.h>

extern "C"
{
    #include "../Linear/SimpleQueue.h"
}
queue_t* q = NULL;
TEST(DSTB_Queue,CreateEmpty)
{
    q = queue_create(4);
    ASSERT_NE(q,nullptr);
}

TEST(DSTB_Queue,DestroyIt)
{
    queue_destroy(q);
    ASSERT_EQ(q,nullptr);
}