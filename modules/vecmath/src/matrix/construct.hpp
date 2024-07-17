#pragma once
#include "struct.hpp"

namespace Math {
    // Zero
    template<typename T, uint N, uint M = N>
    auto Zero() {
        Mat<T, N, M> mat;
        for (uint row = 0; row < N; ++row) {
            for (uint col = 0; col < M; ++col) {
                mat.at(row, col) = T(0);
            }
        }
        return mat;
    }
    // Identity
    template<typename T, uint N>
    auto Identity() {
        auto mat = Zero<T, N>();
        for (uint n = 0; n < N; ++n) {
            mat.at(n, n) = T(1);
        }
        return mat;
    }
    // insert
    template<typename T, uint N, uint M>
    template<typename U, uint N2, uint M2>
    auto Mat<T, N, M>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= N && M2 + where.y <= M)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.x + n, where.y + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    template<typename T>
    template<typename U, uint N2, uint M2>
    auto Mat<T, 2, 1>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= 2 && M2 + where.y <= 1)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.x + n, where.y + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    template<typename T>
    template<typename U, uint N2, uint M2>
    auto Mat<T, 3, 1>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= 3 && M2 + where.y <= 1)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.x + n, where.y + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    template<typename T>
    template<typename U, uint N2, uint M2>
    auto Mat<T, 4, 1>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= 4 && M2 + where.y <= 1)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.y + n, where.x + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    // resize
    template<uint N2, uint M2, typename T, uint N, uint M>
    auto resize(const Mat<T, N, M>& mat) {
        Mat<T, N2, M2> out;
        out.insert(mat, { 0, 0 });
        return out;
    }
}