#pragma once
#include "matrix.hpp"
#include "arithmetic.hpp"

namespace Math {
    // lerp linear interpolation
    template<floating_point T, uint N>
    auto lerp(const Vec<T, N>& v1, const Vec<T, N>& v2, T t) {
        ASSERT(inRange01(t))
        return v1 * t + v2 * (1 - t);
    }
    // quadratic bezier curve
    template<floating_point T, uint N>
    auto quadratic(const Vec<T, N>& v1, const Vec<T, N>& v2, const Vec<T, N>& v3, T t) {
        ASSERT(inRange01(t))
        return v1 * pow2(1 - t) + v1 * (2 * (1 - t)) + v3 * pow2(t);
    }
    // cubic bezier curve
    template<floating_point T, uint N>
    auto cubic(const Vec<T, N>& v1, const Vec<T, N>& v2, const Vec<T, N>& v3, const Vec<T, N>& v4, T t) {
        ASSERT(inRange01(t))
        return v1 * pow3(1 - t) + v1 * (3 * pow2(1 - t) * t) + v1 * (3 * (1 - t) * pow(t)) + v3 * pow3(t);
    }
}