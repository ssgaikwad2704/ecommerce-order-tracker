#include <gtest/gtest.h>
#include "record.h"

class RecordTest : public ::testing::Test {
protected:
    void SetUp() override {
        total_orders = 0;
    }
};

TEST_F(RecordTest, AddOrderSuccess) {
    EXPECT_EQ(addOrder(1001, "Cotton_Dress", STATUS_PENDING), 0);
    EXPECT_EQ(total_orders, 1);
    EXPECT_EQ(order_database[0].order_id, 1001);
}

TEST_F(RecordTest, UpdateOrderStatus) {
    addOrder(1002, "Three-Piece_Set", STATUS_DISPATCHED);
    EXPECT_EQ(updateOrderStatus(1002, STATUS_DELIVERED), 0);
    EXPECT_EQ(order_database[0].status, STATUS_DELIVERED);
    
    // Test updating a non-existent ID
    EXPECT_EQ(updateOrderStatus(9999, STATUS_RETURNED), -1); 
}