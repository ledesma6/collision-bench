#include <gtest/gtest.h>
#include "AABB.hpp"

// Test that an uninitialized box is "inverted" (empty)
TEST(AABBTest, InitializationIsConsistent) {
    collision::AABB box;
    collision::Vector3 origin(0.0, 0.0, 0.0);

    // An empty box should not contain the origin
    EXPECT_FALSE(box.contains(origin));

    // Check that min is +inf and max is -inf
    EXPECT_TRUE(box.min().x() > 1e18);
    EXPECT_TRUE(box.max().x() < -1e18);
}

// Test basic extension logic
TEST(AABBTest, ExtendsToFitPoints) {
    collision::AABB box;
    box.extend({-5.0, -5.0, -5.0});
    box.extend({5.0, 5.0, 5.0});

    EXPECT_TRUE(box.contains({0, 0, 0}));
    EXPECT_TRUE(box.contains({-5.0, 0, 0}));
    EXPECT_FALSE(box.contains({6.0, 0, 0}));
}