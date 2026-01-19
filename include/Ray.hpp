#ifndef COLLISION_BENCH_RAY_HPP
#define COLLISION_BENCH_RAY_HPP

#include "Point.hpp"

namespace collision {
    class Ray {
        /**
         * @brief A Ray primitive.
         * Used for fast collision dectection.
        */
    public:
        /**
         * @brief Construct a Ray.
         * @param origin The origin point of the ray
         * @param direction The direction of the ray.
         * @note direction should be a normalized vector.
         */
        Ray(const Vector3& origin, const Vector3& direction) :
        origin_(origin),
        direction_(direction),
        inv_direction_(1.0 / direction.array())
        {
            //check to verify that the direction is normalized when debugging
            assert(std::abs(direction.squaredNorm() - 1.0) < 1e-9);
        };

        /**
         *@brief Computes a point along the ray at distance t.
         *@param t The distance along the ray.
         */
        //it's faster to pass small primitive types by value
        Vector3 at(double t) const {
            return origin_ + (t * direction_);
        };

        const Vector3& origin() const { return origin_; };
        const Vector3& direction() const { return direction_; };
        const Vector3& invDirection() const { return inv_direction_; };

    private:
        //using const members for thread safety and compiler optimization.
        const Vector3 origin_;
        const Vector3 direction_;
        const Vector3 inv_direction_;
    };
};



#endif //COLLISION_BENCH_RAY_HPP