#include <iostream>
#include <Eigen/Core>

int main() {
    std::cout << "--- Collision Bench: System Check ---" << std::endl;

    // Check Eigen Version
    std::cout << "Eigen Version: "
              << EIGEN_WORLD_VERSION << "."
              << EIGEN_MAJOR_VERSION << "."
              << EIGEN_MINOR_VERSION << std::endl;

    // Check for SIMD (Instruction Sets)
    std::cout << "SIMD Instructions Enabled: " << Eigen::SimdInstructionSetsInUse() << std::endl;

    // Simple Math Test
    Eigen::Vector3d v1(1.0, 2.0, 3.0);
    Eigen::Vector3d v2(3.0, 2.0, 1.0);
    double dotProduct = v1.dot(v2);

    std::cout << "Math Test (Dot Product): " << dotProduct << std::endl;

    if (dotProduct == 10.0) {
        std::cout << "Status: Success. Eigen is configured correctly." << std::endl;
    } else {
        std::cout << "Status: Failure. Math results inconsistent." << std::endl;
    }

    return 0;
}