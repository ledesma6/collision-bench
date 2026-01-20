#include <random>
#include <gtest/gtest.h>
#include "AABB.hpp"
#include "Ray.hpp"

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

// Test consistency between naive and component-wise implementations of contains and extend
TEST(AABBConsistency, NaiveMatchesOptimized) {
    collision::AABB box_naive, box_optimized;

    // Use a fixed seed for reproducibility in tests
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-100.0, 100.0);

    // 1. Stress test the 'extend' logic
    for (int i = 0; i < 1000; ++i) {
        collision::Vector3 p(dist(gen), dist(gen), dist(gen));
        box_naive.extend_naive(p);
        box_optimized.extend(p);

        // Eigen provides a way to check equality within a tolerance
        ASSERT_TRUE(box_naive.min().isApprox(box_optimized.min()))
            << "Min mismatch at iteration " << i;
        ASSERT_TRUE(box_naive.max().isApprox(box_optimized.max()))
            << "Max mismatch at iteration " << i;
    }

    // 2. Stress test the 'contains' logic
    for (int i = 0; i < 1000; ++i) {
        collision::Vector3 p(dist(gen), dist(gen), dist(gen));
        // expect identical boolean results
        EXPECT_EQ(box_naive.contains_naive(p), box_optimized.contains(p))
            << "Contains mismatch at iteration " << i;
    }
}

TEST(AABBIntersectionTest, BasicScenarios) {
    collision::AABB box(collision::Vector3(-1, -1, -1), collision::Vector3(1, 1, 1));

    //hits the front face
    collision::Ray ray_hit(collision::Vector3(0, 0, -5), collision::Vector3(0, 0, 1));
    EXPECT_TRUE(box.intersects(ray_hit));

    //pointing away from the box
    collision::Ray ray_miss(collision::Vector3(0, 0, -5), collision::Vector3(0, 1, 0));
    EXPECT_FALSE(box.intersects(ray_miss));

    //origin inside the box
    collision::Ray ray_inside(collision::Vector3(0, 0, 0), collision::Vector3(0, 0, 1));
    EXPECT_TRUE(box.intersects(ray_inside));

}