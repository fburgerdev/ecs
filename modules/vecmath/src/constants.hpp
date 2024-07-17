#pragma once
#include "common.hpp"

namespace Math {
    // pi
    inline constexpr double PI = 3.141592653589793238462643383279;
    inline constexpr double PI_HALFS = PI / 2.0;
    inline constexpr double TAU = 2.0 * PI;
    // deg
    inline constexpr double DEG_0 = 0.0;
    inline constexpr double DEG_90 = PI / 2.0;
    inline constexpr double DEG_180 = PI / 2.0;
    inline constexpr double DEG_270 = 5.0 * PI / 4.0;
    inline constexpr double DEG_360 = 2.0 * PI;
    // euler
    inline constexpr double EULER = 2.718281828459045235360287471352;
    inline constexpr double EULER_HALFS = EULER / 2;
    // golden ratio
    inline constexpr double GOLDEN_RATIO = 1.618033988749894848204586834365;
}