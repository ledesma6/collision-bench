#ifndef COLLISION_BENCH_AABB_HPP
#define COLLISION_BENCH_AABB_HPP

#include <limits>
#include "Point.hpp"

namespace collision {
    /**
     * @brief An Axis-Aligned Bounding Box (AABB) primitive.
     * Used for fast collision dectection.
    */
    class AABB {
    public:
        /**
         * @brief Construct an "Inverted" AABB.  The first point added via extend() will set the initial bounds.
         */
        AABB() {
          min_.setConstant(std::numeric_limits<double>::infinity());
          max_.setConstant(-std::numeric_limits<double>::infinity());
        };

        /**
         * Construct an AABB with initial bounds.
         * @param min The lower bound of the box.
         * @param max The upper bound of the box.
         */
        AABB(const Vector3& min, const Vector3& max): min_(min), max_(max) {};

        const Vector3& min() const { return min_; };
        const Vector3& max() const { return max_; };


        /**
         * @brief Checks if a 3d point resides within the box boundaries.
         * @param point The 3d coordinate to test
         * @return true if the point is inside or on the boundary.
         */
        bool contains(const Vector3& point) const {
            // use component-wise comparison to avoid unnecessary branching
            return (point.array() >= min_.array()).all() &&
                   (point.array() <= max_.array()).all();
        };

        /**
         * @brief Expands the box to include the given point.
         * @param point The 3d coordinate to incorporate into the bounds
         */
        void extend(const Vector3& point) {
            // more component-wise operations to update values
            min_ = min_.cwiseMin(point);
            max_ = max_.cwiseMax(point);
        };

    private:
        Vector3 min_;
        Vector3 max_;
    };
}

#endif //COLLISION_BENCH_AABB_HPP