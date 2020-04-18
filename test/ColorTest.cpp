#include <gtest/gtest.h>
#include "../includes/Color.hpp"

TEST(Color, Construct) {
    Color c({100, 50, 30, 10});
    ASSERT_EQ(100, c.r);
    ASSERT_EQ(50, c.g);
    ASSERT_EQ(30, c.b);
    ASSERT_EQ(10, c.a);
}

TEST(Color, Construct_OutOfRangeValues) {
    Color c({76, -24, 0, 385});
    ASSERT_EQ(76, c.r);
    ASSERT_EQ(0, c.g);
    ASSERT_EQ(0, c.b);
    ASSERT_EQ(255, c.a);
}

TEST(Color, Lerp) {
    Color c1({100, 50, 30, 10});
    Color c2({200, 100, 40, 90});
    Color c = Color::lerp(&c1, &c2, 0.4, 0.6, 0.5);
    ASSERT_EQ(149, c.r);
    ASSERT_EQ(74, c.g);
    ASSERT_EQ(35, c.b);
    ASSERT_EQ(49, c.a);
}