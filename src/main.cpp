#include <iostream>
#include <random>
#include "AABB.hpp"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-100.0, 100.0);



    const size_t numPoints = 1000;
    std::vector<collision::Vector3> points;
    points.reserve(numPoints);

    for (size_t i = 0; i < numPoints; ++i) {
        points.emplace_back(dist(gen), dist(gen), dist(gen));
    }

    collision::AABB axis_aligned_bounding_box = collision::AABB();

    for (const auto& point : points) {
        axis_aligned_bounding_box.extend(point);
    }

    std::cout << "Box Min:" << axis_aligned_bounding_box.min().transpose() << std::endl;
    std::cout << "Box Max: " << axis_aligned_bounding_box.max().transpose() << std::endl;

    return 0;
}