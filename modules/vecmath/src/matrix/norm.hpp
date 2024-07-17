#pragma once
#include "alias.hpp"

namespace Math {
    // inner
    template<typename T, uint N, uint M>
    auto inner(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
        T out = 0;
        for (uint i = 0; i < N * M; ++i) {
            out += mat1.at(i) * mat2.at(i);
        }
        return out;
    }
    template<typename T, uint N, uint M>
    auto inner(const Mat<T, N, M>& mat) {
        return inner(mat, mat);
    }
    // transpose
    template<typename T, uint N, uint M>
    auto transpose(const Mat<T, N, M>& mat) {
        Mat<T, M, N> out;
        for (uint n = 0; n < N; ++n) {
            for (uint m = 0; m < M; ++m) {
                out.at(m, n) = mat.at(n, m);
            }
        }
        return out;
    }
    // norm
    template<floating_point T, uint N, uint M>
    auto norm(const Mat<T, N, M>& mat) {
        return sqrt(inner(mat));
    }
    // normalize
    template<floating_point T, uint N, uint M>
    auto normalize(const Mat<T, N, M>& mat) {
        return mat / norm(mat);
    }

    // vector operations
    // :: dot
    template<typename T, uint N>
    auto dot(const Vec<T, N>& v1, const Vec<T, N>& v2) {
        T out = 0;
        for (uint n = 0; n < N; ++n) {
            out += v1.at(n) * v2.at(n);
        }
        return out;
    }
    template<typename T, uint N>
    auto dot(const Vec<T, N>& v) {
        return dot(v, v);
    }
    // :: cross
    template<typename T>
    auto cross(const Vec3<T>& v1, const Vec3<T>& v2) {
        return Vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }
    // :: length
    template<floating_point T, uint N>
    auto length(const Vec<T, N>& v) {
        return sqrt(dot(v));
    }
    // :: distance
    template<floating_point T, uint N>
    auto distance(const Vec<T, N>& v1, const Vec<T, N>& v2) {
        return length(v2 - v1);
    }
}