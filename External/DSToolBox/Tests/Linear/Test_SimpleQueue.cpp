#include <gtest/gtest.h>

extern "C"
{
    #include "../Linear/SimpleQueue.h"
}

TEST(DSToolTests,CreateEmptySQueue)
{
    queue_t* q = queue_create(1);
    ASSERT_NE(q,nullptr);
    queue_destroy(q);
    ASSERT_EQ(q,nullptr);
}