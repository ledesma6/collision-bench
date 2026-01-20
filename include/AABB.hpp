#ifndef COLLISION_BENCH_AABB_HPP
#define COLLISION_BENCH_AABB_HPP

#include <limits>
#include "Point.hpp"
#include "Ray.hpp"

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
         * @brief Checks if a point is inside the box using standard branching and an early exit strategy.
         * @param point The 3d coordinate to test
         */
        bool contains_naive(const Vector3& point) const {
            if (point.x() < min_.x() || point.x() > max_.x()) return false;
            if (point.y() < min_.y() || point.y() > max_.y()) return false;
            if (point.z() < min_.z() || point.z() > max_.z()) return false;
            return true;
        }

        /**
         * @brief Expands the box to include the given point.
         * @param point The 3d coordinate to incorporate into the bounds
         */
        void extend(const Vector3& point) {
            // more component-wise operations to update values
            min_ = min_.cwiseMin(point);
            max_ = max_.cwiseMax(point);
        };

        /**
         * @brief Expands the box to include the given point using standard branching.
         * @param point The 3d coordinate to incorporate into the bounds
         */
        void extend_naive(const Vector3& point) {
            if (point.x() < min_.x()) min_.x() = point.x();
            if (point.y() < min_.y()) min_.y() = point.y();
            if (point.z() < min_.z()) min_.z() = point.z();

            if (point.x() > max_.x()) max_.x() = point.x();
            if (point.y() > max_.y()) max_.y() = point.y();
            if (point.z() > max_.z()) max_.z() = point.z();
        };

        /**
         * @brief Verifies if a ray intersects the box using the Slab Method.
         * @param ray The ray to test against the box.
         */
        bool intersects(const Ray& ray) const {
            //calculate the intersection distances
            Vector3 t_a = (min_ - ray.origin()).cwiseProduct(ray.invDirection());
            Vector3 t_b = (max_ - ray.origin()).cwiseProduct(ray.invDirection());
            //find the entry and exit distances
            Vector3 t_near = t_a.cwiseMin(t_b);
            Vector3 t_far = t_a.cwiseMax(t_b);
            //find the entry and exit intervals
            double t_start = t_near.maxCoeff();
            double t_end = t_far.minCoeff();
            return t_start <= t_end && t_end > 0;
        };

    private:
        Vector3 min_;
        Vector3 max_;
    };
}

#endif //COLLISION_BENCH_AABB_HPP