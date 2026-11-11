#include <gtest/gtest.h>
#include "validation.h"

TEST(ValidationTest, ValidIdCheck) {
    EXPECT_EQ(isValidId(5001), 1);
    EXPECT_EQ(isValidId(-10), 0);
    EXPECT_EQ(isValidId(0), 0);
}

TEST(ValidationTest, ValidStatusCheck) {
    EXPECT_EQ(isValidStatus(0), 1); // Pending
    EXPECT_EQ(isValidStatus(3), 1); // Returned
    EXPECT_EQ(isValidStatus(4), 0); // Invalid
    EXPECT_EQ(isValidStatus(-1), 0); // Invalid
}