#pragma once
#include "constants.hpp"
#include "logging.hpp" // ASSERT
#include <concepts> // std::floating_point
#include <cmath> // floor / ceil, sqrt, trig, exp / log

namespace Math {
    // integral / floating
    using std::integral;
    using std::floating_point;
    template <typename T>
    concept numeric = integral<T> || floating_point<T>;
    
    // abs
    template<numeric T>
    T abs(T x) {
        return x > 0 ? x : -x;
    }

    // floor
    template<floating_point T>
    T floor(T x) {
        return std::floor(x);
    }
    // ceil
    template<floating_point T>
    T ceil(T x) {
        return std::ceil(x);
    }

    // sqrt
    template<floating_point T>
    T sqrt(T x) {
        ASSERT(x > 0)
        return std::sqrt(x);
    }

    // trig
    // :: sin
    template<floating_point T>
    T sin(T x) {
        return std::sin(x);
    }
    // :: cos
    template<floating_point T>
    T cos(T x) {
        return std::cos(x);
    }
    // :: tan
    template<floating_point T>
    T tan(T x) {
        ASSERT((x / PI_HALFS) != floor(x / PI_HALFS))
        return std::tan(x);
    }
    // :: asin
    template<floating_point T>
    T asin(T x) {
        ASSERT(abs(x) <= 1)
        return std::asin(x);
    }
    // :: acos
    template<floating_point T>
    T acos(T x) {
        ASSERT(abs(x) <= 1)
        return std::acos(x);
    }
    // :: atan
    template<floating_point T>
    T atan(T x) {
        return std::atan(x);
    }

    // exp / log
    // :: exp
    template<floating_point T>
    T exp(T x) {
        return std::exp(x);
    }
    // :: ln
    template<floating_point T>
    T ln(T x) {
        ASSERT(x > 0)
        return std::log(x);
    }
    // :: log2
    template<floating_point T>
    T log2(T x) {
        ASSERT(x > 0)
        return std::log2(x);
    }
    // :: log10
    template<floating_point T>
    T log10(T x) {
        ASSERT(x > 0)
        return std::log10(x);
    }
    // :: pow
    template<floating_point T>
    T pow(T base, T exponent) {
        ASSERT(base > 0)
        return std::pow(base, exponent);
    }
    // :: pow2
    template<numeric T>
    T pow2(T x) {
        return x * x;
    }
    // :: pow3
    template<numeric T>
    T pow3(T x) {
        return x * x * x;
    }
    // :: pow4
    template<numeric T>
    T pow4(T x) {
        return x * x * x * x;
    }

    // max
    template<numeric T1, numeric T2, numeric... TRest>
    auto max(const T1& val1, const T2& val2, TRest&&... rest) {
        if constexpr(sizeof...(TRest) == 0) {
            return val1 >= val2 ? val1 : val2;
        }
        else {
            return max(val1 >= val2 ? val1 : val2, forward<TRest>(rest)...);
        }
    }
    // min
    template<numeric T1, numeric T2, numeric... TRest>
    auto min(const T1& val1, const T2& val2, TRest&&... rest) {
        if constexpr(sizeof...(TRest) == 0) {
            return val1 > val2 ? val2 : val1;
        }
        else {
            return min(val1 > val2 ? val2 : val1, forward<TRest>(rest)...);
        }
    }

    // clamp
    template<numeric T>
    T clamp(T x, auto minValue, auto maxValue) {
        return max(minValue, min(x, maxValue));
    }
    template<numeric T>
    T clamp01(T x) {
        return clamp(x, 0, 1);
    }
    // inRange
    template<numeric T>
    bool inRange(T x, auto minValue, auto maxValue) {
        return x >= minValue && x <= maxValue;
    }
    template<numeric T>
    bool inRange01(T x) {
        return inRange(x, 0, 1);
    }
}