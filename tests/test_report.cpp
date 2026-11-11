#include <gtest/gtest.h>
#include "file_handler.h"
#include "record.h"
#include <stdio.h>

TEST(FileHandlerTest, SaveAndLoad) {
    total_orders = 0;
    addOrder(555, "Dupatta", STATUS_PENDING);
    
    EXPECT_EQ(saveRecordsToFile("data/test_data.txt"), 0);
    
    total_orders = 0; // Clear memory to simulate restart
    
    EXPECT_EQ(loadRecordsFromFile("data/test_data.txt"), 0);
    EXPECT_EQ(total_orders, 1);
    EXPECT_EQ(order_database[0].order_id, 555);
    
    remove("data/test_data.txt"); // Cleanup
}